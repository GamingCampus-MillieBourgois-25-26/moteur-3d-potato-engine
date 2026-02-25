#pragma once

#include <cstdint>
#include <random>

class UUID
{
public:
    using ID = uint64_t;

    static ID Generate()
    {
        static std::random_device rd;
        static std::mt19937_64 eng(rd());
        static std::uniform_int_distribution<uint64_t> distr;

        return distr(eng);
    }
};