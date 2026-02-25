#pragma once
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/BroadPhase/BroadPhaseLayer.h>

namespace BroadPhaseLayers
{
    inline constexpr JPH::BroadPhaseLayer NON_MOVING(0);
    inline constexpr JPH::BroadPhaseLayer MOVING(1);
    inline constexpr JPH::uint NUM_LAYERS = 2;
};