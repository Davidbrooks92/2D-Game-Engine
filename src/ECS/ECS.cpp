#include "ECS.h"
#include <stdlib.h>

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