#include <string>

using namespace std;
class variant
{
public:
	variant(string token_) : token(token_) {};
	variant() {}; //Default constructor
	~variant() {}; //Default constructor
	string token = "";
	double value = 0.0;
};