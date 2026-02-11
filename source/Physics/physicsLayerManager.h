#pragma once

class PhysicsLayerManager
{
public:
	bool ShouldCollide(PhysicsLayer layerA, PhysicsLayer layerB) const;
};