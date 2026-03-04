#pragma once
#include <cstdint>
#include <random>

namespace Engine
{
    inline uint64_t GenerateUUID()
    {
        static std::random_device rd;
        static std::mt19937_64 eng(rd());
        static std::uniform_int_distribution<uint64_t> distr;
        return distr(eng);
    }
}