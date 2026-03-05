#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Core/Reference.h>
#include <Jolt/Physics/Collision/Shape/Shape.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/PhysicsSystem.h>

enum ShapeType
{
	Box,
	Sphere,
	Capsule
};

class PhysicsShape
{
public:
	ShapeType type;

	virtual ~PhysicsShape() = default;

	virtual JPH::Ref<JPH::Shape> GetJoltShape() const = 0;
};


class BoxShape : public PhysicsShape
{
public:
	JPH::Vec3 halfExtents;

	BoxShape(const JPH::Vec3& halfExtent)
		: halfExtents(halfExtent)
	{
		type = ShapeType::Box;
	}

	JPH::Ref<JPH::Shape> GetJoltShape() const override
	{
		return new JPH::BoxShape(halfExtents);
	}
};

////////////////////////////////////////////////////////////

class SphereShape : public PhysicsShape
{
public:
	float radius;

	SphereShape(float rad)
		: radius(rad)
	{
		type = ShapeType::Sphere;
	}

	JPH::Ref<JPH::Shape> GetJoltShape() const override
	{
		return new JPH::SphereShape(radius);
	}
};

////////////////////////////////////////////////////////////

class CapsuleShape : public PhysicsShape
{
public:
	float radius;
	float height;

	CapsuleShape(float rad, float hgt)
		: radius(rad), height(hgt)
	{
		type = ShapeType::Capsule;
	}

	JPH::Ref<JPH::Shape> GetJoltShape() const override
	{
		return new JPH::CapsuleShape(height * 0.5f, radius);
	}
};