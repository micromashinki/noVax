#include <limits.h>
#include <cstdint>
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

		if (value > (Type)UINT64_MAX/2)
			N = true;
		else
			N = false;

		value = value >> sizeof(Type);
		C = value >> 1;
	}

	template<typename Type>
	void detectCflag(Type a,Type b) {

		Type fgh = UINT64_MAX;
		if (((Type)UINT64_MAX / 2 > a && (Type)UINT64_MAX / 2 < b) || ((Type)UINT64_MAX / 2 < a && (Type)UINT64_MAX / 2 > b))
			V = true;
		else
			V = false;
	}

};
