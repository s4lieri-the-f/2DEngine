#include <vector>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <typeinfo>

enum Type
{
    WATER,
    GOOD_CARP,
    CARP_CAVIAR,
    WATER_LILY,
    ROCK,
    BAD_CARP,
    PLAYER
};

enum Priority
{
    LOW,
    MEDIUM,
    HIGH,
};

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
    if (coo.first >= size.first)
    {
        coo.first %= size.first;
    }
    while (coo.first < 0)
    {
        coo.first += size.first;
    }
    if (coo.second >= size.second)
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

public:
    std::unordered_map<std::pair<int, int>, T, pair_hash> map;
    std::priority_queue<std::pair<int, T>, std::vector<std::pair<int, T>>, cmp> queue;

    PriorityQueueMap() = default;
    void insert(T new_entity);
    void erase(const T &key);
    T top();
    bool is_empty();
    bool empty();
    Type find(std::pair<int, int> coo);

    ~PriorityQueueMap() = default;
};

class EntityInterface
{
protected:
    int x, y;

public:
    Type type;
    Priority priority;

    int age;
    int max_age;
    bool alive{true};

    EntityInterface(Type type, Priority priority) : type(type), priority(priority) {}
    void die();
    virtual std::pair<int, int> get_position();
    bool is_alive();
    void set_max_age(int new_max_age);
    virtual std::vector<EntityInterface *> tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &map, std::pair<int, int> size);
    void change_coo(std::pair<int, int> new_coo);
    EntityInterface *die_of_old_age();
};

class Fish : public EntityInterface
{
public:
    Fish(Type type, Priority priority) : EntityInterface(type, priority) {}
    virtual bool partner_in_range(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size);
    virtual void die();
    virtual bool is_alive();
    virtual std::vector<EntityInterface *> reproduce();
};

class GoodEntity : public Fish
{
    Type predator;

public:
    GoodEntity(Type type, Priority priority) : Fish(type, priority) {}
    virtual std::pair<int, int> get_predator(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size);
    bool fish_in_radius(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size);
    GoodEntity *move_away(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size);
    Type predator_type();
    std::vector<EntityInterface *> reproduce(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size);
    std::vector<EntityInterface *> tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size) override;
};

class BadEntity : public Fish
{
    Type prey;

public:
    bool canibalism;
    BadEntity(Type type, Priority priority) : Fish(type, priority) {}
    virtual std::pair<int, int> get_prey(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size);
    Type prey_type();
    std::vector<EntityInterface *> tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size) override;
};

class Caviar : public GoodEntity
{
public:
    int evolution_age;
    Type evolution_type;
    Caviar(Type type, Priority priority) : GoodEntity(type, priority) {}
    std::vector<std::pair<int, int>> *evolve(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size);
    std::vector<EntityInterface *> tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size) override;
};

class BadCarp : public BadEntity
{
    int max_age = 100;

public:
    BadCarp(std::pair<int, int> coo) : BadEntity(Type::BAD_CARP, Priority::MEDIUM)
    {
        this->change_coo(coo);
    }
    std::vector<EntityInterface *> tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size) override;
};

class GoodCarp : public GoodEntity
{
    int max_age = 100;

public:
    GoodCarp(std::pair<int, int> coo) : GoodEntity(Type::GOOD_CARP, Priority::MEDIUM)
    {
        this->change_coo(coo);
    }
    std::vector<EntityInterface *> reproduce(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size);
    std::vector<EntityInterface *> tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size) override;
};

class CaviarCarp : public Caviar
{
    int max_age = 10;

public:
    CaviarCarp(std::pair<int, int> coo) : Caviar(Type::CARP_CAVIAR, Priority::MEDIUM)
    {
        this->change_coo(coo);
    }
    std::vector<EntityInterface *> tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size) override;
};

class Stone : public EntityInterface
{
    int max_age = 10000000;

public:
    Stone(std::pair<int, int> coo) : EntityInterface(Type::ROCK, Priority::LOW)
    {
        this->change_coo(coo);
    }
    std::vector<EntityInterface *> tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size) override;
};

class Ocean
{
    std::vector<std::vector<bool>> WaterlilyMap;
    PriorityQueueMap<EntityInterface *> Entities;
    std::pair<int, int> size;

public:
    Ocean(std::pair<int, int> size); // random generation
    void tick();
    std::vector<std::vector<int>> generate_map(); // return ocean as int matrix to draw
};
