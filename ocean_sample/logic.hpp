#include <vector>
#include <future>

enum Type
{
    BACTERIA,
    FISH,
    SHARK,
    ROCK
    // Add more types here
};

#include <queue>
#include <unordered_map>
#include <vector>

template <typename T, typename Priority>
class PriorityQueueMap
{
    std::unordered_map<T, Priority> map;
    std::priority_queue<std::pair<Priority, T>> queue;

public:
    void insert(const T &key, const Priority &priority)
    {
        map[key] = priority;
        queue.push({priority, key});
    }

    void erase(const T &key)
    {
        map.erase(key);
        // Note: This doesn't remove the item from the queue
    }

    std::pair<Priority, T> top()
    {
        auto top = queue.top();
        while (!queue.empty() && map[top.second] != top.first)
        {
            queue.pop();
            top = queue.top();
        }
        return top;
    }

    void pop()
    {
        auto top = queue.top();
        while (!queue.empty() && map[top.second] != top.first)
        {
            queue.pop();
            top = queue.top();
        }
        queue.pop();
        map.erase(top.second);
    }

    
};

class Entity{

    int x, y;
    Type type;

public:
    Entity(int x, int y, Type type) : x(x), y(y), type(type){};
    virtual std::pair<int, int> get_position() const = 0;
    virtual std::future<void> tick() = 0;
    ~Entity();
};

class Bacteria : public Entity
{
public:
    std::pair<int, int> get_position() const override;
    std::future<void> tick() override;
};

// More Entity classes here

class Ocean{
    std::vector<Entity*> entities;
    std::pair<int, int> size;
public:
    Ocean(int x, int y) : size(x, y){};
    void add_entity(Entity* entity);
    void tick();
    ~Ocean();
};

