#include "ECS.h"
#include <stdlib.h>
#include "../Logger/Logger.h"

//TODO: Implement all the fucntions from ECS.

int Entity::GetId() const {
    return id;
}


void System::AddEntitiyToSystem(Entity entity) {
    entities.push_back(entitiy);
}
void System::RemoveEntityFromSystem(Entity entity) {
    entities.erase(std::__remove_if(entities.begin(), entities.end(), [&entity](Entity other){
        return entity == other;
    }), entities.end());
}
std::vector<Entity> GetSystemEntities() const{
    return entities;
}
const Signature& GetComponentSignature() const{
    return componentSignature;
}
Entity Registry::CreateEntity() {
    int entityId;

    entityId = numEntities++;

    Entity entity(entityId);
    entitiesToBeAdded.insert(entity);
    return entity;

    Logger::Log("Entity created with is = " + std::to_string(entityId));
}

void Registry::Update() {

}