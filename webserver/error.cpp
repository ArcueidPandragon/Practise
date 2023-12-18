#include <cstdlib>
#include <stdio.h>
#include "error.h"
void handError(const char* error){
	puts(error);
	std::exit(1);
	}

