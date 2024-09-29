#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>

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

        std::vector<IPool*> componentPools;
};

template <typename TComponent>
void System::RequireComponent() {
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
};

#endif