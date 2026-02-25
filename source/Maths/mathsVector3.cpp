#include <Jolt/Jolt.h>
//dx11

struct Vec3
{
	float x, y, z;

	Vec3(const JPH::Vec3& v) : x(v.GetX()), y(v.GetY()), z(v.GetZ());
	//Constructeur DX11

	operator JPH::Vec3() const
	{
		return JPH::Vec3(x, y, z);
	}
};