
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>

#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

#include "exprtk.hpp"
#include "variant.h"


bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789.") == std::string::npos;
};

bool is_reserved(const std::string &str)
{    
    bool is_word = exprtk::details::is_reserved_word(str);
    bool is_func = exprtk::details::is_base_function(str);
    bool is_control = exprtk::details::is_control_struct(str);
    bool is_logic = exprtk::details::is_logic_opr(str);  
    return is_word || is_func || is_control || is_logic;
};

inline std::vector<variant> compute(std::string expression_string)
{
    using namespace std;
    using namespace boost;

    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    expression_string.erase(remove_if(expression_string.begin(), expression_string.end(), ::isspace),
                            expression_string.end());

    vector<std::string> variants;
    for (const auto &t : tokenizer<char_separator<char>>(
             expression_string, char_separator<char>("<>:=()[]{}^/*+-,!;")))
    {
        bool is_var = !is_digits(t) && !is_reserved(t);
        if (is_var)  // If not num
        {
            variants.emplace_back(t);  // Make variable
        }
    }

    // Make var list unique
    set<string> s(variants.begin(), variants.end());
    variants.assign(s.begin(), s.end());    
    vector<variant> unique_vars;
    for (auto &v : variants)
    {
        unique_vars.emplace_back(v);
    }
    
    // Build variable table
    symbol_table_t symbol_table;
    symbol_table.add_constants(); // pi, phi, inf
    for (auto &v : unique_vars){
        symbol_table.add_variable(v.token, v.value);
    }

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    auto begin = std::chrono::high_resolution_clock::now();

    parser_t parser;
    if (!parser.compile(expression_string, expression)){
        cout << "\n" << expression_string << "\nCompilation error...\n";
        return std::vector<variant>();
    }

    auto mid = std::chrono::high_resolution_clock::now();

    expression.value();

    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout   << "Compile Time = " << std::chrono::duration_cast<std::chrono::microseconds>(mid-begin).count() << "us\n" 
                << "Evaluate Time = " << std::chrono::duration_cast<std::chrono::microseconds>(end-mid).count() << "us\n";

    return unique_vars;
};



class web_interface
{
public:
    const char* get_vals(const char* input_string)
    {
        std::string line_out;
        std::vector<variant> result = compute(std::string(input_string));
        if(result.size() == 0){
            return "#ERR";            
        }else{
            for(auto& v : result){
                line_out += v.token + " = " + std::to_string(v.value) + "\n";
            }
        }

		char* output_cstr = new char[line_out.length() + 1];
		strcpy(output_cstr, line_out.c_str());

        return output_cstr;
    }
};

/*
The goal is to create a dependancy tree to solve values of variables
1. Need to ID the equations
    1. Differentiat between function blocks for(){}, while(){}, vec[#]={#,...,#}, etc. and equations 
    2. Split by ; for function blocks
    3. Once split, 
2. Need to build dependancy network
*/