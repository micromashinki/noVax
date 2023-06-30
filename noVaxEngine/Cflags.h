#include <limits.h>
#include <cstdint>
#pragma once

class Cflags {
public:
	bool C{ 0 };
	bool V{ 0 };
	bool Z{ 0 };
	bool N{ 0 };

    bool operator==(const Cflags& other) const {
        return C == other.C && V == other.V && Z == other.Z && N == other.N;
    }

};
