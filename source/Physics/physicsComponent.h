#pragma once

#include <Jolt/Physics/Body/BodyID.h>
#include <Jolt/Physics/Body/BodyInterface.h>

class PhysicsComponent
{
public:
	PhysicsComponent() = default;
	~PhysicsComponent();

	void Initialize()