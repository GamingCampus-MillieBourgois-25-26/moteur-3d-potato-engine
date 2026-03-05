#pragma once

#include <Jolt/Jolt.h>
#include <DirectXMath.h>

namespace Maths
{
	struct Vec3
	{
		float x, y, z;

		Vec3(const JPH::Vec3& v) : x(v.GetX()), y(v.GetY()), z(v.GetZ()) {};
		Vec3(const DirectX::XMFLOAT3& v) : x(v.x), y(v.y), z(v.z) {};
		Vec3(float a,float b, float c) : x(a), y(b), z(c) {};

		operator JPH::Vec3() const;
		operator DirectX::XMFLOAT3() const;

	};
}