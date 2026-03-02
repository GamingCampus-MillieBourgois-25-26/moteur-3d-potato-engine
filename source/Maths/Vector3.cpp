#include "Maths/Vector3.h"

Maths::Vec3::operator JPH::Vec3() const
{
	return JPH::Vec3(x, y, z);
}
Maths::Vec3::operator DirectX::XMFLOAT3() const
{
	return DirectX::XMFLOAT3(x, y, z);
}
