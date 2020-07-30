#pragma once

#include "Entity.h"

class EntityManager;

class SystemBase{

    EntityManager* m_entitymanager;

public:
    explicit SystemBase (EntityManager* entity_manager) : m_entitymanager (entity_manager) { }
    virtual ~SystemBase() = default;

    virtual void on_entity_created(const Entity& entity) = 0;
    virtual void on_entity_destroyed(const Entity& entity) = 0;
    virtual void update(float dT) = 0;
};