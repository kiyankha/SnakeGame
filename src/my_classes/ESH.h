// #ifndef ESH_h_
// #define ESH_h_

// #include <iostream>
// #include <vector>
// #include <memory>
// #include <algorithm>
// #include <bitset>
// #include <array>

// class Component;
// class Entity;

// using ComponentID = std::size_t;

// inline ComponentID getComponentTypeID()
// {
//     static ComponentID lasID = 0;
//     return lasID++;
// }

// template <typename T>
// inline ComponentID getComponentTypeID() noexcept
// {
//     static ComponentID typeID = getComponentTypeID();

//     return typeID();
// }

// constexpr std::size_t maxComponents = 32;

// using ComponentBitSet = std::bitset<maxComponents>;
// using ComponentArray = std::array<Component *, maxComponents>;

// class Component
// {
// public:
//     Entity *entity;

//     virtual void init();
//     virtual void update();
//     virtual void draw();

//     virtual ~Component();
// };

// class Entity
// {
// private:
//     bool active = true;
//     std::vector<std::unique_ptr<Component>> components;

//     ComponentArray componentArray;
//     ComponentBitSet componentBitSet;

// public:
//     void update()
//     {
//         for (auto &c : components)
//             c->update();
//         for (auto &c : components)
//             c->draw();
//     }

//     void draw();
//     bool isActive() const { return active; }
//     void destroy() { active = false; }

//     template<typename T> bool hasComponent() const
//     {
//         return componentBitSet[getComponentTypeID<T>];
//     }

//     template<typename T, typename... TArgs>
//     T& addComponent(TArgs&&... mArgs)
//     {
//         T* c(new T(std::forward<TArgs>mArgs()...));
//         c->entity = this;
//         std::unique_ptr<Component> uPtr{c};
//         components.emplace_back(std::move(uPtr));

//         componentArray[getComponentTypeID<T>()] = c;
//         componentBitSet[getComponentTypeID<T>()] = true;

//         c->init();
//         return *c;
//     }

//     template<typename T> T& getComponentTypeID() const
//     {
//         auto ptr(componentArray[getComponentTypeID<T>()]);
//         return *static_cast<T*>(ptr);
//     }
    
// };

// #endif