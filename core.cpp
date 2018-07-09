#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

#include "interface.hpp"
#include "glue.cpp" //must include for WebIDL interface


int main(){
	printf("Main funct.\n");
	return 0;
}
