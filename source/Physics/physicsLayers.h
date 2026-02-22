#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/ObjectLayer.h>

namespace PhysicsLayers
{
	static const JPH::ObjectLayer NON_MOVING = 0;
	static const JPH::ObjectLayer MOVING = 1;
	static const JPH::uint NUM_PHYSICS_LAYERS = 2;
}