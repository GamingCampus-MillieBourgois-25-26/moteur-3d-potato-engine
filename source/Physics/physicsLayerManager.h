#pragma once

#include "physicsLayers.h"

class PhysicsLayerManager
{
public:
	bool ShouldCollide(JPH::ObjectLayer layerA, JPH::ObjectLayer layerB) const;
};