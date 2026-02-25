#include "Physics/physicsLayerManager.h"

bool PhysicsObjectVSBroadPhaseLayerFilter::ShouldCollide(JPH::ObjectLayer layerA, JPH::BroadPhaseLayer layerB) const
{
	if (layerA == PhysicsLayers::MOVING || layerB == BroadPhaseLayers::MOVING)
	{
		return true;
	}
	return false;
}

bool PhysicsObjectLayerPairFilter::ShouldCollide(JPH::ObjectLayer layerA, JPH::ObjectLayer layerB) const
{
	if (layerA == PhysicsLayers::MOVING || layerB == PhysicsLayers::MOVING)
	{
		return true;
	}
	return false;
}