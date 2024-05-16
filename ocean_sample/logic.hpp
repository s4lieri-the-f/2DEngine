#include <vector>
#include <queue>
#include <unordered_map>
#include <future>
#include <ctime>

/*
ОГУРЕЦ ОТ КОПАТЫЧА
ОГУРЕЦ ОТ КОПАТЫЧА
ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА
 ОГУРЕЦ ОТ КОПАТЫЧА

*/
/*

4) допилить методы Ocean
5) НАПИСАТЬ ПРИОРИТИ КЬЮ МЭП

.........................................................

6) внутри океана - то что помечено коммами ЕЩЕ НЕ ГОТОВО

*/

int random(int s, int f){
    int range = f-s+1;
    return (std::clock() % range + s);

}


enum Type
{
    NOTHING, //hehehe
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

    void kill_it(void* pointer_ocean){
        alive = 0;
    }; //смерть, без взаимодействия с океаном

    bool is_dead(void* pointer_ocean){ // проверка на мертвость
        return !alive;
    };

    Entity(int x, int y, Type type) : x(x), y(y), type(type){}; // create new ocean being

    std::pair<int, int> get_position() { // возвращение координат в океане
        return {x, y};
    };

    virtual void tick(void* pointer_ocean) = 0; // update a life cycle

    ~Entity(); //wipe it off the face of ocean

};

template <typename T, typename Priority> class PriorityQueueMap{

    auto static cmp = [](std::pair<T, Priority> a, std::pair<T, Priority> b) {return a.second > b.second;};
    std::priority_queue<std::pair<T, Priority>, std::vector<std::pair<T, Priority>, cmp>> queue;
    std::unordered_map<std::pair<int, int>, T> map; //T = Entity

public:
    PriorityQueueMap();

    ~PriorityQueueMap();

    void old_insert(const T &key, const Priority &priority, const Type t, std::pair<int, int> size){
        // вставка нового элемента

    }

    void insert(Entity* new_entity){

    }// вставка нового элемента


    void erase(const T &key){
        // стереть отовсюду
    }

    std::pair<Priority, T> top(){
        // вернуть ссылку на объект
    }

    void pop(){
        // вернуть верхний и стереть его из очереди
    }

    std::pair<Priority, T> pop_1(){

    }

    bool empty(){

    }

    Type find(std::pair<int, int> coo){
        // вернуть ссылку на объект
        return WATER;
    }


}; /// ПУСТОЙ КЛАСС, ДОПИСАТЬ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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

    bool is_empty(std::pair<int, int> coo){
        // check if the cage is empty
        if(((Ocean*)future_ocean)->entities.find(coo) == WATER){ // != carp or caviar or stone or...
            return 1;
        } return 0;
    } //проверка клетки на пустоту (нет Entity по координате)

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
            std::pair<std::pair<int, int>, Type> tmp = (*(Ocean*)future_ocean).entities.pop_1();
            pond[tmp.first.first][tmp.first.second] = tmp.second;
        }
        for (int i = 0; i < water_lily_coo.size(); ++i) {
            pond[(*(Ocean*)future_ocean).water_lily_coo[i].first][(*(Ocean*)future_ocean).water_lily_coo[i].second]=WATER_LILY;
        }
        return pond;
    }// Построение карты для отправки Ксюшe

    ~Ocean(){} // деструктор

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
};

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

    bool find_adults(void* pointer_ocean){
        if((*(Ocean*)pointer_ocean).find_type_near_this(GOOD_CARP, this->get_position()).first != -1){
            waiting_time++;
            return 0;
        } else {
            waiting_time = 0;
            return 1;
        }
    }

    ~caviar_carp() {

    }

    void die(void* pointer_ocean){

        (*(Ocean*)pointer_ocean).kill_it(this->get_position());

    }

    void die_if_you_should(void* pointer_ocean){
        if(waiting_time > max_waiting_time){
            die((Ocean*)pointer_ocean);
        }
    } //ok

    void evolution(void* pointer_ocean);

    virtual void tick(void* pointer_ocean){
        age++;
        find_adults(pointer_ocean);
        die_if_you_should(pointer_ocean);
        evolution(pointer_ocean);
        if(this->is_dead((Ocean*)pointer_ocean)){
            die(pointer_ocean);
        }
        caviar_carp* new_caviar = new caviar_carp(this->get_position().first, this->get_position().second, age, waiting_time);
        (*(Ocean*)pointer_ocean).add_f_entity(new_caviar);
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

    std::pair<int, int> partner_is_near(void* pointer_ocean){ //only good_carp can be a partner
        return (*(Ocean*)pointer_ocean).find_type_near_this(this->type, this->get_position());
    }//все ок

    bool no_friend_is_near(void* pointer_ocean){
        // check the circle around this carp
        // all carps are friends of good ones
        if((*(Ocean*)pointer_ocean).find_type_near_this(this->type, this->get_position()).first==-1 && (*(Ocean*)pointer_ocean).find_type_near_this(BAD_CARP, this->get_position()).first != -1){
            return 1;
        } return 0;

    }//все ок

    virtual ~good_carp() {
        // как деструктор писать ааааааааааа
    } //тут нет нихуя внутри

    void die(void* pointer_ocean){
        (*(Ocean*)pointer_ocean).kill_it({this->get_position().first, this->get_position().second});
        this->~good_carp();

    }///delete from ocean - нет удаления с океана

    void die_if_you_should(void* pointer_ocean){
        if(age >= max_age || l_years >= max_l_years){
            this->die(pointer_ocean);
        }
    }

    void fate(void* pointer_ocean){
        if(random(0, 1000000) == 1){
            this->die(((Ocean*)pointer_ocean)); //that's your fate
        }
    }

    std::pair<int, int> reproduce(std::pair<int, int> parent_2, void* pointer_ocean){ // use coo

        std::pair<int, int> child_coo = (*(Ocean*)pointer_ocean).find_empty_near_this(this->get_position());

        if(child_coo.first==-1){
            child_coo = (*(Ocean*)pointer_ocean).find_empty_near_this(parent_2);
        }
        if(child_coo.first==-1){
            //don't let them born there is no space
            return child_coo;
        }
        //create new object - caviar
        if(child_coo.first!=-1){
            caviar_carp* child = new caviar_carp(child_coo.first, child_coo.second);
            (*(Ocean*)pointer_ocean).add_f_entity((Entity*)child);
        }
        return child_coo;

    } /// не работает - создание икры

    void move(std::pair<int, int> coo, void* pointer_ocean){
        good_carp* new_carp = new good_carp(this->get_position().first, this->get_position().second, age, l_years);
        (*(Ocean*)pointer_ocean).add_f_entity(new_carp);
        return;
    }

    void random_move(void* pointer_ocean){
        //randomly
        int n_move = random(0, 8);
        int X = get_position().first;
        int Y = get_position().second;
        std::pair<int, int> moves[] = {{X, Y}, {X+1, Y}, {X, Y+1}, {X-1, Y}, {X, Y-1}, {X+1, Y+1}, {X-1, Y-1}, {X+1, Y-1}, {X-1, Y+1} };
        for(int i = 0; i < 9; i++, n_move++){
            if(n_move==9){
                n_move=0;
            }
            if((*(Ocean*)pointer_ocean).in_fild(moves[n_move]) && (*(Ocean*)pointer_ocean).is_empty(moves[n_move])){
                //do a move
                move(moves[i], ((Ocean*)pointer_ocean));
                return;
            }
        }
        ///
        return;
    } //все ок

    std::pair<int, int> where_is_predator(void* pointer_ocean){
        int X = get_position().first;
        int Y = get_position().second;
        std::pair<int, int> moves[] = {{X+1, Y+1}, {X-1, Y-1}, {X+1, Y-1}, {X-1, Y+1}};
        for (int i = 0; i < 4; ++i) {
            if((*(Ocean*)pointer_ocean).find_type_near_this(BAD_CARP, moves[i]).first != -1){
                return moves[i];
            }
        }
        return {-1, -1};
    } //все ок

    void move_away(std::pair<int, int> predator_coo, void* pointer_ocean){
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
        if((*(Ocean*)pointer_ocean).is_empty((*(Ocean*)pointer_ocean).new_coo({x1, y1}))){
            move((*(Ocean*)pointer_ocean).new_coo({x1, y1}), ((Ocean*)pointer_ocean));
        } else {
            random_move(((Ocean*)pointer_ocean));
        }
        return;

    } ///логику передумать в корне - просто тупо
    //мы тупо двигаемся в противоположную сторону, а если не вышло то на рандоме.
    //как бы если не вышло, то надо не на рандоме, а в другие клетки в противоположном направлении от противника пытаться попасть...


    void tick(void* pointer_ocean) override{
        age++;
        die_if_you_should(((Ocean*)pointer_ocean));
        fate(((Ocean*)pointer_ocean));

        if(!this->is_dead(((Ocean*)pointer_ocean))){
            std::pair<int, int> neighbour = partner_is_near(((Ocean*)pointer_ocean));
            if(neighbour.first!=-1){
                reproduce(neighbour, ((Ocean*)pointer_ocean));

            } else if(where_is_predator(((Ocean*)pointer_ocean)).first!=-1){
                move_away(where_is_predator(((Ocean*)pointer_ocean)), (Ocean*)pointer_ocean);

            } else if(no_friend_is_near(((Ocean*)pointer_ocean))){
                l_years++;
                random_move(((Ocean*)pointer_ocean));
            }  /*else if(cur_cycle.find_type_near_this(SHRIMP, this->get_position()).first != -1){
                move(cur_cycle.find_type_near_this(SHRIMP, this->get_position()));
                ///kill shrimp
            } // else do not move
            */
        } else {
            die(((Ocean*)pointer_ocean));
        }
    } //тут все ок

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

    std::pair<int, int> the_same_is_near(void* pointer_ocean){
        return (*(Ocean*)pointer_ocean).find_type_near_this(this->type, this->get_position());
    }

    std::pair<int, int> food_is_near(void* pointer_ocean){
        return (*(Ocean*)pointer_ocean).find_type_near_this(GOOD_CARP, this->get_position());
    }

    std::pair<int, int> where_is_food(void* pointer_ocean){
        int X = get_position().first;
        int Y = get_position().second;
        std::pair<int, int> moves[] = {{X+1, Y+1}, {X-1, Y-1}, {X+1, Y-1}, {X-1, Y+1}};
        for (int i = 0; i < 4; ++i) {
            moves[i]=(*(Ocean*)pointer_ocean).new_coo(moves[i]);
            if((*(Ocean*)pointer_ocean).find_type_near_this(GOOD_CARP, moves[i]).first != -1){
                return moves[i];
            }
        }
        return {-1, -1};
    }

    ~bad_carp() {
    }

    void die(void* pointer_ocean){
        (*(Ocean*)pointer_ocean).kill_it({this->get_position().first, this->get_position().second});
        this->~bad_carp();


    }///delete from ocean

    void die_if_you_should(void* pointer_ocean){
        if(age >= max_age){
            this->kill_it(((Ocean*)pointer_ocean));
        }
    }

    void fate(void* pointer_ocean){
        if(random(0, 10000) == 1){
            this->kill_it(((Ocean*)pointer_ocean)); //that's your fate
        }
    }

    void move(std::pair<int, int> coo, void* pointer_ocean){
        bad_carp* new_carp = new bad_carp(this->get_position().first, this->get_position().second, age);
        (*(Ocean*)pointer_ocean).add_f_entity(new_carp); /// mistake
        return;
    } ///heeeeeeeeeeeeeeeeeeeeeeeeeeeeelp - создание нового не работает

    void random_move(void* pointer_ocean){
        //randomly
        int n_move = random(0, 8);
        int X = get_position().first;
        int Y = get_position().second;
        std::pair<int, int> moves[] = {{X, Y}, {X+1, Y}, {X, Y+1}, {X-1, Y}, {X, Y-1}, {X+1, Y+1}, {X-1, Y-1}, {X+1, Y-1}, {X-1, Y+1} };
        for(int i = 0; i < 9; i++, n_move++){
            if(n_move==9){
                n_move=0;
            }
            moves[i]=(*(Ocean*)pointer_ocean).new_coo(moves[i]);
            if((*(Ocean*)pointer_ocean).is_empty(moves[n_move])){
                //do a move
                this->move(moves[i], ((Ocean*)pointer_ocean));
                return;
            }
        }
        return;
    }

    void eat_move(std::pair<int, int> food_coo, void* pointer_ocean){
        move(food_coo, ((Ocean*)pointer_ocean));
        //kill the food
        (*(Ocean*)pointer_ocean).kill_it(food_coo);
    } ///

    void tick(void* pointer_ocean) override{
        age++;
        die_if_you_should(((Ocean*)pointer_ocean));
        fate(((Ocean*)pointer_ocean));
        if(!this->is_dead((Ocean*)pointer_ocean)){
            std::pair<int, int> food = food_is_near(((Ocean*)pointer_ocean));
            std::pair<int, int> where_is_the_next_food = where_is_food(((Ocean*)pointer_ocean));
            if(food.first!=-1){
                eat_move(food, ((Ocean*)pointer_ocean));
            } else if(where_is_the_next_food.first!=-1){
                move(where_is_the_next_food, ((Ocean*)pointer_ocean));
            } else {
                random_move(((Ocean*)pointer_ocean));
            }
        }else{
            die(((Ocean*)pointer_ocean));
        }

    }
}; //карпы агрессивные

void caviar_carp::evolution(void* pointer_ocean){
    if(age>=max_age){
        // create a couple of new random carps

        die((Ocean*)pointer_ocean);
        int X{0}, Y{0};
        std::pair<int, int> coo = this->get_position();
        std::pair<int, int> moves[9] = {{0,0},{0, 1}, {1,  0}, {1, 1}, {0, -1}, {-1, 0}, {-1, -1}, {1, -1}, {-1, 1}};
        for (int i = 0; i < 9; ++i) {
            std::pair<int, int> new_coo = {coo.first+moves[i].first, coo.second+moves[i].second};
            new_coo = ((Ocean*)pointer_ocean)->new_coo(new_coo);
            if(random(0,2)==1){
                if(((Ocean*)pointer_ocean)->is_empty(new_coo)){
                    bad_carp* new_carp = new bad_carp(new_coo);
                    (*(Ocean*)pointer_ocean).add_f_entity(new_carp);
                }
            } else {
                if(((Ocean*)pointer_ocean)->is_empty(new_coo)){
                    good_carp* new_carp = new good_carp(new_coo);
                    (*(Ocean*)pointer_ocean).add_f_entity(new_carp);
                }
            }

        }
    }
} //эволюция игры в разных карпов

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

    void die(void* pointer_ocean){
        (*(Ocean*)pointer_ocean).kill_it({this->get_position().first, this->get_position().second});
        this->~stone();

    }

    void move(std::pair<int, int> coo, void* pointer_ocean){
        stone* new_stone = new stone(coo.first, coo.second, age); /// mistake
        (*(Ocean*)pointer_ocean).add_f_entity((Entity*) new_stone);
        return;
    } ///heeeeeeeeeeeeeeeeeeeeeeeeeeeeelp


    void random_move(void* pointer_ocean){
        //randomly
        int n_move = random(0, 8);
        int X = get_position().first;
        int Y = get_position().second;
        std::pair<int, int> moves[] = {{X, Y}, {X+1, Y}, {X, Y+1}, {X-1, Y}, {X, Y-1}, {X+1, Y+1}, {X-1, Y-1}, {X+1, Y-1}, {X-1, Y+1} };
        for(int i = 0; i < 9; i++, n_move++){
            moves[i]=(*(Ocean*)pointer_ocean).new_coo(moves[i]);
            if(n_move==9){
                n_move=0;
            }
            if((*(Ocean*)pointer_ocean).check_who_is_there(moves[n_move])!= this->type){
                //do a move
                if(!(*(Ocean*)pointer_ocean).is_empty(moves[n_move]) && (*(Ocean*)pointer_ocean).check_who_is_there(moves[n_move])!=WATER_LILY){
                    // kill it
                    (*(Ocean*)pointer_ocean).kill_it(moves[n_move]); ///
                }
                move(moves[i], ((Ocean*)pointer_ocean));
                return;
            }
        }
        return;

    } ///

    void evolution(void* pointer_ocean){
        if(random(0, 1000000)==age%1000000){
            die(((Ocean*)pointer_ocean));
        } else if(random(0, 100)==5){
            random_move(((Ocean*)pointer_ocean));
        }
    }

    void tick(void* pointer_ocean) override{
        age++;
        evolution(((Ocean*)pointer_ocean));
    }


}; //камень

void Ocean::create_entities(){
    int max_cages = size.first*size.second;
    int fish_amount = random(max_cages/(30), max_cages/(20));
    for (int i = 0; i < fish_amount; ++i) {
        std::pair<int, int> coo = {random(0, size.first-1), random(0, size.second-1)};
        if(is_empty(coo)){
            good_carp* new_carp = new good_carp({random(0, size.first-1), random(0, size.second-1)});
            this->entities.insert(new_carp);
        }
    }

    int stone_amount = random((max_cages-fish_amount)/(20), (max_cages-fish_amount)/(10));
    for (int i = 0; i < stone_amount; ++i) {
        std::pair<int, int> coo = {random(0, size.first-1), random(0, size.second-1)};
        if(is_empty(coo)){
            stone* new_stone = new stone({random(0, size.first-1), random(0, size.second-1)});
            this->entities.insert(new_stone);
        }
    }

}