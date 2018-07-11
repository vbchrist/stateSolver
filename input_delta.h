#pragma once
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
class input_delta
{
public:
	input_delta();
	~input_delta();
	char* get_changes(const char*  input_cstr);
	pair<vector<string>, vector<string>> adds_removals(vector<string> s1, vector<string> s2);

private:

	vector<string> last_string_vec;
	string input = "";
};



input_delta::input_delta()
{
}


input_delta::~input_delta()
{
}

char* input_delta::get_changes(const char*  input_cstr)
{
	std::string input(input_cstr);

	boost::char_separator<char> sep(";");
	boost::tokenizer<boost::char_separator<char>> tokens(input, sep);
	vector<string> current_string_vec;
	for (const auto& t : tokens) {
		current_string_vec.emplace_back(t);
	}
	auto differences = adds_removals(last_string_vec, current_string_vec);

	string output;
	output += "Adds:\n";
	for (auto& a : differences.first) {
		output += a + "\n";
	}
	output += "Removes:\n";
	for (auto& r : differences.second) {
		output += r + "\n";
	}

	char* output_cstr = new char[output.length() + 1];
	strcpy(output_cstr, output.c_str());

	last_string_vec = current_string_vec;

	return output_cstr;
}

inline pair<vector<string>, vector<string>> input_delta::adds_removals(vector<string> s1, vector<string> s2)
{
	vector<string> add, remove;
	//case insensitive
	//for (auto& s : s1) { std::transform(s.begin(), s.end(), s.begin(), ::tolower); }
	//for (auto& s : s2) { std::transform(s.begin(), s.end(), s.begin(), ::tolower); }
	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());

	size_t start = 0;
	for (size_t left = 0; left < s1.size(); ++left) {
		for (size_t right = start; right < s2.size(); ++right) {

			if (s1[left] == s2[right]) {
				start = right + 1;
				right = s2.size();
			}
			else if (left < s1.size() -1 && s1[left + 1] == s2[right]) {
				remove.emplace_back(s1[left]);
				left++;
				start = right + 1;
				right = s2.size();
			}
			else {
				add.emplace_back(s2[right]);
			}

		}
	}
	for (size_t right = start; right < s2.size(); ++right) {
		add.emplace_back(s2[right]);
	}

	return pair<vector<string>, vector<string>>(add, remove);
}


