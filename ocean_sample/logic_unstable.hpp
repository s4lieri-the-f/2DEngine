#include <vector>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <typeinfo>

enum Type
{
    WATER,       // yeah, we need a lot of water
    GOOD_CARP,   // some kind od a fish BUT IT'S DIFFERENT IT'S BETTER
    CARP_CAVIAR, // idk maybe i should make it like a part of карпик? it's like newborn carps
    WATER_LILY,  // can do nothing, just exists
    ROCK,        // can do nothing, but no one can move through it
    BAD_CARP,    // it's the most aggressive fish in the ocean
    PLAYER       ///???

};

enum Priority // we need it for queue
{
    LOW,
    MEDIUM,
    HIGH,
};

// сюда общие методы

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const
    {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

int random(int s, int f)
{
    int range = f - s + 1;
    return (std::clock() % range + s);
}

std::pair<int, int> new_coo(std::pair<int, int> coo, std::pair<int, int> size)
{
    if (coo.first > size.first)
    {
        coo.first %= size.first;
    }
    while (coo.first < 0)
    {
        coo.first += size.first;
    }
    if (coo.second > size.second)
    {
        coo.second %= size.second;
    }
    while (coo.second < 0)
    {
        coo.second += size.second;
    }
    return coo;
}

template <typename T>
class PriorityQueueMap
{
    struct cmp
    {
        bool operator()(const std::pair<int, T> &p1, const std::pair<int, T> &p2) const
        {
            return p1.first > p2.first;
        }
    };

    std::unordered_map<std::pair<int, int>, std::queue<T>> map;
    std::priority_queue<std::pair<int, T>, cmp> queue;

public:
    PriorityQueueMap() = default;

    void push(T *item);
    T *top();
    T *pop();
    bool is_empty();

    ~PriorityQueueMap() = default;
};

class EntityInterface
{
    int x, y;

public:
    Type type;
    Priority priority; 

    int age;
    int max_age;
    bool alive{true};

    EntityInterface(Type type, Priority priority) : type(type), priority(priority){};
    void die(); //how does dying work, do we need to return dead entity with new pos?
    std::pair<int, int> get_position();
    bool is_alive();
    void set_max_age(int new_max_age);
    virtual std::vector<EntityInterface *> tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *);
    void change_coo(std::pair<int, int> new_coo);
    EntityInterface *die_of_old_age(); //do we need to return dead entity with new pos?

};

class Fish : public EntityInterface
{
public:
    virtual bool partner_in_range(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size);
    virtual void die();
    virtual bool is_alive();
    //virtual EntityInterface *reproduce(); // @TODO add logic to return two fish
    virtual std::vector<EntityInterface*> reproduce(); 
};

class GoodEntity : public Fish
{
    Type predator_type; // logicaly there can be more than one predator, so we should change this moment later
public:

    virtual std::pair<int, int> get_predator(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size);
    bool fish_in_radius(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size);
    GoodEntity* move_away(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size);
    Type predator_type();
    std::vector<EntityInterface*> reproduce(std::pair<int, int> size);
};

class BadEntity : public Fish
{
    Type prey_type;
public:
    bool canibalism;
    virtual std::pair<int, int> get_prey(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size);
    Type prey_type();

};

class Shark : public BadEntity
{
};

class Caviar : public GoodEntity
{

public:
    int evolution_age;
    Type evolution_type;
    std::vector<std::pair<int, int>>* evolve(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size);
};

// add Entity classes there

class BadCarp : public BadEntity
{
    int max_age = 100;
public:
    
    BadCarp(std::pair<int, int> coo){
        this->change_coo(coo);
    }
    std::vector<EntityInterface *>* tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size);
};
class GoodCarp : public GoodEntity
{
    int max_age = 100;
public:
    GoodCarp(std::pair<int, int> coo){
        this->change_coo(coo);
    }
    std::vector<EntityInterface*> reproduce(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size);
    std::vector<EntityInterface *>* tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size);

};
class CaviarCarp : public Caviar
{
    int max_age = 10;
public:
    CaviarCarp(std::pair<int, int> coo){
        this->change_coo(coo);
    }
    std::vector<EntityInterface *>* tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size);
};
class Stone : public EntityInterface
{
    int max_age = 10000000;
public:
    Stone(std::pair<int, int> coo){
        this->change_coo(coo);
    }
    std::vector<EntityInterface *>* tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size);
};

class Ocean
{
    std::vector<std::vector<bool>> WaterlilyMap;
    PriorityQueueMap<EntityInterface *> *Entities;
    std::pair<int, int> size;

public:
    Ocean(std::pair<int, int> size); // random generation
    void tick();
    void regenerate_wlmap();
    std::vector<std::vector<int>> generate_map(); // return  ocean as int matrix to draw

    ~Ocean();
};