#include "physicsBodyFactory.h"

#include "physicsLayers.h"

#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/ObjectLayer.h>

PhysicsBody PhysicsBodyFactory::CreateBody(PhysicsSystem& system, PhysicsBodyType type, const PhysicsShape& shape, float mass, JPH::Vec3 position, JPH::Quat rotation)
{
	JPH::BodyInterface& bodyInterface = system.GetJoltSystem().GetBodyInterface();

	JPH::EMotionType motionType = JPH::EMotionType::Static;

	switch (type)
	{
	case PhysicsBodyType::Static: motionType = JPH::EMotionType::Static; break;
	case PhysicsBodyType::Dynamic: motionType = JPH::EMotionType::Dynamic; break;
	case PhysicsBodyType::Kinematic: motionType = JPH::EMotionType::Kinematic; break;
	}

	JPH::ObjectLayer layer;

	if (motionType == JPH::EMotionType::Static)
	{
		layer = PhysicsLayers::NON_MOVING;
	}
	else
	{
		layer = PhysicsLayers::MOVING;
	}

	JPH::BodyCreationSettings settings(shape.GetJoltShape(), position, rotation, motionType, layer);

	JPH::Body* body = bodyInterface.CreateBody(settings);

	JPH::EActivation activation;
	if (motionType == JPH::EMotionType::Dynamic)
	{
		activation = JPH::EActivation::Activate;
	}
	else
	{
		activation = JPH::EActivation::DontActivate;
	}

	bodyInterface.AddBody(body->GetID(), activation);

	return PhysicsBody(body->GetID(), &bodyInterface);
}