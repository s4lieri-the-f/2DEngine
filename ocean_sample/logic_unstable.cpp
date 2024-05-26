#include "logic_unstable.hpp"
#include <climits>

// PriorityQueueMap
template <typename T>
void PriorityQueueMap<T>::insert(T item)
{
    queue.push({item->priority, item});
    map[item->get_position()] = item;
}

template <typename T>
T PriorityQueueMap<T>::top()
{
    if (queue.empty())
    {
        return nullptr;
    }
    auto tmp = queue.top().second;
    return tmp;
} 

template <typename T>
bool PriorityQueueMap<T>::is_empty()
{
    return queue.empty();
}

template <typename T>
void PriorityQueueMap<T>::erase(const T &key)
{
    // Implementation for erase if needed
}

template <typename T>
bool PriorityQueueMap<T>::empty()
{
    return queue.empty();
}

template <typename T>
Type PriorityQueueMap<T>::find(std::pair<int, int> coo)
{
    if (map.find(coo) == map.end())
    {
        return WATER;
    }
    return map[coo]->type;
}

// EntityInterface
std::vector<EntityInterface *> EntityInterface::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &map, std::pair<int, int> size)
{
    std::vector<EntityInterface *> tmp;
    return tmp;
}

std::pair<int, int> EntityInterface::get_position()
{
    return {x, y};
}

bool EntityInterface::is_alive()
{
    return alive;
}

void EntityInterface::set_max_age(int new_max_age)
{
    max_age = new_max_age;
}

void EntityInterface::die()
{
    alive = false;
}

void EntityInterface::change_coo(std::pair<int, int> new_coo)
{
    x = new_coo.first;
    y = new_coo.second;
}

// Fish
bool Fish::partner_in_range(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size)
{
    if (radius == 1)
    {
        int x = this->get_position().first;
        int y = this->get_position().second;
        std::pair<int, int> moves[] = {{x, y}, {x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1}, {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1}};
        for (int i = 0; i < 9; ++i)
        {
            moves[i] = new_coo(moves[i], size);
            if (M.find(moves[i]) != M.end() && M.at(moves[i])->type == this->type)
            {
                return true;
            }
        }
        return false;
    }
    else if (radius == 2)
    {
        int x = this->get_position().first;
        int y = this->get_position().second;
        std::pair<int, int> moves[] = {{x, y}, {x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1}, {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1}, {x + 1, y + 2}, {x, y + 2}, {x - 1, y + 2}, {x + 2, y + 2}, {x - 2, y + 2}, {x + 2, y - 2}, {x + 2, y - 1}, {x + 2, y}, {x + 2, y + 1}};
        for (int i = 0; i < 18; ++i)
        {
            moves[i] = new_coo(moves[i], size);
            if (M.find(moves[i]) != M.end() && M.at(moves[i])->type == this->type)
            {
                return true;
            }
        }
    }
    return false;
}

void Fish::die()
{
    this->alive = false;
}

bool Fish::is_alive()
{
    return alive;
}

// GoodEntity

Type GoodEntity::predator_type()
{
    return predator;
}

std::pair<int, int> GoodEntity::get_predator(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size)
{
    if (radius == 1)
    {
        int x = this->get_position().first;
        int y = this->get_position().second;
        Type predator_type = this->predator_type();

        std::pair<int, int> moves[] = {{x, y}, {x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1}, {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1}};
        for (int i = 0; i < 9; ++i)
        {
            moves[i] = new_coo(moves[i], size);
            if (M.find(moves[i]) != M.end() && M.at(moves[i])->type == predator_type)
            {
                return moves[i];
            }
        }
    }
    else if (radius == 2)
    {
        int x = this->get_position().first;
        int y = this->get_position().second;
        std::pair<int, int> moves[] = {{x, y}, {x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1}, {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1}, {x + 1, y + 2}, {x, y + 2}, {x - 1, y + 2}, {x + 2, y + 2}, {x - 2, y + 2}, {x + 2, y - 2}, {x + 2, y - 1}, {x + 2, y}, {x + 2, y + 1}};
        for (int i = 0; i < 18; ++i)
        {
            moves[i] = new_coo(moves[i], size);
            if (M.find(moves[i]) != M.end() && M.at(moves[i])->type == predator)
            {
                return moves[i];
            }
        }
    }
    return {-1, -1};
}

bool GoodEntity::fish_in_radius(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size)
{
    if (radius == 1)
    {
        int x = this->get_position().first;
        int y = this->get_position().second;
        std::pair<int, int> moves[] = {{x, y}, {x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1}, {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1}};
        for (int i = 0; i < 9; ++i)
        {
            moves[i] = new_coo(moves[i], size);
            if (M.find(moves[i]) != M.end() && M.at(moves[i])->type == type)
            {
                return true;
            }
        }
    }
    else if (radius == 2)
    {
        int x = this->get_position().first;
        int y = this->get_position().second;
        std::pair<int, int> moves[] = {{x, y}, {x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1}, {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1}, {x + 1, y + 2}, {x, y + 2}, {x - 1, y + 2}, {x + 2, y + 2}, {x - 2, y + 2}, {x + 2, y - 2}, {x + 2, y - 1}, {x + 2, y}, {x + 2, y + 1}};
        for (int i = 0; i < 18; ++i)
        {
            moves[i] = new_coo(moves[i], size);
            if (M.find(moves[i]) != M.end() && M.at(moves[i])->type == predator)
            {
                return true;
            }
        }
    }

    return false;
}

GoodEntity *GoodEntity::move_away(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size)
{
    int x1 = this->get_position().first;
    int y1 = this->get_position().second;
    std::pair<int, int> predator_coo = get_predator(1, M, size);
    if (predator_coo.first == -1)
    {
        return nullptr;
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
    if (M.find(new_coo({x1, y1}, size)) == M.end())
    {
        this->change_coo(new_coo({x1, y1}, size));
        return this;
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
            if (M.find(new_coo(moves[n_move], size)) == M.end())
            {
                this->change_coo(new_coo(moves[n_move], size));
                return this;
            }
        }
        return nullptr;
    }
}

std::vector<EntityInterface *> GoodEntity::reproduce(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size)
{
    std::vector<EntityInterface *> children;
    int X = get_position().first;
    int Y = get_position().second;
    std::pair<int, int> moves[] = {{X, Y}, {X + 1, Y}, {X, Y + 1}, {X - 1, Y}, {X, Y - 1}, {X + 1, Y + 1}, {X - 1, Y - 1}, {X + 1, Y - 1}, {X - 1, Y + 1}};
    for (int i = 0; i < 9; i++)
    {
        if (M.find(new_coo(moves[i], size)) == M.end())
        {
            CaviarCarp *child = new CaviarCarp(new_coo(moves[i], size));
            children.push_back(child);
        }
    }
    return children;
}

std::vector<EntityInterface *> GoodEntity::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size)
{
    std::vector<EntityInterface *> changes;
    this->age++;
    if (age >= max_age || random(0, 10000) == 1)
    {
        this->die();
        changes.push_back(this);
    }
    if (this->is_alive())
    {
        std::pair<int, int> predator = this->get_predator(1, M, size);
        std::pair<int, int> where_is_the_next_predator = this->get_predator(2, M, size);
        if (predator.first != -1)
        {
            this->change_coo(move_away(M, size)->get_position());
        }
        else if (this->partner_in_range(1, M, size))
        {
            int X = get_position().first;
            int Y = get_position().second;
            int n_move = random(0, 8);
            std::pair<int, int> moves[] = {{X, Y}, {X + 1, Y}, {X, Y + 1}, {X - 1, Y}, {X, Y - 1}, {X + 1, Y + 1}, {X - 1, Y - 1}, {X + 1, Y - 1}, {X - 1, Y + 1}};
            for (int i = 0; i < 9; i++, n_move++)
            {
                if (n_move == 9)
                {
                    n_move = 0;
                }
                moves[n_move] = new_coo(moves[n_move], size);
                if (M.find(new_coo(moves[n_move], size)) == M.end())
                {
                    CaviarCarp *child = new CaviarCarp(new_coo(moves[n_move], size));
                    changes.push_back(child);
                }
            }
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
                if (M.find(new_coo(moves[n_move], size)) == M.end())
                {
                    this->change_coo(new_coo(moves[n_move], size));
                    break;
                }
            }
        }
    }
    else
    {
        die();
    }
    return changes;
}

// BadEntity
std::vector<EntityInterface *> BadEntity::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size)
{
    std::vector<EntityInterface *> changes;
    this->age++;
    if (age >= max_age || random(0, 10000) == 1)
    {
        this->die();
        changes.push_back(this);
    }
    if (this->is_alive())
    {
        std::pair<int, int> food = this->get_prey(1, M, size);
        std::pair<int, int> where_is_the_next_food = this->get_prey(2, M, size);
        if (food.first != -1)
        {
            this->change_coo(new_coo(food, size));
            changes.push_back(this);
            M.at(food)->die();
            changes.push_back(M.at(food));
        }
        else if (where_is_the_next_food.first != -1 && M.find(where_is_the_next_food) == M.end())
        {
            this->change_coo(new_coo(where_is_the_next_food, size));
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
                if (M.find(new_coo(moves[n_move], size)) == M.end())
                {
                    this->change_coo(new_coo(moves[n_move], size));
                    break;
                }
            }
        }
    }
    else
    {
        die();
        changes.push_back(this);
    }
    return changes;
}

// Caviar
std::vector<EntityInterface *> Caviar::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size)
{
    std::vector<EntityInterface *> changes;
    this->age++;
    if (age >= max_age || random(0, 10000) == 1)
    {
        this->die();
    }
    else if (age >= this->evolution_age)
    {
        std::vector<std::pair<int, int>> *f_pos = this->evolve(M, size);
        for (size_t i = 0; i < f_pos->size(); i++)
        {
            GoodCarp *new_carp = new GoodCarp(f_pos->at(i));
            changes.push_back(new_carp);
        }
    }
    return changes;
}

// BadCarp
std::vector<EntityInterface *> BadCarp::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size)
{
    std::vector<EntityInterface *> changes;
    this->age++;
    if (age >= max_age || random(0, 10000) == 1)
    {
        this->die();
        changes.push_back(this);
    }
    if (this->is_alive())
    {
        std::pair<int, int> food = this->get_prey(1, M, size);
        std::pair<int, int> where_is_the_next_food = this->get_prey(2, M, size);
        if (food.first != -1)
        {
            this->change_coo(new_coo(food, size));
            changes.push_back(this);
            M.at(food)->die();
            changes.push_back(M.at(food));
        }
        else if (where_is_the_next_food.first != -1 && M.find(where_is_the_next_food) == M.end())
        {
            this->change_coo(new_coo(where_is_the_next_food, size));
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
                if (M.find(new_coo(moves[n_move], size)) == M.end())
                {
                    this->change_coo(new_coo(moves[n_move], size));
                    break;
                }
            }
        }
    }
    else
    {
        die();
        changes.push_back(this);
    }
    return changes;
}

// GoodCarp
std::vector<EntityInterface *> GoodCarp::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size)
{
    std::vector<EntityInterface *> changes;
    this->age++;
    if (age >= max_age || random(0, 10000) == 1)
    {
        this->die();
        changes.push_back(this);
    }
    if (this->is_alive())
    {
        std::pair<int, int> predator = this->get_predator(1, M, size);
        std::pair<int, int> where_is_the_next_predator = this->get_predator(2, M, size);
        if (predator.first != -1)
        {
            this->change_coo(move_away(M, size)->get_position());
        }
        else if (this->partner_in_range(1, M, size))
        {
            int X = get_position().first;
            int Y = get_position().second;
            int n_move = random(0, 8);
            std::pair<int, int> moves[] = {{X, Y}, {X + 1, Y}, {X, Y + 1}, {X - 1, Y}, {X, Y - 1}, {X + 1, Y + 1}, {X - 1, Y - 1}, {X + 1, Y - 1}, {X - 1, Y + 1}};
            for (int i = 0; i < 9; i++, n_move++)
            {
                if (n_move == 9)
                {
                    n_move = 0;
                }
                moves[n_move] = new_coo(moves[n_move], size);
                if (M.find(new_coo(moves[n_move], size)) == M.end())
                {
                    CaviarCarp *child = new CaviarCarp(new_coo(moves[n_move], size));
                    changes.push_back(child);
                }
            }
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
                if (M.find(new_coo(moves[n_move], size)) == M.end())
                {
                    this->change_coo(new_coo(moves[n_move], size));
                    break;
                }
            }
        }
    }
    else
    {
        die();
    }
    return changes;
}

std::vector<EntityInterface *> GoodCarp::reproduce(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size)
{
    std::vector<EntityInterface *> children;
    int X = get_position().first;
    int Y = get_position().second;
    std::pair<int, int> moves[] = {{X, Y}, {X + 1, Y}, {X, Y + 1}, {X - 1, Y}, {X, Y - 1}, {X + 1, Y + 1}, {X - 1, Y - 1}, {X + 1, Y - 1}, {X - 1, Y + 1}};
    for (int i = 0; i < 9; i++)
    {
        if (M.find(new_coo(moves[i], size)) == M.end())
        {
            CaviarCarp *child = new CaviarCarp(new_coo(moves[i], size));
            children.push_back(child);
        }
    }
    return children;
}

// CaviarCarp
std::vector<EntityInterface *> CaviarCarp::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size)
{
    std::vector<EntityInterface *> changes;
    this->age++;
    if (age >= max_age || random(0, 10000) == 1)
    {
        this->die();
    }
    else if (age >= this->evolution_age)
    {
        std::vector<std::pair<int, int>> *f_pos = this->evolve(M, size);
        for (size_t i = 0; i < f_pos->size(); i++)
        {
            GoodCarp *new_carp = new GoodCarp(f_pos->at(i));
            changes.push_back(new_carp);
        }
    }
    return changes;
}

// Stone
std::vector<EntityInterface *> Stone::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> &M, std::pair<int, int> size)
{
    std::vector<EntityInterface *> changes;
    this->age++;
    if (random(age, max_age) == age)
    {
        this->die();
    }
    else if (random(0, 10000) == 666)
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
            if (M.find(new_coo(moves[n_move], size)) == M.end())
            {
                this->change_coo(new_coo(moves[n_move], size));
                break;
            }
            else if (M.at(new_coo(moves[n_move], size))->type != this->type)
            {
                M.at(new_coo(moves[n_move], size))->die();
                changes.push_back(M.at(new_coo(moves[n_move], size)));
                this->change_coo(new_coo(moves[n_move], size));
                break;
            }
        }
    }
    return changes;
}

// Ocean
Ocean::Ocean(std::pair<int, int> new_size)
{
    size = new_size;
    std::vector<std::vector<bool>> lilies(size.first, std::vector<bool>(size.second, (random(0, size.first * size.second / 20) == 1)));
    WaterlilyMap = lilies;
}

void Ocean::tick()
{
    for (int i = 0; i < size.first; i++)
    {
        for (int j = 0; j < size.second; j++)
        {
            if (WaterlilyMap[i][j])
            {
                WaterlilyMap[i][j] = 0;
                int X = i;
                int Y = j;
                std::pair<int, int> moves[] = {{X, Y}, {X + 1, Y}, {X, Y + 1}};
                int k = random(0, 2);
                while (WaterlilyMap[moves[k].first][moves[k].second] == 1)
                {
                    k = random(0, 2);
                }

                WaterlilyMap[moves[k].first][moves[k].second] = 1;
            }
        }
    }

    PriorityQueueMap<EntityInterface *> new_map;
    while (!Entities.empty())
    {
        auto cur_entity_pair = Entities.top();
        auto cur_entity = cur_entity_pair;
        if (!cur_entity->is_alive())
        {
            Entities.queue.pop();
            continue;
        }
        auto changes = cur_entity->tick(Entities.map, size);
        for (size_t i = 0; i < changes.size(); i++)
        {
            new_map.insert(changes[i]);
        }
        if (cur_entity->is_alive())
        {
            new_map.insert(cur_entity);
        }
        Entities.queue.pop();
    }
    Entities = new_map;
}

std::vector<std::vector<int>> Ocean::generate_map()
{
    std::vector<std::vector<int>> final_map(std::vector<std::vector<int>>(size.first, std::vector<int>(size.second, 0)));
    for (int i = 0; i < size.first; i++)
    {
        for (int j = 0; j < size.second; j++)
        {
            if (Entities.find({i, j}) == WATER)
            {
                (final_map)[i][j] = 0;
            }
            else if (Entities.find({i, j}) == CARP_CAVIAR)
            {
                (final_map)[i][j] = 1;
            }
            else if (Entities.find({i, j}) == GOOD_CARP)
            {
                (final_map)[i][j] = 2;
            }
            else if (Entities.find({i, j}) == BAD_CARP)
            {
                (final_map)[i][j] = 3;
            }
            else if (Entities.find({i, j}) == ROCK)
            {
                (final_map)[i][j] = 4;
            }
            if (WaterlilyMap[i][j])
            {
                (final_map)[i][j] = 5;
            }
        }
    }
    return final_map;
}
