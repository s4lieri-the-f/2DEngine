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
    bool alive{true};
    int x, y;

public:
    Type type;
    Priority priority;

    int age;
    int max_age;

    EntityInterface(Type type, Priority priority) : type(type), priority(priority){};
    virtual void die();
    std::pair<int, int> get_position();
    virtual std::vector<EntityInterface *> tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *);
};

class Fish : public EntityInterface
{
public:
    virtual bool partner_in_range(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size);
    virtual void die();
    virtual bool is_alive();
    virtual EntityInterface *reproduce(); // @TODO add logic to return two fish
};

class GoodEntity : public Fish
{
public:
    virtual std::pair<int, int> get_predator(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size);
    bool fish_in_radius(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size);
    void move_away(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size);
};

class BadEntity : public Fish
{
public:
    virtual std::pair<int, int> get_prey(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size);
};

class Shark : public BadEntity
{
};

class Caviar : public GoodEntity
{
public:
};

// add Entity classes there

class BadCarp : public BadEntity
{
public:
    std::vector<EntityInterface *> tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *);
};
class GoodCarp : public GoodEntity
{
public:
    std::vector<EntityInterface *> tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *);
};
class CaviarCarp : public Fish
{
public:
    std::vector<EntityInterface *> tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *);
};
class Stone : public EntityInterface
{
public:
    std::vector<EntityInterface *> tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *);
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