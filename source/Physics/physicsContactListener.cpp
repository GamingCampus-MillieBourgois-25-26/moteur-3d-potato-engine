#include "physicsContactListener.h"

#include <iostream>

void OnContactAdded(const JPH::Body& body1, const JPH::Body& body2, const JPH::ContactManifold& manifold, JPH::ContactSettings& ioSettings)
{
	std::cout << "A contact was added" << std::endl;
}
void OnContactPersisted(const JPH::Body& body1, const JPH::Body& body2, const JPH::ContactManifold& manifold, JPH::ContactSettings& ioSettings)
{
	std::cout << "A contact persisted" << std::endl;
}
void OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair)
{
	std::cout << "A contact was removed" << std::endl;
}