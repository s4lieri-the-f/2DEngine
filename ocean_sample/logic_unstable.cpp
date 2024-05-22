#include <logic_unstable.hpp>
#include <boost/functional/hash.hpp>

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const
    {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return boost.hash_combine(h1, h2);
    }
};

// PriorityQueueMap
template <typename T>
void PriorityQueueMap<T>::push(T *item)
{
    queue.push(item, item.priority);
    map.insert({item.x, item.y});
};
template <typename T>
T *PriorityQueueMap<T>::pop()
{
    return queue.pop().first;
};
template <typename T>
T *PriorityQueueMap<T>::top()
{
    return queue.top().first;
};
template <typename T>
bool PriorityQueueMap<T>::is_empty()
{
    return queue.empty();
};

// EntityInterface
std::vector<EntityInterface *> EntityInterface::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *map)
{
    std::vector<EntityInterface *> tmp;
    return tmp;
};

std::pair<int, int> EntityInterface::get_position()
{
    return {x, y};
}

void EntityInterface::die()
{
    this->alive = false;
}

// Fish
bool Fish::partner_in_range(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size)
{
    if (radius == 1)
    {

        int x = this->get_position().first;
        int y = this->get_position().second;
        std::pair<int, int> moves[] = {{x, y}, {x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1}, {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1}};
        for (int i = 0; i < 9; ++i)
        {
            moves[i] = new_coo(moves[i], size);
            if (M->find(moves[i]) != M->end() && M[moves[i]].type == this->type)
            {
                return 1;
            }
        }
        return 0; // there isn't any
    }
    //?
    return 0;
}

void Fish::die()
{
    this->die();
} // сомнительно

bool Fish::is_alive()
{
    return this->alive;
} // не работает

EntityInterface *Fish::reproduce()
{
    return this; // что оно должно по умолчанию возвращать...
}

// GoodEntity
std::pair<int, int> GoodEntity::get_predator(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size)
{
    // откуда мы возьмем тип хищника?..
    int x = this->get_position().first;
    int y = this->get_position().second;
    std::pair<int, int> moves[] = {{x, y}, {x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1}, {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1}};
    for (int i = 0; i < 9; ++i)
    {
        moves[i] = new_coo(moves[i], size);
        if (M->find(moves[i]) != M->end() && typeid(*M[moves[i]]).name() == "class BadEntity") // надеюсь тип так сравнится...
        {
            return moves[i];
        }
    }
    return {-1, -1};
} // работает только в радиусе 1...

bool GoodEntity::fish_in_radius(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size)
{
    int x = this->get_position().first;
    int y = this->get_position().second;
    std::pair<int, int> moves[] = {{x, y}, {x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1}, {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1}};
    for (int i = 0; i < 9; ++i)
    {
        moves[i] = new_coo(moves[i], size);
        if (M->find(moves[i]) != M->end() && M[moves[i]].type == this->type)
        {
            return 1;
        }
    }
    return 0;
}

void GoodEntity::move_away(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size)
{
    int x1 = this->get_position().first;
    int y1 = this->get_position().second;
    std::pair<int, int> predator_coo = get_predator(1, M, size); // какой радиус...
    if (predator_coo.first == -1)
    {
        return;
    }
    int x2 = predator_coo.first;
    int y2 = predator_coo.second;
    if (x2 > x1)
    {
        x1--;
    }
    else if (x2 < x1)
    {
        x1++;
    }
    if (y2 > y1)
    {
        y1--;
    }
    else if (y2 < y1)
    {
        y1++;
    }
    if (M->find(new_coo({x1, y1}, size)) == M->end()) // is_empty(new_coo({x1, y1}), M, size)
    {
        move(new_coo({x1, y1}, size), M, size); // метода мув у нас не будет...
    }
    else
    {
        random_move(M, size); // и этот метод где-то в тике и не метод..
    }
    return;
} // не работает

// BadEntity
std::pair<int, int> BadEntity::get_prey(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size)
{
    // откуда мы возьмем тип жертвы?..
    int x = this->get_position().first;
    int y = this->get_position().second;
    std::pair<int, int> moves[] = {{x, y}, {x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1}, {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1}};
    for (int i = 0; i < 9; ++i)
    {
        moves[i] = new_coo(moves[i], size);
        if (M->find(moves[i]) != M->end() && typeid(M[moves[i]]).name() == "class GoodEntity") // надеюсь тип так сравнится...
        {
            return moves[i];
        }
    }
    return {-1, -1};
} // радиус 1

// Caviar

// BadCarp
std::vector<EntityInterface *> BadCarp::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M)
{
    this->age++;
    if (age >= max_age || random(0, 10000) == 1)
    {
        this->die();
    }
    if (this->is_alive())
    {
        std::pair<int, int> food = this->get_prey(1, M, size);
        std::pair<int, int> where_is_the_next_food = this->get_prey(2, M, size);
        if (food.first != -1)
        {
            return move(food_coo, M, size);
            // kill the food
            kill_it(food_coo);
        }
        else if (where_is_the_next_food.first != -1)
        {
            return move(where_is_the_next_food, M, size);
        }
        else
        {
            int n_move = random(0, 8);
            int X = get_position().first;
            int Y = get_position().second;
            std::pair<int, int> moves[] = {{X, Y}, {X + 1, Y}, {X, Y + 1}, {X - 1, Y}, {X, Y - 1}, {X + 1, Y + 1}, {X - 1, Y - 1}, {X + 1, Y - 1}, {X - 1, Y + 1}};
            for (int i = 0; i < 9; i++, n_move++)
            {
                if (n_move == 9)
                {
                    n_move = 0;
                }
                moves[n_move] = new_coo(moves[n_move], size);
                if (is_empty(moves[n_move], M, size))
                {
                    // do a move
                    return move(moves[n_move], M, size);
                }
            }
        }
    }
    else
    {
        die();
    }
}
// GoodCarp
std::vector<EntityInterface *> GoodCarp::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *)
{
}
// CaviarCarp
std::vector<EntityInterface *> CaviarCarp::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *)
{
}
// Stone
std::vector<EntityInterface *> Stone::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *)
{
}