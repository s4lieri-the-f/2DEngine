#include "./logic_unstable.hpp"

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
};

bool EntityInterface::alive()
{
    return alive;
};

void EntityInterface::die()
{
    this->alive = false;
};

void EntityInterface::change_coo(std::pair<int, int> new_coo)
{
    x = new_coo.first;
    y = new_coo.second;
};

EntityInterface *die_of_old_age()
{
    if (age > max_age)
    {
        raturn die(); // redo it
    }
    return nullptr;
} // useless function, delete it later

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
} // only for radius == 1

void Fish::die()
{
    this->die();
} // сомнительно

bool Fish::is_alive()
{
    return this->alive();
} // не работает

EntityInterface *Fish::reproduce()
{
    return nullptr; // по умолчанию nullptr
}

// GoodEntity

Type predator_type()
{
    return this->predator_type;
}

std::pair<int, int> GoodEntity::get_predator(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size)
{
    // откуда мы возьмем тип хищника?..
    // tenporary predators type is contained by a prey

    int x = this->get_position().first;
    int y = this->get_position().second;
    Type predator_type = this->predator_type();

    std::pair<int, int> moves[] = {{x, y}, {x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1}, {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1}};
    for (int i = 0; i < 9; ++i)
    {
        moves[i] = new_coo(moves[i], size);
        // if (M->find(moves[i]) != M->end() && typeid(*M[moves[i]]).name() == "class BadEntity") // надеюсь тип так сравнится...
        if (M->find(moves[i]) != M->end() && M[moves[i]].first.type == predator_type)
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

GoodEntity *GoodEntity::move_away(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size)
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
    if (M->find(new_coo({x1, y1})) == M->end()) // is_empty(new_coo({x1, y1}), M, size)
    {
        // move(new_coo({x1, y1}, size), M, size); // метода мув у нас не будет...
        this->change_coo(new_coo({x1, y1}, size));
        return this;
    }
    else
    {

        // randomly
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
            if (M->find(new_coo(moves[n_move], size)) == M->end())
            {
                // do a move
                this->change_coo(new_coo(moves[n_move], size));
                return this;
            }
        }
        return nullptr;
    }
    return nullptr;
} // work only for a single-eatable preys

std::vector<EntityInterface *> GoodEntity::reproduce(std::pair<int, int> size)
{
    std::vector<EntityInterface *> children;

    int X = get_position().first;
    int Y = get_position().second;
    std::pair<int, int> moves[] = {{X, Y}, {X + 1, Y}, {X, Y + 1}, {X - 1, Y}, {X, Y - 1}, {X + 1, Y + 1}, {X - 1, Y - 1}, {X + 1, Y - 1}, {X - 1, Y + 1}};
    for (int i = 0; i < 9; i++)
    {
        if (M->find(new_coo(moves[i], size)) == M->end())
        {
            this->change_coo(new_coo(moves[i], size));
            children.push_back(this);
        }
    }
    this->change_coo(new_coo({X, Y}, size));
    return children;
} // only creates a clones of itself (entities of the same type), dosn't check its requirement to reproduce

// BadEntity
std::pair<int, int> BadEntity::get_prey(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size)
{
    Type predator_type = this->prey_type();
    int x = get_position().first;
    int y = get_position().second;
    std::pair<int, int> moves[] = {{x, y}, {x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1}, {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1}};
    for (int i = 0; i < 9; ++i)
    {
        moves[i] = new_coo(moves[i], size);
        // if (M->find(moves[i]) != M->end() && typeid(*M[moves[i]]).name() == "class BadEntity") // надеюсь тип так сравнится...
        if (M->find(moves[i]) != M->end() && M[moves[i]].first.type == predator_type)
        {
            return moves[i];
        }
    }
    return {-1, -1};
} // радиус 1
// work only for a single-type-eaters, change it in future
// we do need it to work with at least radius which is equal to two

Type BadEntity::prey_type()
{
    return prey_type;
}

// Caviar

std::vector<std::pair<int, int>> *Caviar::evolve(std::pair<int, int> size)
{

    std::vector<std::pair<int, int>> evolve_pos;

    // randomly
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
        if (M->find(new_coo(moves[n_move], size)) == M->end())
        {
            evolve_pos.push_back(new_coo(moves[n_move], size));
        }
    }
    return &evolve_pos;
}

// BadCarp
std::vector<EntityInterface *> *BadCarp::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size)
{
    std::vector<EntityInterface *> changes;
    this->age++;
    if (age >= max_age || random(0, 10000) == 1)
    {
        this->die();
        // return nullptr; //? should we return the dead entity?
        changes.push_back(this);
    }
    // or this->die_of_old_age();
    if (this->is_alive())                                                        // well, this checking dosn't make any sence coz we've already used the return thing...
    {                                                                            // oh, i'm wrong, the fish can be killed by a something else exept its age as well as by the old death
        std::pair<int, int> food = this->get_prey(1, M, size);                   // would return {-1, -1} if there wasn't any food in radius, which is one by the way
        std::pair<int, int> where_is_the_next_food = this->get_prey(2, M, size); // same as previous, but the radious here is higher, it's two this time
        if (food.first != -1)                                                    // that means that the food is somewhere in adjoining cells
        {
            this->change_coo(new_coo(food, size));
            changes.push_back(this);
            (*M)[food].first->die(); // killing food
            changes.push_back((*M)[food].first);
        }
        else if (where_is_the_next_food.first != -1) // the predator has detected a prey
        {
            this->change_coo(new_coo(where_is_the_next_food, size)); // redo it if this->get_prey(2, M, size) dosn't return an adjoining coo
            changes.push_back(this);
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
                if (M->find(new_coo(moves[n_move], size)) == M->end())
                {
                    // do a random move
                    this->change_coo(new_coo(moves[n_move], size));
                    changes.push_back(this);
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
    return &changes;
}
// GoodCarp
std::vector<EntityInterface *> GoodCarp::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size)
{
    std::vector<EntityInterface *> changes;
    this->age++;
    if (age >= max_age || random(0, 10000) == 1)
    {
        this->die();
        changes.push_back(this);
    }
    // or this->die_of_old_age();
    if (this->is_alive())
    {
        std::pair<int, int> predator = this->get_predator(1, M, size);                   // would return {-1, -1} if there wasn't any danger in radius, which is one by the way
        std::pair<int, int> where_is_the_next_predator = this->get_predator(2, M, size); // same as previous, but the radious here is higher, it's two this time

        if (predator.first != -1) // that means that the food is somewhere in adjoining cells
        {
            changes.push_back(move_away(M, size));
        }
        else if (this->partner_in_range(1, M, size)) // the predator has detected a prey
        {
            // create a caviar
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
                if (M->find(new_coo(moves[n_move], size)) == M->end())
                {
                    // do a random move
                    CaviarCarp child(new_coo(moves[n_move], size));
                    changes.push_back(*child);
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
                if (M->find(new_coo(moves[n_move], size)) == M->end())
                {
                    // do a random move
                    this->change_coo(new_coo(moves[n_move], size));
                    changes.push_back(this);
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
    return &changes;
}

// CaviarCarp
std::vector<EntityInterface *> CaviarCarp::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size)
{
    std::vector<EntityInterface *> changes;
    this->age++;
    if (age >= max_age || random(0, 10000) == 1)
    {
        this->die();
        changes.push_back(this);
    }
    else if (age >= this->evolution_age)
    {
        std::vector<std::pair<int, int>> f_pos = *(this->evolve(M, size));
        for (i = 0; i < f_pos.size(); i++)
        {
            GoodCarp new_carp(f_pos[i]);
            changes.push_back(new_carp);
        }
    }
    // too young for being able to move
    return changes;
}
{
}
// Stone
std::vector<EntityInterface *> Stone::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M)
{
}