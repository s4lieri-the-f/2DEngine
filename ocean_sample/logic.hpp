#include <vector>
#include <future> // Я ещё подумаю об этом.

/*
    Тоже сделано в смешном состоянии. 
    Исправлять можно всё, главное -- чтобы Ocean::get_grid() возвращал int**, который я могу отправить Ксюше.
*/

enum Type
{
    BACTERIA,
    FISH,
    SHARK,
    ROCK
    // Add more types here
};

enum Priority
{
    LOW,
    MEDIUM,
    HIGH
};

#include <queue>
#include <unordered_map>
#include <vector>

template <typename T, typename Priority>
class PriorityQueueMap
{
    std::unordered_map<T, std::pair<int, int>> map;
    std::priority_queue<std::pair<Priority, T>> queue;

public:
    PriorityQueueMap();

    void insert(const T &key, const Priority &priority);

    void erase(const T &key);

    std::pair<Priority, T> top();

    void pop();

    ~PriorityQueueMap();
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
    PriorityQueueMap<std::pair<Entity, int>, Priority> entities;
    std::pair<int, int> size;
public:
    Ocean(int x, int y) : size(std::make_pair(x, y)) { entities = PriorityQueueMap<std::pair<Entity, int>, Priority>(); };
    void add_entity(Entity entity);
                // По факту рождение, хулидесу. Энтити сразу можно координаты задать.
    void tick();// Для каждого энтити по приоритету проверяем че происходит, изменения вносим сразу.
                // Есть обращения по x, y (главное делать это парой), можно вытаскивать из entities, существует ли добрая рыпка поблизости, и жрать её раньше, чем она свалит, к примеру.
                // Тик без цикла, сделай это функцией, которая вызывается внутри нетворкинга. Это я дописываю уже. С тебя классы, тики каждого энтити, и изменение.
    int ** get_grid(); 
                // Построение карты для отправки Ксюши. Тоже допиши.

    ~Ocean();
};

