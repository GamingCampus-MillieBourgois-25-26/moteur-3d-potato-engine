#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/ContactListener.h>

class PhysicsContactListener : public JPH::ContactListener
{
public:
	void OnContactAdded(const JPH::Body& body1, const JPH::Body& body2, const JPH::ContactManifold& manifold, JPH::ContactSettings& ioSettings) override;
	void OnContactPersisted(const JPH::Body& body1, const JPH::Body& body2, const JPH::ContactManifold& manifold, JPH::ContactSettings& ioSettings) override;
	void OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair) override;
};
