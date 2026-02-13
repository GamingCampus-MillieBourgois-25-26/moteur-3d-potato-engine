#include "physicsBroadPhaseLayerManager.h"

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
	switch ((JPH::BroadPhaseLayer::Type)inLayer)
	{
	case ((JPH::BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING): return "NON_MOVING";
	case ((JPH::BroadPhaseLayer::Type)BroadPhaseLayers::MOVING): return "MOVING";
	default: return "INVALID";
	}
}
