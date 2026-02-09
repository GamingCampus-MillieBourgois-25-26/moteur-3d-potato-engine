#pragma once

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <string>
#include "Component.h"

class Actor
{
public:
    using ID = uint64_t;

    Actor(ID id, const std::string& name = "Actor")
        : m_ID(id), m_Name(name) {
    }

    template<typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
        auto type = std::type_index(typeid(T));
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        comp->owner = this;

        T& ref = *comp;
        m_Components[type] = std::move(comp);

        ref.OnInit();
        return ref;
    }

    template<typename T>
    T* GetComponent()
    {
        auto type = std::type_index(typeid(T));
        auto it = m_Components.find(type);
        if (it == m_Components.end())
            return nullptr;

        return static_cast<T*>(it->second.get());
    }

    template<typename T>
    bool HasComponent() const
    {
        return m_Components.contains(std::type_index(typeid(T)));
    }

    void OnUpdate(float dt)
    {
        for (auto& [type, comp] : m_Components)
            comp->OnUpdate(dt);
    }

    ID GetID() const { return m_ID; }
    const std::string& GetName() const { return m_Name; }

private:
    ID m_ID;
    std::string m_Name;

    std::unordered_map<std::type_index, std::unique_ptr<Component>> m_Components;
};
