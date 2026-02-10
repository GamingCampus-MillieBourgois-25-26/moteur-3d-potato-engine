

class RigidBody
{
private:
	JPH::Body body;
public:
	RigidBody(JPH::ShapeRefC shape, JPH::RVec3Arg position, JPH::QuatArg orientation, JPH::EMotionType motionType, JPH::ObjectLayer objectLayer);


};