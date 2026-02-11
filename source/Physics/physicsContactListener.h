#pragma once

class PhysicsContactListener : public JPH::ContactListener
{
public:
	void OnContactAdded(const JPH::Body& body1, const JPH::Body& body2, const JPH::ContactManifold& manifold) override;
	void OnContactPersisted(const JPH::Body& body1, const JPH::Body& body2, const JPH::ContactManifold& manifold) override;
	void OnContactRemoved(const JPH::Body& body1, const JPH::Body& body2) override;
};
