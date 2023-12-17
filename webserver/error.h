#pragma once
#include <cstdlib>
#include <stdio.h>

void handError(const char* error){
	puts(error);
	std::exit(1);
	}

