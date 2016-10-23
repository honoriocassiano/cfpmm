//============================================================================
// Name        : CFPMM.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include "InstanceUtils.h"

int main(void) {

	using namespace cfpmm;

	InstanceUtils::generate(10, 5, correlation::WEAK, true);

	return 0;
}
