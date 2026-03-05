#pragma once


#include <Jolt/Jolt.h>
#include <DirectXMath.h>

namespace Maths
{
	struct Quat
	{
		float x, y, z, w;

		Quat(const JPH::Quat& v) : x(v.GetX()), y(v.GetY()), z(v.GetZ()), w(v.GetW()) {};
		Quat(const DirectX::XMFLOAT4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {};
		Quat(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {};

		operator JPH::Quat() const;
		operator DirectX::XMFLOAT4() const;
	};
}