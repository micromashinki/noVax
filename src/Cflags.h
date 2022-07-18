#include <limits.h>
#pragma once

class Cflags {
public:
	bool C{ 0 };
	bool V{ 0 };
	bool Z{ 0 };
	bool N{ 0 };


	template<typename Type>
	void setFlags(uint64_t value) {
		if (value == 0)
			Z = true;
		else
			Z = false;

	//	if (value > (Type)MAXDWORD64/2)
	//		N = true;
	//	else
	//		N = false;

		value = value >> sizeof(Type);
		V = value >> 1;
	}

	template<typename Type>
	void detectCflag(Type a,Type b) {
		//if ((Type)MAXDWORD64 / 2 > a && (Type)MAXDWORD64 / 2 < b || (Type)MAXDWORD64 / 2 < a && (Type)MAXDWORD64 / 2 > b)
	//		C = true;
	//	else
	//		C = false;
	}

};
