#pragma once

#include "physicsLayers.h"
#include "physicsBroadPhaseLayers.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/BroadPhase/BroadPhaseLayer.h>

class PhysicsObjectVSBroadPhaseLayerFilter : public JPH::ObjectVsBroadPhaseLayerFilter
{
public:
	bool ShouldCollide(JPH::ObjectLayer layerA, JPH::BroadPhaseLayer layerB) const override;
};


class PhysicsObjectLayerPairFilter : public JPH::ObjectLayerPairFilter
{
public:
	bool ShouldCollide(JPH::ObjectLayer layerA, JPH::ObjectLayer layerB) const override;
};