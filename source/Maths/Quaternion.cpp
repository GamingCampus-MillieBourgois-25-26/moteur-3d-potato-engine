#include "Maths/Quaternion.h"

Maths::Quat::operator JPH::Quat() const
{
	return JPH::Quat(x, y, z, w);
}
Maths::Quat::operator DirectX::XMFLOAT4() const
{
	return DirectX::XMFLOAT4(x, y, z, w);
}
