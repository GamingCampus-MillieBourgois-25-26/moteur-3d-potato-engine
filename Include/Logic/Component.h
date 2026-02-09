#pragma once

class Actor;

class Component
{
public:
    virtual ~Component() = default;

    virtual void OnInit() {}
    virtual void OnUpdate(float dt) {}
    virtual void OnDestroy() {}

    Actor* owner = nullptr;
};
