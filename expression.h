#include <string>

using namespace std;
class expression
{
public:
	expression(string e) : raw_text(e) {};
	expression() {}; //Default constructor
	~expression() {}; //Default constructor
	string raw_text = "";
};

class linear : expression
{
public:
	linear() {}; //Default constructor
	~linear() {}; //Default constructor
};

class polynomial : expression
{
public:
	polynomial() {}; //Default constructor
	~polynomial() {}; //Default constructor
};

class nonlinear : expression
{
public:
	nonlinear() {}; //Default constructor
	~nonlinear() {}; //Default constructor
};