#include "Jolt/Jolt.h"

// Jolt includes
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>

// STL includes
#include <cstdarg>
#include <iostream>
#include <thread>

class RigidBody
{
private:
	JPH::Body body;
public:
	RigidBody(JPH::ShapeRefC shape, JPH::RVec3Arg position, JPH::QuatArg orientation, JPH::EMotionType motionType, JPH::ObjectLayer objectLayer);


};