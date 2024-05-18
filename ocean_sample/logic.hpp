#include <vector>
#include <queue>
#include <unordered_map>
#include <future>
#include <ctime>

/*
 *
 * kill_it(coo) для существа по координате - не работает
 *
 * kill_it для entity и kill_it для ocean, который был перенесен в entity наложились друг на друга, один из них переименовать и написать
 *
 * вызов add_f_entity() из методов Entity заменить на возврат Entity* из tick()
 *
 * в некоторых методах нужно вернуть больше одного Entity*
 *
 * добавить передачу map и size в методы всех Entity (чтоб нормально работало)
 *
 */




int random(int s, int f){
    int range = f-s+1;
    return (std::clock() % range + s);

}


enum Type
{
    WATER, //yeah, we need a lot of water
    GOOD_CARP, //some kind od a fish BUT IT'S DIFFERENT IT'S BETTER
    CARP_CAVIAR, //idk maybe i should make it like a part of карпик? it's like newborn carps
    WATER_LILY, // can do nothing, just exists
    ROCK, // can do nothing, but no one can move through it
    //SHRIMP, // they are really fast, can't attack you, harmless creatures
    BAD_CARP, // it's the most aggressive fish in the ocean
    PLAYER ///???


};

enum Priority //we need it for queue
{
    LOW,
    MEDIUM,
    HIGH,
    LILY
};

class Entity{ // fishes, animals, stones, etc
    int alive{1}; // по умолчанию существо живо
    int x, y; // ok, it's like coordinates

public:

    Type type;
    Priority priority;

    void kill_it(){
        alive = 0;
    }; //смерть, без взаимодействия с океаном

    bool is_dead(){ // проверка на мертвость
        return !alive;
    };

    Entity(int x, int y, Type type) : x(x), y(y), type(type){}; // create new ocean being

    std::pair<int, int> get_position() { // возвращение координат в океане
        return {x, y};
    };

    virtual Entity* tick(std::unordered_map<std::pair<int, int>, Entity>* M) = 0; // update a life cycle

    ~Entity(); //wipe it off the face of ocean



    bool is_empty(std::pair<int, int> coo, std::unordered_map<std::pair<int, int>, Entity>* M); //проверка клетки на пустоту (нет Entity по координате)


    bool in_fild(std::pair<int, int> coo, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size); //проверка принадлежит ли координата полю

    bool comp_cage(Type t, std::pair<int, int> coo, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size); // проверка тот ли тип, что нас интерисует лежит по координате

    std::pair<int, int> find_empty_near_this(std::pair<int, int> coo, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size); // находит первую пустую клетку по соседству с заданной координатой

    std::pair<int, int> find_type_near_this(Type type, std::pair<int, int> coo, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size); //найти конкретный тип близь заданной координаты

    std::pair<int, int> new_coo(std::pair<int, int> coo, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size); //переделывает координаты за пределами поля в корректные (принадлежащие полю)

    Type check_who_is_there(std::pair<int, int> coo, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size); //возвращает, какой тип лежит по запрашиваемой координате

};

template <typename T, typename Priority> class PriorityQueueMap{

    auto static cmp = [](std::pair<T, Priority> a, std::pair<T, Priority> b) {return a.second > b.second;};
    std::priority_queue<std::pair<T, Priority>, std::vector<std::pair<T, Priority>, cmp>> queue; // очередь из пар (Entity и его приоритет), отсортированная по приоритетам

    ///при чем там вектор в priority_queue?
public:

    std::unordered_map<std::pair<int, int>, T> map; //мэп, где по ключам(координатам) лежат Entity
    //T = Entity?

    PriorityQueueMap();

    ~PriorityQueueMap();

    void insert(Entity* new_entity){
        map.insert({new_entity->get_position(), new_entity->type});
        queue.push(new_entity, new_entity->priority);
    }// вставка нового элемента


    void erase(const T &key){
        //а зачем нам этот метод? он вообще всю очередь очищает?
        queue.erase();
    }/// стереть отовсюду???

    std::pair<Priority, T> top(){
        Entity* cur_entity = queue.top().first;
    }// вернуть ссылку на объект

    void pop(){
        Entity* cur_entity = queue.pop().first;
        //мэп не трогаем, не стираем!!
    }// вернуть верхний и стереть его из очереди

    bool empty(){
        return queue.empty();
    } // проверяет пустая ли очередь??

    Type find(std::pair<int, int> coo){
        // вернуть ссылку на объект
        // по коо, те ключу, найти в мэп
        return *map[coo];
    }


}; ///

class Ocean{

    std::pair<int, int> size; //the size of ocean
    PriorityQueueMap<Entity, Priority> entities; //all entities and their priorities
    std::vector<std::pair<int, int>> water_lily_coo; //list of lilies coordinates
    Ocean* future_ocean; ///temporary solution
    ///rewrite everything on swapping PriorityQueueMaps instead of creating a new ocean every time

public:

    void create_water_lily();

    void create_entities();

    Ocean(int x, int y) : size(std::make_pair(x, y)) {
        entities = new PriorityQueueMap<std::pair<Entity, int>, Priority>();
        //при условии, что океан создается только единожды!!
        create_water_lily(); // создаем рандомно лилии на поле
        create_entities();
    }; //the start of the world

    Ocean(int x, int y, std::vector<std::pair<int, int>>* old_water_lily_coo ) : size(std::make_pair(x, y)), water_lily_coo(*old_water_lily_coo) {
        entities = new PriorityQueueMap<std::pair<Entity, int>, Priority>();
    }; //конструктор для будущего океана

    void add_f_entity(Entity* entity){
        ((Ocean*)future_ocean)->entities.insert(entity);
        //add here an adding algorithm for a queue

    } // добавление энтити в будущий океан

    std::pair<int, int> new_coo(std::pair<int, int> coo){

        if(coo.first>this->size.first){
            coo.first%=size.first;
        }
        while(coo.first<0){
            coo.first+=size.first;
        }
        if(coo.second>this->size.second){
            coo.second%=size.second;
        }
        while(coo.second<0){
            coo.second+=size.second;
        }
        return coo;
    } //переделывает координаты за пределами поля в корректные (принадлежащие полю)


    void water_lily_movement(){
        for (int i = 0; i < water_lily_coo.size(); ++i) {
            water_lily_coo[i]={water_lily_coo[i].first + random(0,1),water_lily_coo[i].second + random(0,1)};
            water_lily_coo[i]=new_coo(water_lily_coo[i]);
        }
    } //движение кувшинок


    void tick(){
        water_lily_movement();
        future_ocean = new Ocean(size.first, size.second, &water_lily_coo); // переделать
        while (!entities.empty()){
            entities.pop().tick(this); //они сами себя добавляют в будующий океан
        }
        entities=future_ocean->entities;
    } //тик жизни океана

    Type** get_grid(){

        Type ** pond = new Type*[size.first];
        for(size_t i = 0; i < size.first; ++i) pond[i] = new Type[size.second];

        for (int i = 0; i < size.first; ++i) {
            for (int j = 0; j < size.second; ++j) {
                pond[i][j] = WATER;
            }
        }
        while (!entities.empty()){
            Entity* tmp_entity = (*(Ocean*)future_ocean).entities.pop();
            pond[tmp_entity->get_position().first][tmp_entity->get_position().second] = tmp_entity->type;
        }
        for (int i = 0; i < water_lily_coo.size(); ++i) {
            pond[(*(Ocean*)future_ocean).water_lily_coo[i].first][(*(Ocean*)future_ocean).water_lily_coo[i].second]=WATER_LILY;
        }
        return pond;
    }// Построение карты для отправки Ксюшe

    ~Ocean(){} // деструктор

    bool is_empty(std::pair<int, int> coo){
        // check if the cage is empty
        if(((Ocean*)future_ocean)->entities.find(coo) == WATER){ // != carp or caviar or stone or...
            return 1;
        } return 0;
    } //проверка клетки на пустоту (нет Entity по координате)



    ///
/*
    bool is_empty(std::pair<int, int> coo){
        // check if the cage is empty
        if(((Ocean*)future_ocean)->entities.find(coo) == WATER){ // != carp or caviar or stone or...
            return 1;
        } return 0;
    } //проверка клетки на пустоту (нет Entity по координате)


    bool in_fild(std::pair<int, int> coo){
        if(coo.first >= 0 && coo.second >= 0 && coo.first < size.first && size.second > coo.second){
            return 1;
        } return 0;
    } //проверка принадлежит ли координата полю

    bool comp_cage(Type t, std::pair<int, int> coo){
        if(entities.find(coo).second==t){ ///
            return 1;
        } else {
            return 0;
        }
    } // проверка тот ли тип, что нас интерисует лежит по координате

    std::pair<int, int> find_empty_near_this(std::pair<int, int> coo){
        int x = coo.first;
        int y = coo.second;
        std::pair<int, int> moves[] = {{x, y}, {x+1, y}, {x, y+1}, {x-1, y}, {x, y-1}, {x+1, y+1}, {x-1, y-1}, {x+1, y-1}, {x-1, y+1}};

        for (int i = 0; i < 9; ++i) {
            moves[i]= new_coo(moves[i]);
            if(this->is_empty(moves[i])){
                return moves[i];
            }

        }

        return {-1, -1}; //there isn't any empty space near our coo
    } // находит первую пустую клетку по соседству с заданной координатой

    std::pair<int, int> find_type_near_this(Type type, std::pair<int, int> coo){
        int x = coo.first;
        int y = coo.second;
        std::pair<int, int> moves[] = {{x, y}, {x+1, y}, {x, y+1}, {x-1, y}, {x, y-1}, {x+1, y+1}, {x-1, y-1}, {x+1, y-1}, {x-1, y+1}};
        for (int i = 0; i < 9; ++i) {
            if(in_fild(moves[i])){
                if(entities.find(moves[i]).second == type){
                    return moves[i];
                }
            }
        }
        return {-1, -1}; //there isn't any
    } //найти конкретный тип близь заданной координаты

    std::pair<int, int> new_coo(std::pair<int, int> coo){
        if(in_fild(coo)){
            return coo;
        }
        if(coo.first>this->size.first){
            coo.first%=size.first;
        }
        while(coo.first<0){
            coo.first+=size.first;
        }
        if(coo.second>this->size.second){
            coo.second%=size.second;
        }
        while(coo.second<0){
            coo.second+=size.second;
        }
        return coo;
    } //переделывает координаты за пределами поля в корректные (принадлежащие полю)


    Type check_who_is_there(std::pair<int, int> coo){
        return entities.find(coo).second;
    } //возвращает, какой тип лежит по запрашиваемой координате

    std::pair<int, int> kill_it(std::pair<int, int> coo){
        entities.find(coo).second.kill_it();
    } //переключает показатель жизни внутри существа по координате на смерть
    */
};








bool Entity::is_empty(std::pair<int, int> coo, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
    // check if the cage is empty
    return M.contains(coo);
} //проверка клетки на пустоту (нет Entity по координате)


bool Entity::in_fild(std::pair<int, int> coo, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
    if(coo.first >= 0 && coo.second >= 0 && coo.first < size.first && size.second > coo.second){
        return 1;
    } return 0;
} //проверка принадлежит ли координата полю

bool Entity::comp_cage(Type t, std::pair<int, int> coo, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
    if((this->in_fild(coo, M, size) && (M[coo]).type==t)){ ///
        return 1;
    } else {
        return 0;
    }
} // проверка тот ли тип, что нас интерисует лежит по координате

std::pair<int, int> Entity::find_empty_near_this(std::pair<int, int> coo, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
    int x = coo.first;
    int y = coo.second;
    std::pair<int, int> moves[] = {{x, y}, {x+1, y}, {x, y+1}, {x-1, y}, {x, y-1}, {x+1, y+1}, {x-1, y-1}, {x+1, y-1}, {x-1, y+1}};

    for (int i = 0; i < 9; ++i) {
        moves[i]= new_coo(moves[i], M, size);
        if(this->is_empty(moves[i], M, size)){
            return moves[i];
        }
    }
    return {-1, -1}; //there isn't any empty space near our coo
} // находит первую пустую клетку по соседству с заданной координатой

std::pair<int, int> Entity::find_type_near_this(Type type, std::pair<int, int> coo, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
    int x = coo.first;
    int y = coo.second;
    std::pair<int, int> moves[] = {{x, y}, {x+1, y}, {x, y+1}, {x-1, y}, {x, y-1}, {x+1, y+1}, {x-1, y-1}, {x+1, y-1}, {x-1, y+1}};
    for (int i = 0; i < 9; ++i) {
        if(in_fild(moves[i], std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size)){
            if(comp_cage(type, moves[i], M, size)){
                return moves[i];
            }
        }
    }
    return {-1, -1}; //there isn't any
} //найти конкретный тип близь заданной координаты

std::pair<int, int> Entity::new_coo(std::pair<int, int> coo, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
    if(in_fild(coo, M, size)){
        return coo;
    }
    if(coo.first>size.first){
        coo.first%=size.first;
    }
    while(coo.first<0){
        coo.first+=size.first;
    }
    if(coo.second>size.second){
        coo.second%=size.second;
    }
    while(coo.second<0){
        coo.second+=size.second;
    }
    return coo;
} //переделывает координаты за пределами поля в корректные (принадлежащие полю)


Type Entity::check_who_is_there(std::pair<int, int> coo, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
    if (is_empty(coo, M, size)){
        return WATER;
    }
    return M[coo];
} //возвращает, какой тип лежит по запрашиваемой координате


















void Ocean::create_water_lily(){
    int amount = random(size.first*size.second/(20), size.first*size.second/(10));
    bool arr[size.first][size.second];
    for (int i = 0; i <size.first; ++i) {
        for (int j = 0; j <size.second; ++j) {
            arr[i][j]=1;
        }
    }
    for (int i = 0; i < amount; ++i) {
        std::pair<int, int> coo = {random(0, size.first-1), random(0, size.second-1)};
        while(arr[coo.first][coo.second]){
            coo = {random(0, size.first-1), random(0, size.second-1)};
        }
        arr[coo.first][coo.second]=0;
        water_lily_coo.push_back(coo);
    }
} // water lily generation


class caviar_carp: public Entity{
    int age;
    int max_age{20};
    int waiting_time{0};
    int max_waiting_time{2};

public:


    caviar_carp(int x, int y) : Entity(x, y, CARP_CAVIAR) {
        age=0;
        this->priority=LOW;
    }

    caviar_carp(int x, int y, int a, int w) : Entity(x, y, CARP_CAVIAR) {
        age=a;
        waiting_time = w;
        this->priority=LOW;
    }

    bool find_adults(std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
        if(find_type_near_this(GOOD_CARP, this->get_position(), M, size).first != -1){
            waiting_time++;
            return 0;
        } else {
            waiting_time = 0;
            return 1;
        }
    }

    ~caviar_carp() {

    }

    void die(){

        this->kill_it(this->get_position());

    }

    void die_if_you_should(){
        if(waiting_time > max_waiting_time){
            die();
        }
    } //ok

    void evolution(std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size);

    virtual Entity* tick(std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
        age++;
        find_adults( M,  size);
        die_if_you_should();
        evolution( M,  size);
        if(this->is_dead()){
            die();
            return nullptr;
        }
        caviar_carp* new_caviar = new caviar_carp(this->get_position().first, this->get_position().second, age, waiting_time);
        return new_caviar;
    }
}; //икра карпов

class good_carp : public Entity
{
    int max_age{100};
    int max_l_years{20};

    int l_years{0};
    int age;

public:
/*
    good_carp(int x, int y) : Entity(x, y, GOOD_CARP) {
        age = 0;
        this->priority=LOW;
    }//все ок
*/
    good_carp(std::pair<int, int> coo) : Entity(coo.first, coo.second, GOOD_CARP) {
        age = 0;
        this->priority=LOW;
    }//все ок

    good_carp(int x, int y, int a, int l) : Entity(x, y, GOOD_CARP) {
        age = a;
        l_years = l;
        this->priority=LOW;
    }//все ок

    std::pair<int, int> partner_is_near(std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){ //only good_carp can be a partner
        return find_type_near_this(this->type, this->get_position(), M, size);
    }//все ок

    bool no_friend_is_near(std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
        // check the circle around this carp
        // all carps are friends of good ones
        if(find_type_near_this(this->type, this->get_position(), M, size).first==-1 && find_type_near_this(BAD_CARP, this->get_position(), M, size).first != -1){
            return 1;
        } return 0;

    }//все ок

    virtual ~good_carp() {
        // как деструктор писать ааааааааааа
    } //тут нет нихуя внутри

    void die(){
        kill_it();

    }///delete from ocean - нет удаления с океана

    void die_if_you_should(){
        if(age >= max_age || l_years >= max_l_years){
            this->die();
        }
    }

    void fate(){
        if(random(0, 1000000) == 1){
            this->die(); //that's your fate
        }
    }

    //std::pair<int, int>
    Entity* reproduce(std::pair<int, int> parent_2, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){ // use coo

        std::pair<int, int> child_coo = find_empty_near_this(this->get_position(), std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size);

        if(child_coo.first==-1){
            child_coo = find_empty_near_this(parent_2, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size);
        }
        if(child_coo.first==-1){
            //don't let them born there is no space
            return child_coo;
        }
        //create new object - caviar
        if(child_coo.first!=-1){
            caviar_carp* child = new caviar_carp(child_coo.first, child_coo.second);
            //add_f_entity((Entity*)child); ///
            return child;
        }
        return nullptr;

    } /// создание икры без add_f_entity((Entity*)child) не работает

    Entity* move(std::pair<int, int> coo, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
        good_carp* new_carp = new good_carp(this->get_position().first, this->get_position().second, age, l_years);
        return new_carp;
    }

    Entity* random_move(std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
        //randomly
        int n_move = random(0, 8);
        int X = get_position().first;
        int Y = get_position().second;
        std::pair<int, int> moves[] = {{X, Y}, {X+1, Y}, {X, Y+1}, {X-1, Y}, {X, Y-1}, {X+1, Y+1}, {X-1, Y-1}, {X+1, Y-1}, {X-1, Y+1} };
        for(int i = 0; i < 9; i++, n_move++){
            if(n_move==9){
                n_move=0;
            }
            if(in_fild(moves[n_move],  M, size) && is_empty(moves[n_move], M, size)){
                //do a move
                return move(moves[i],  M,  size);
            }
        }
        return nullptr;
    } //все ок

    std::pair<int, int> where_is_predator(std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
        int X = get_position().first;
        int Y = get_position().second;
        std::pair<int, int> moves[] = {{X+1, Y+1}, {X-1, Y-1}, {X+1, Y-1}, {X-1, Y+1}};
        for (int i = 0; i < 4; ++i) {
            if(find_type_near_this(BAD_CARP, moves[i]).first != -1){
                return moves[i];
            }
        }
        return {-1, -1};
    } //все ок

    Entity* move_away(std::pair<int, int> predator_coo, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
        int x1 = get_position().first;
        int y1 = get_position().second;
        int x2 = predator_coo.first;
        int y2 = predator_coo.second;
        if(x2>x1){
            x1--;
        } else if(x2<x1){
            x1++;
        }
        if(y2>y1){
            y1--;
        } else if(y2<y1){
            y1++;
        }
        if(is_empty(new_coo({x1, y1}), M, size)){
            return move(new_coo({x1, y1}), M, size);
        } else {
            return random_move(M, size);
        }
        return nullptr;

    } ///логику передумать в корне - просто тупо
    //мы тупо двигаемся в противоположную сторону, а если не вышло то на рандоме.
    //как бы если не вышло, то надо не на рандоме, а в другие клетки в противоположном направлении от противника пытаться попасть...


    Entity* tick(std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size) override{
        age++;
        die_if_you_should();
        fate(M, size);

        if(!this->is_dead()){
            std::pair<int, int> neighbour = partner_is_near(M, size);
            if(neighbour.first!=-1){
                //?
                return reproduce(neighbour, M, size); //вернет только Entity ребенка, ссылку на нынешнюю рыбу не возвращает
                //?
            } else if(where_is_predator(M, size).first!=-1){
                return move_away(where_is_predator(M, size));

            } else if(no_friend_is_near(M, size)){
                l_years++;
                return random_move(M, size);
            }  /*else if(cur_cycle.find_type_near_this(SHRIMP, this->get_position()).first != -1){
                move(cur_cycle.find_type_near_this(SHRIMP, this->get_position()));
                ///kill shrimp
            } // else do not move
            */
        } else {
            die();
        }
    } //тут все ок
    /// reproduce должен возвращать два Entity* ?

}; //карпы не агрессивные

class bad_carp : public Entity
{
    int max_age{100};
    int age;

public:

    bad_carp(int x, int y) : Entity(x, y, BAD_CARP) {
        age = 0;
        this->priority=MEDIUM;
    }

    bad_carp(std::pair<int, int> coo) : Entity(coo.first, coo.second, BAD_CARP) {
        age = 0;
        this->priority=MEDIUM;
    }

    bad_carp(int x, int y, int c_age) : Entity(x, y, BAD_CARP) {
        age = c_age;
        this->priority=MEDIUM;
    }

    std::pair<int, int> the_same_is_near(std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
        return find_type_near_this(this->type, this->get_position(), M, size);
    }

    std::pair<int, int> food_is_near(std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
        return find_type_near_this(GOOD_CARP, this->get_position(), M, size);
    }

    std::pair<int, int> where_is_food(std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
        int X = get_position().first;
        int Y = get_position().second;
        std::pair<int, int> moves[] = {{X+1, Y+1}, {X-1, Y-1}, {X+1, Y-1}, {X-1, Y+1}};
        for (int i = 0; i < 4; ++i) {
            moves[i]=new_coo(moves[i]);
            if(find_type_near_this(GOOD_CARP, moves[i], M, size).first != -1){
                return moves[i];
            }
        }
        return {-1, -1};
    }

    ~bad_carp() {
    }

    void die(){
        kill_it({this->get_position().first, this->get_position().second});
    }///delete from ocean

    void die_if_you_should(){
        if(age >= max_age){
            this->kill_it();
        }
    }

    void fate(){
        if(random(0, 10000) == 1){
            this->kill_it(); //that's your fate
        }
    }

    Entity* move(std::pair<int, int> coo, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
        bad_carp* new_carp = new bad_carp(this->get_position().first, this->get_position().second, age);
        return new_carp;
    }

    Entity* random_move(std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
        //randomly
        int n_move = random(0, 8);
        int X = get_position().first;
        int Y = get_position().second;
        std::pair<int, int> moves[] = {{X, Y}, {X+1, Y}, {X, Y+1}, {X-1, Y}, {X, Y-1}, {X+1, Y+1}, {X-1, Y-1}, {X+1, Y-1}, {X-1, Y+1} };
        for(int i = 0; i < 9; i++, n_move++){
            if(n_move==9){
                n_move=0;
            }
            moves[n_move]=new_coo(moves[n_move]);
            if(is_empty(moves[n_move], M, size)){
                //do a move
                return move(moves[n_move], M, size);
            }
        }
        /// nullptr or itself??????
        return nullptr;
    }

    Entity* eat_move(std::pair<int, int> food_coo, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
        return move(food_coo, M, size);
        //kill the food
        kill_it(food_coo);
    } ///

    Entity* tick(std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size) override{
        age++;
        die_if_you_should();
        fate();
        if(!this->is_dead()){
            std::pair<int, int> food = food_is_near();
            std::pair<int, int> where_is_the_next_food = where_is_food();
            if(food.first!=-1){
                return eat_move(food, M, size);
            } else if(where_is_the_next_food.first!=-1){
                return move(where_is_the_next_food, M, size);
            } else {
                return random_move(M, size);
            }
        }else{
            die();
        }

    }
}; //карпы агрессивные

void caviar_carp::evolution(std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
    if(age>=max_age){
        // create a couple of new random carps

        die();
        int X{0}, Y{0};
        std::pair<int, int> coo = this->get_position();
        std::pair<int, int> moves[9] = {{0,0},{0, 1}, {1,  0}, {1, 1}, {0, -1}, {-1, 0}, {-1, -1}, {1, -1}, {-1, 1}};
        for (int i = 0; i < 9; ++i) {
            std::pair<int, int> new_coo = {coo.first+moves[i].first, coo.second+moves[i].second};
            new_coo = this->new_coo(new_coo);
            if(random(0,2)==1){
                if(is_empty(new_coo, M, size)){
                    bad_carp* new_carp = new bad_carp(new_coo);
                    add_f_entity(new_carp); ///
                }
            } else {
                if(is_empty(new_coo, M, size)){
                    good_carp* new_carp = new good_carp(new_coo);
                    add_f_entity(new_carp, M, size); ///
                }
            }

        }
    }
} //эволюция игры в разных карпов
/// как это переписать без add_f_entity????, карпов же много

class stone: public Entity{
    int age;
public:

    stone(int x, int y) : Entity(x, y, ROCK) {
        age = 0;
        this->priority=HIGH;
    }

    stone(int x, int y, int a) : Entity(x, y, ROCK) {
        age = a;
        this->priority=HIGH;
    }

    virtual ~stone() {

    }

    void die(){
        kill_it({this->get_position().first, this->get_position().second});
    }

    Entity* move(std::pair<int, int> coo, std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
        stone* new_stone = new stone(coo.first, coo.second, age);
        return new_stone;
    }


    Entity* random_move(std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
        //randomly
        int n_move = random(0, 8);
        int X = get_position().first;
        int Y = get_position().second;
        std::pair<int, int> moves[] = {{X, Y}, {X+1, Y}, {X, Y+1}, {X-1, Y}, {X, Y-1}, {X+1, Y+1}, {X-1, Y-1}, {X+1, Y-1}, {X-1, Y+1} };
        for(int i = 0; i < 9; i++, n_move++){
            moves[i]=new_coo(moves[i]);
            if(n_move==9){
                n_move=0;
            }
            if(check_who_is_there(moves[n_move])!= this->type){
                //do a move
                if(!is_empty(moves[n_move], M, size) && check_who_is_there(moves[n_move], M, size)!=WATER_LILY){
                    // kill it
                    kill_it(moves[n_move]); ///
                }
                return move(moves[i], M, size);

            }
        }
        return nullptr;

    } ///

    Entity* evolution(std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size){
        if(random(0, 1000000)==age%1000000){
            die();
            ///??
            return nullptr;
        } else if(random(0, 100)==5){
            return random_move(M, size);
        }
    }

    Entity* tick(std::unordered_map<std::pair<int, int>, Entity>* M, std::pair<int, int> size) override{
        age++;
        return evolution(M, size);
    }


}; //камень

void Ocean::create_entities(){
    int max_cages = size.first*size.second;
    int fish_amount = random(max_cages/(30), max_cages/(20));
    for (int i = 0; i < fish_amount; ++i) {
        std::pair<int, int> coo = {random(0, size.first-1), random(0, size.second-1)};
        if(is_empty(coo, *(this->entities.map), size)){
            good_carp* new_carp = new good_carp({random(0, size.first-1), random(0, size.second-1)});
            this->entities.insert(new_carp);
        }
    }

    int stone_amount = random((max_cages-fish_amount)/(20), (max_cages-fish_amount)/(10));
    for (int i = 0; i < stone_amount; ++i) {
        std::pair<int, int> coo = {random(0, size.first-1), random(0, size.second-1)};
        if(is_empty(coo, *(this->entities.map), size)){
            stone* new_stone = new stone({random(0, size.first-1), random(0, size.second-1)});
            this->entities.insert(new_stone);
        }
    }

}