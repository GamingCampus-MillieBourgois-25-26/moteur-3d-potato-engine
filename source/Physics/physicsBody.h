#pragma once

class PhysicsBody
{
public:
	void SetPosition(JPH::Vec3 position);
	void SetRotation(JPH::Quat rotation);
	
	void AddForce(JPH::Vec3 force);
	void AddImpulse(JPH::Vec3 impulse);

	JPH::BodyID GetID() const;

private:
	JPH::BodyID m_id;
};

