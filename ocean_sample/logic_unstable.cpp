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

void EntityInterface::set_max_age(int new_max_age){
    max_age = new_max_age;
}

void EntityInterface::die()
{
    this->alive = false;
};

void EntityInterface::change_coo(std::pair<int, int> new_coo)
{
    x = new_coo.first;
    y = new_coo.second;
};

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
    } else if(radius == 2){
        int x = this->get_position().first;
        int y = this->get_position().second;
        std::pair<int, int> moves[] = {{x, y}, {x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1}, {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1},
        {x+1, y+2},{x, y+2},{x-1, y+2},{x+2, y+2},{x-2, y+2},
        {x+2, y-2}, {x+2, y-1}, {x+2, y}, {x+2, y+1}};
        for (int i = 0; i < 18; ++i)
        {
            moves[i] = new_coo(moves[i], size);
            if (M->find(moves[i]) != M->end() && (*M)[moves[i]].type == this->type)
            {
                return 1;
            }
        }
    }
    return 0;
} 

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
    if(radius==1){
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
    }else if(radius == 2){
        int x = this->get_position().first;
        int y = this->get_position().second;
        std::pair<int, int> moves[] = {{x, y}, {x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1}, {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1},
        {x+1, y+2},{x, y+2},{x-1, y+2},{x+2, y+2},{x-2, y+2},
        {x+2, y-2}, {x+2, y-1}, {x+2, y}, {x+2, y+1}};
        for (int i = 0; i < 18; ++i)
        {
            moves[i] = new_coo(moves[i], size);
            if (M->find(moves[i]) != M->end() && (*M)[moves[i]].type == predator_type)
            {
                return moves[i];
            }
        }
    }
    return {-1, -1};
} // работает только в радиусе 1...

bool GoodEntity::fish_in_radius(int radius, std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size)
{

    if(radius == 1){
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
    }else if(radius == 2){
        int x = this->get_position().first;
        int y = this->get_position().second;
        std::pair<int, int> moves[] = {{x, y}, {x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1}, {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1},
        {x+1, y+2},{x, y+2},{x-1, y+2},{x+2, y+2},{x-2, y+2},
        {x+2, y-2}, {x+2, y-1}, {x+2, y}, {x+2, y+1}};
        for (int i = 0; i < 18; ++i)
        {
            moves[i] = new_coo(moves[i], size);
            if (M->find(moves[i]) != M->end() && (*M)[moves[i]].type == predator_type)
            {
                return 1;
            }
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
                break;
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
    if(radius==1){

        std::pair<int, int> moves[] = {{x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1}, {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1}};
        for (int i = 0; i < 8; ++i)
        {
            moves[i] = new_coo(moves[i], size);
            // if (M->find(moves[i]) != M->end() && typeid(*M[moves[i]]).name() == "class BadEntity") // надеюсь тип так сравнится...
            if (M->find(moves[i]) != M->end() && M[moves[i]].first.type == predator_type)
            {
                return moves[i];
            }
             if (canibalism && M->find(moves[i]) != M->end() && M[moves[i]].first.type == this->type)
            {
                return moves[i];
            }
        }
    }else if(radius==2){
        std::pair<int, int> moves[] = {{x + 1, y}, {x, y + 1}, {x - 1, y}, {x, y - 1}, {x + 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}, {x - 1, y + 1}};
        for (int i = 0; i < 8; ++i)
        {
            moves[i] = new_coo(moves[i], size);

            std::pair<int, int> moves2[] = {{moves[i].first + 1, moves[i].second}, {moves[i].first, moves[i].second + 1}, {moves[i].first - 1, moves[i].second}, {moves[i].first, moves[i].second - 1}, {moves[i].first + 1, moves[i].second + 1}, {moves[i].first - 1, moves[i].second - 1}, {moves[i].first + 1, moves[i].second - 1}, {moves[i].first - 1, moves[i].second + 1}};
        for (int j = 0; j < 8; ++j)
        {
            moves2[j] = new_coo(moves2[j], size);
            // if (M->find(moves[i]) != M->end() && typeid(*M[moves[i]]).name() == "class BadEntity") // надеюсь тип так сравнится...
            if (M->find(moves2[j]) != M->end() && M[moves2[j]].first.type == predator_type)
            {
                return moves[i]; // not moves2[j]!!! important moment!!!!
            }
             if (canibalism && M->find(moves2[j]) != M->end() && M[moves2[j]].first.type == this->type)
            {
                return moves[i]; // not moves2[j]!!! important moment!!!!
            }
        }
        }
    }
    return {-1, -1};
} // радиус 1
// work only for a single-type-eaters, change it in future
// we do need it to work with at least radius which is equal to two

Type BadEntity::prey_type()
{
    return this->prey_type;
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
std::vector<EntityInterface *>* *BadCarp::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size)
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
        else if (where_is_the_next_food.first != -1 && M->find(where_is_the_next_food) == M->end()) // the predator has detected a prey
        {
            this->change_coo(new_coo(where_is_the_next_food, size)); // redo it if this->get_prey(2, M, size) dosn't return an adjoining coo
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
std::vector<EntityInterface *>* GoodCarp::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size)
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
            this->change_coo( move_away(M, size)->get_position());
        }
        else if (this->partner_in_range(1, M, size)) 
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
                    //changes.push_back(this);
                    break;
                }
            }
        }
    }
    else
    {
        die();
        //changes.push_back(this);
    }
    return &changes;
}

std::vector<EntityInterface *>* GoodCarp::reproduce(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size)
{
    std::vector<EntityInterface *> children;

    int X = get_position().first;
    int Y = get_position().second;
    std::pair<int, int> moves[] = {{X, Y}, {X + 1, Y}, {X, Y + 1}, {X - 1, Y}, {X, Y - 1}, {X + 1, Y + 1}, {X - 1, Y - 1}, {X + 1, Y - 1}, {X - 1, Y + 1}};
    for (int i = 0; i < 9; i++)
    {
        if (M->find(new_coo(moves[i], size)) == M->end())
        {
            CaviarCarp* child(new_coo(moves[i], size));
            children.push_back(child);
        }
    }
    return children;
} 

// CaviarCarp
std::vector<EntityInterface *>* CaviarCarp::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M, std::pair<int, int> size)
{
    std::vector<EntityInterface *> changes;
    this->age++;
    if (age >= max_age || random(0, 10000) == 1)
    {
        this->die();
        //changes.push_back(this);
        // do not save its own changes in vector
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

// Stone
std::vector<EntityInterface *>* Stone::tick(std::unordered_map<std::pair<int, int>, EntityInterface *, pair_hash> *M)
{
        std::vector<EntityInterface *> changes;
    this->age++;
    if (random(age, max_age) == age )
    {
        this->die();
        //changes.push_back(this);
    } else if(random(0, INT_MAX) == 666){
        //random move
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
                    this->change_coo(new_coo(moves[n_move], size));
                    break;
                } else if (M[(new_coo(moves[n_move], size))] != this->type){
                    M[(new_coo(moves[n_move], size))].second.die();
                    changes(M[(new_coo(moves[n_move], size))].second);
                    this->change_coo(new_coo(moves[n_move], size));
                    break;
                }
            }
    }
    return changes;
}

//Ocean
Ocean::Ocean(std::pair<int, int> new_size, std::vector<std::pair<Type, int>> aumont_of_entities) {
    
    std::vector<std::vector<bool>> lilies(size.first, std::vector<bool>(size.second, (random(0, size.first*size.second/20)==1)));
    WaterlilyMap = lilies;
    size = new_size;
    //aumont_of_entities отсортировать по типу
    for (size_t i = 0; i < aumont_of_entities.size(); i++)
    {
    if(aumont_of_entities[i].first == GOOD_CARP){
        for(int i = 0; i < aumont_of_entities[i].second; i++){
            GoodCarp new_entity({0,0});
            std::pair<int,int> coo = {random(0, size.first), random(0, size.second)};
            while(Entities->map->find(new_coo(coo, size)) != Entities->map->end()){
                coo = {random(0, size.first), random(0, size.second)};
            }
            new_entity.change_coo(coo);
            (*Entities).insert(*new_entity);
        }

    } else if(aumont_of_entities[i].first == CARP_CAVIAR){
        for(int i = 0; i < aumont_of_entities[i].second; i++){
            CaviarCarp new_entity({0,0});
            std::pair<int,int> coo = {random(0, size.first), random(0, size.second)};
            while(Entities->map->find(new_coo(coo, size)) != Entities->map->end()){
                coo = {random(0, size.first), random(0, size.second)};
            }
            new_entity.change_coo(coo);
            (*Entities).insert(*new_entity);
        }

    } else if(aumont_of_entities[i].first == BAD_CARP){
        for(int i = 0; i < aumont_of_entities[i].second; i++){
            BadCarp new_entity({0,0});
            std::pair<int,int> coo = {random(0, size.first), random(0, size.second)};
            while(Entities->map->find(new_coo(coo, size)) != Entities->map->end()){
                coo = {random(0, size.first), random(0, size.second)};
            }
            new_entity.change_coo(coo);
            (*Entities).insert(*new_entity);        }

    } else if(aumont_of_entities[i].first == ROCK){
        for(int i = 0; i < aumont_of_entities[i].second; i++){
            Stone new_entity({0,0});
            std::pair<int,int> coo = {random(0, size.first), random(0, size.second)};
            while(Entities->map->find(new_coo(coo, size)) != Entities->map->end()){
                coo = {random(0, size.first), random(0, size.second)};
            }
            new_entity.change_coo(coo);
            (*Entities).insert(*new_entity);
        }

    } 
    }
} // Я ЗАБЫЛА ЧТО ЭТО ПРИОРИТИКЬЮМЭП, ПЕРЕПИСАТЬ!!!

void Ocean::tick(){
    for (int i = 0; i < this->size.first; i++)
    {
        for(int j = 0; j < this->size.second; j++){
            if(WaterlilyMap[i][j]){
                WaterlilyMap[i][j]==0;
                int X = i;
                int Y = j;
                std::pair<int, int> moves[] = {{X, Y}, {X + 1, Y}, {X, Y + 1}};
                int k = random(0, 2);
                while (WaterlilyMap[moves[k].first][moves[k].second]==1)
                {
                    k = random(0, 2);
                }
            
                WaterlilyMap[moves[k].first][moves[k].second]=1;
                
            }
        }
    }

    PriorityQueueMap* new_map; //?
    while (!this->Entities->empty())
    {
        EntityInterface* cur_entity = this->Entities.top();
        if(!cur_entity->alive){
            this->Entities.pop();
            continue;
        }
        std::vector<EntityInterface *>* changes = cur_entity->tick(*this->Entities->map, this->size);
        for (int i = 0; i < changes->size(); i++)
        {
            new_map.insert(changes[i]);
        }
        if(cur_entity->alive){
            new_map.insert(cur_entity);
            this->Entities.pop();
            continue;
        }
    }
    Entities = new_map;
    

}

std::vector<std::vector<int>>* Ocean::generate_map(){

    std::vector<std::vector<int>> final_map (this->size.first, std::vector<bool>(this->size.second, 0));

    for (int i = 0; i < this->size.first; i++)
    {
        for(int j = 0; j < this->size.second; j++){
            if(WATER == Entities->find({i,j})){
                final_map[i][j]==0;
            }else if(CARP_CAVIAR == Entities->find({i,j})){
                final_map[i][j]==1;
            }else if(GOOD_CARP == Entities->find({i,j})){
                final_map[i][j]==2;
            }else if(BAD_CARP == Entities->find({i,j})){
                final_map[i][j]==3;
            }else if(ROCK == Entities->find({i,j})){
                final_map[i][j]==4;
            }
            if(WaterlilyMap[i][j]){
                final_map[i][j]==5;
            }
        }
    }
    return &final_map;
    
 }





void PriorityQueueMap::insert(Entity *new_entity)
    {
        map.insert({new_entity->get_position(), new_entity->type});
        queue.push(new_entity, new_entity->priority);
    } // вставка нового элемента

void PriorityQueueMap::erase(const T &key)
    {
        queue.erase();
    } /// стереть отовсюду

std::pair<Priority, T> PriorityQueueMap::top()
    {
        Entity *cur_entity = queue.top().first;
    } // вернуть ссылку на объект

void PriorityQueueMap::pop()
    {
        Entity *cur_entity = queue.pop().first;
        // мэп не трогаем, не стираем!!
    } // вернуть верхний и стереть его из очереди

bool PriorityQueueMap::empty()
    {
        return queue.empty();
    } // проверяет пустая ли очередь??

Type PriorityQueueMap::find(std::pair<int, int> coo)
    {
        // вернуть ссылку на объект
        // по коо, те ключу, найти в мэп
        
        if(map.find(coo)==map.end()){
            return WATER;
        } 
        return map[coo];
    }
