#include "physicsLayerManager.h"

bool PhysicsLayerManager::ShouldCollide(JPH::ObjectLayer layerA, JPH::ObjectLayer layerB) const
{
	if (layerA == PhysicsLayers::MOVING || layerB == PhysicsLayers::MOVING)
	{
		return true;
	}
	return false;
}