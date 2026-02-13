#pragma once

#include <unordered_map>
#include <memory>
#include "Actor.h"
#include "UUID.h"

class Scene
{
public:
    Actor& CreateActor(const std::string& name = "Actor")
    {
        Actor::ID id = UUID::Generate();
        auto [it, ok] = m_Actors.emplace(id, Actor(id, name));
        return it->second;
    }

    void DestroyActor(Actor::ID id)
    {
        m_Actors.erase(id);
    }

    void OnUpdate(float dt)
    {
        for (auto& [id, actor] : m_Actors)
            actor.OnUpdate(dt);
    }

    auto& GetActors() { return m_Actors; }

private:
    std::unordered_map<Actor::ID, Actor> m_Actors;
};
