#include "rigidbody.h"

#include <Jolt/Jolt.h>

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

RigidBody::RigidBody(JPH::ShapeRefC shape, JPH::RVec3Arg position, JPH::QuatArg orientation, JPH::EMotionType motionType, JPH::ObjectLayer objectLayer)
{
	JPH::BodyCreationSettings bSettings(shape, position, orientation, motionType, objectLayer);
}