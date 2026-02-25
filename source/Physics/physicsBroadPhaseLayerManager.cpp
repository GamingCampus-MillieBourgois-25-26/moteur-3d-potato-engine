#include "Physics/physicsBroadPhaseLayerManager.h"

PhysicsBroadPhaseLayerInterface::PhysicsBroadPhaseLayerInterface()
{
	m_ObjectToBroadPhase[PhysicsLayers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
	m_ObjectToBroadPhase[PhysicsLayers::MOVING] = BroadPhaseLayers::MOVING;
}

JPH::uint PhysicsBroadPhaseLayerInterface::GetNumBroadPhaseLayers() const
{
	return BroadPhaseLayers::NUM_LAYERS;
}

JPH::BroadPhaseLayer PhysicsBroadPhaseLayerInterface::GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const
{
	return m_ObjectToBroadPhase[inLayer];
}

const char* PhysicsBroadPhaseLayerInterface::GetBroadPhaseLayerName(JPH::BroadPhaseLayer inLayer) const
{
	switch (inLayer.GetValue())
	{
	case 0:	return "NON_MOVING";
	case 1:		return "MOVING";
	default:
		return "INVALID";
	}
}