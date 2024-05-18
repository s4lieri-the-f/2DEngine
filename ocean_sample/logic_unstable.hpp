#include <vector>
#include <unordered_map>
#include <queue>

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

    void push(T);
    void top();
    void pop();
    void remove(T);
    bool is_empty();

    ~PriorityQueueMap() = default;
};

class EntityInterface
{
    int age;
    int max_age;
    bool alive{true};
    int x, y;

public:
    Type type;
    Priority priority;

    EntityInterface(Type type, Priority priority) : type(type), priority(priority){};

    virtual EntityInterface *tick(std::unordered_map<std::pair<int, int>, EntityInterface *> *);
};

class Fish : public EntityInterface
{
public:
    virtual bool partner_in_range(int radius);
    virtual void die();
    virtual bool is_alive();
    virtual EntityInterface *reproduce(); // @TODO add logic to return two fish
};

class GoodEntity : public Fish
{
    virtual std::pair<int, int> get_predator(int radius);
    bool fish_in_radius(int radius);
    void move_away();
};

class BadEntity : public Fish
{
    virtual std::pair<int, int> get_prey(int radius);
};

class Shark : public BadEntity
{
};

class Caviar : public GoodEntity
{
};

// add Entity classes there

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