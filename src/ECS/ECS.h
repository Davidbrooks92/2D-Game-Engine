#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>
 
const unsigned int MAX_COMPONENTS = 32;

// Signature: Using a bitset to keep track of which component an entity has and 
//also helps keep track of which entities a system is interested in 

typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent {
    protected:
    static int nextId;
};

// Used to assign a unique id to a component type
template <typename TComponent>

class Component: public IComponent {
    //Returns the unique id of Component<T>
    static int GetId(){
        static auto id = nextId++;
        return id;
    }
};

class Entity{
    private:
        int id;

    public:
    Entity(int id): id(id){};
    Entity(const Entity& entity) = default;
        int GetId() const;

        Entity& operator =(const Entity& other) = default;
        bool operator == (const Entity& other) const{return id == other.id;}
        bool operator != (const Entity& other) const{return id != other.id;}
        bool operator > (const Entity& other) const{return id > other.id;}
        bool operator < (const Entity& other) const{return id < other.id;}
};

//System:
// The system processes entities that contain a specific signature
class System {
    private:
        Signature componentSignature;
        std::vector<Entity> entities;
    
    public:
        System() = default;
        ~System() = default;

        void AddEntitiyToSystem(Entity entity);
        void RemoveEntityFromSystem(Entity entity);
        std::vector<Entity> GetSystemEntities() const;
        const Signature& GetComponentSignature() const;
        
        //Defines the component type
        template <typename TComponent> void RequireComponent();
};

//A pool is just a vector of objects of type T
class IPool {
    public:
        virtual ~IPool(){}
};

template <typename T>
class Pool: IPool{
    private:
        std::vector<T> data;

        public:
            Pool(int size = 100){
                data.resize(size);
                }
            ~Pool() = default;

            bool isEmpty() const{
                return data.empty();
            }

            int GetSize() const {
                return data.size();
            }
            void Resize(int n) {
                data.resize(n);
            }
            void Clear() {
                data.clear();
            }
            void Add(T object) {
                data.push_back(object);
            }
            void Set(int index, T object){
                data[index] = object;
            }
            T& Get(int index){
                return static_cast<T&>(data[index]);
            }
            T& operator[]unsigned int index() {
                return data[index];
            }
};

//the resistry manages the creation and the destruction of entities, add systems and components.
class Registry {
    private:
        int numEntities = 0;
        // Vector of component pools, each pool caontains all the data for a certain component type
        // Vector index = component type id
        // pool index = entity id
        std::vector<IPool*> componentPools;

        //Vector of component signatures per entity, saying which component is "Turned on" for a given entity
        // Vector index = entity id
        std::vector<Signature> entityComponentSignatures;

        std::unordered_map<std::type_index, System*> systems;

        // set of entities that are flagged to be added or removed in the next registry update

        std::set<Entity> entitiesToBeAdded;
        std::set<Entity> entitiesToBeKilled;

    public:
        Registry() = default;

        void Update();

        Entity CreateEntity();

        template <typename TComponent, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);

        //TODO AddComponent<T>(...);

        void AddEntityToSystem(Entity entity);
        //TODO 
        //create entity()
        //destroy entity()
        // add component (Entity entity)
        //remove component (Entity entity)
        //has component (Entuty entity)
        //addsystem()
        //has system()
        //get system() 
        Entity CreateEntity();

};

template <typename TComponent>
void System::RequireComponent() {
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
};

template <typename TComponent, typename ...TArgs>
void Registry::AddComponent(Entity entity, TArgs&& ...args) {
    const auto componentId = component<TComponent>::GetId();
    const auto entityId = entity.GetId();

    if (componentId >= componentPools.size()){
        componentPools.resize(componentId + 1, nullptr);
    }

    if (!componentPools[componentId]) {
        Pool<TComponent>* newComponentPool = new Pool<TComponent>();
        componentPools[componentId] = newComponentPool;
    }

    Pool<TComponent>* componentPool = componentPools[componentId];

    if (entityId >= componentPool->GetSize()){
        compnentPool->Resize(numEntities);
    }

    TComponent newComponent(std::forward<TArgs>(args)...);

    componentPool->Set(entityId, newComponent);

    entityComponentSignatures[entityId].set(componentId);
}

#endif