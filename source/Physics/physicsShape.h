#pragma once

class PhysicsShape
{
public:
	virtual ~PhysicsShape() = default;
	virtual JPH::Ref<JPH::Shape> GetJoltShape() const = 0;
};

class BoxShape : public PhysicsShape {};
class SphereShape : public PhysicsShape {};
class CapsuleShape : public PhysicsShape {};