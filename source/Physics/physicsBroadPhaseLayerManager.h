#include "physicsBroadPhaseLayers.h"

#include "physicsLayers.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/BroadPhase/BroadPhaseLayer.h>

class PhysicsBroadPhaseLayerInterface : public JPH::BroadPhaseLayerInterface
{
public:
	PhysicsBroadPhaseLayerInterface();

	JPH::uint GetNumBroadPhaseLayers() const;

	JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const override;

	const char* GetBroadPhaseLayerName(JPH::BroadPhaseLayer inLayer) const override;

private:
	JPH::BroadPhaseLayer m_ObjectToBroadPhase[PhysicsLayers::NUM_LAYERS];
};