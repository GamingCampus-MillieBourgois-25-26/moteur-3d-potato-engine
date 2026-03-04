#include "Physics/physicsContactListener.h"

#include <iostream>

void PhysicsContactListener::OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings)
{
	std::cout << "A contact was added" << std::endl;
}
void PhysicsContactListener::OnContactPersisted(const JPH::Body& body1, const JPH::Body& body2, const JPH::ContactManifold& manifold, JPH::ContactSettings& ioSettings)
{
	std::cout << "A contact persisted" << std::endl;
}
void PhysicsContactListener::OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair)
{
	std::cout << "A contact was removed" << std::endl;
}