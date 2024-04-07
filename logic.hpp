#include <vector>
#include <queue>
#include <unordered_map>
#include <future> // Я ещё подумаю об этом.
#include <ctime>

/*
    ЭТОТ КОД ПОЛНАЯ ХУЙНЯ

    тут ничего полезного, только куча нерабочего говна
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
    SHRIMP, // they are really fast, can't attack you, harmless creatures
    BAD_CARP, // it's the most aggressive fish in the ocean
    PLAYER ///I DON'T KNOW HOW TO BLAYT WORK WITH THIS

    /// Add more types here
};

class Entity{ // fishes, animals, stones, etc
public:
    int x, y; // ok, it's like coordinates
    Type type; // type of fish

    Entity(int x, int y, Type type) : x(x), y(y), type(type){}; // create new ocean being
    virtual std::pair<int, int> get_position() const = 0; /// return coordinates

    virtual std::future<void> tick() = 0; /// update a life cycle

    ~Entity(); ///wipe it off the face of ocean

};

enum Priority //we need it for queue
{
    LOW,
    MEDIUM,
    HIGH
};

template <typename T, typename Priority> class PriorityQueueMap
{
    std::unordered_map<std::pair<int, int>, T> map;
    std::priority_queue<std::pair<Priority, T>> queue; // Т ссылается на объекты в мэпе

public:
    PriorityQueueMap();

    void insert(const T &key, const Priority &priority, const Type t){

    }

    void erase(const T &key){
        // стереть отовсюду
    }

    std::pair<Priority, T> top(){
        // вернуть ссылку на объект
    }

    void pop(){
        /// вернуть верхний и стереть его из очереди
    }

    ~PriorityQueueMap();
}; /// Я НИКТО, ЗВАТЬ МЕНЯ НИКАК И ПОНЯЛА Я НИ-ХУ-Я
/// НИ
/// ХУ
/// Я

class Ocean{

    std::pair<int, int> size;
    PriorityQueueMap<std::pair<Entity, int>, Priority> entities;
    Type** pond;
    std::pair<Type, int> min_amount;

public:

    Ocean(int x, int y) : size(std::make_pair(x, y)) {
        entities = PriorityQueueMap<std::pair<Entity, int>, Priority>();
        Type** pond = new Type* [size.first];
        for (int i = 0; i < size.first; i++) {
            pond[i] = new Type[size.second];
        }
        for (int i = 0; i < size.first; ++i) {
            for (int j = 0; j < size.second; ++j) {
                pond[i][j]=WATER;
            }
        }
    };

    void add_entity(Entity entity){//the start of the world
        ///add here an adding algorithm for a queue
        pond[entity.get_position().first][entity.get_position().second] = entity.type;

    } // По факту рождение, хули. Энтити сразу можно координаты задать.

    bool is_empty(std::pair<int, int> coo){
        // check if the cage is empty
        if(pond[coo.first][coo.second] == WATER){
            return 1;
        } return 0;
    }


    void tick(); ///update our map
    // Для каждого энтити по приоритету проверяем че происходит, изменения вносим сразу.
    // Есть обращения по x, y (главное делать это парой), можно вытаскивать из entities, существует ли добрая рыпка поблизости, и жрать её раньше, чем она свалит, к примеру.
    // Тик без цикла, сделай это функцией, которая вызывается внутри нетворкинга. Это я дописываю уже. С тебя классы, тики каждого энтити, и изменение.

    Type ** get_grid(){//create эту хуйню
        return pond;
    }
    // Построение карты для отправки Ксюши. Тоже допиши.

    int quantity_of_one_type(Type type){ //idk how to connect Type thing with our real objects from queue
        /// do your magic with queue
        ///if there is less carps than we need - just conjure more!!!
    }

    ~Ocean(){ //нихуя не уверена в этом бреде, переделать
        for (int i = 0; i < size.first; i++) {
            delete pond[i];
        }
        delete pond;
    }

    bool in_fild(std::pair<int, int> coo){
        if(coo.first >= 0 && coo.second >= 0 && coo.first < size.first && size.second > coo.second){
            return 1;
        } return 0;
    }

    bool comp_cage(Type t, std::pair<int, int> coo){
        if(pond[coo.first][coo.second]==t){
            return 1;
        } else {
            return 0;
        }
    }

    std::pair<int, int> find_empty_near_this(std::pair<int, int> coo){
        int x = coo.first;
        int y = coo.second;
        std::pair<int, int> moves[] = {{x, y}, {x+1, y}, {x, y+1}, {x-1, y}, {x, y-1}, {x+1, y+1}, {x-1, y-1}, {x+1, y-1}, {x-1, y+1}};

        for (int i = 0; i < 9; ++i) {
            if(in_fild(moves[i])){
                if(this->is_empty(moves[i])){
                    return moves[i];
                }
            }
        }

        return {-1, -1}; //there isn't any empty space near our coo
    }

    std::pair<int, int> find_type_near_this(Type type, std::pair<int, int> coo){
        int x = coo.first;
        int y = coo.second;
        std::pair<int, int> moves[] = {{x, y}, {x+1, y}, {x, y+1}, {x-1, y}, {x, y-1}, {x+1, y+1}, {x-1, y-1}, {x+1, y-1}, {x-1, y+1}};
        for (int i = 0; i < 9; ++i) {
            if(in_fild(moves[i])){
                if(pond[moves[i].first][moves[i].second] == type){
                    return moves[i];
                }
            }
        }
        return {-1, -1}; //there isn't any
    }

    Type check_who_is_there(std::pair<int, int> coo){
        return pond[coo.first][coo.second];
    }
};

///
Ocean cur_cycle({100,100}); // я нихуя не понимаю как писать логику не обращаясь напрямую к полю ааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааа
Ocean next_cycle({100,100});
///


class good_carp : public Entity
{
    int max_age{100};
    int max_l_years{20};

    int l_years{0};
    int age{0};

public:
    // хз нужен ли отдельный конструктор я нихуя не понимаюююююююю
    good_carp(int x, int y, Type type, bool sex) : Entity(x, y, type) {

    }

    std::pair<int, int> get_position() const override{ //зачем оно здесь отдельно
        return {this->x, this->y};
    }

    std::pair<int, int> the_op_is_near(){
        cur_cycle.find_type_near_this(this->type, this->get_position());
    }

    bool no_friend_is_near(){ ///rethink the realization
        // check the circle around this carp
        if(cur_cycle.find_type_near_this(this->type, this->get_position()).first==-1 && cur_cycle.find_type_near_this(BAD_CARP, this->get_position()).first != -1){
            return 1;
        } return 0;

    }

    virtual ~good_carp() {
        // как деструктор писать ааааааааааа
        //this->~Entity();

    } ///тут нет нихуя внутри

    void die(){
        this->~good_carp();
    }///delete from ocean

    void die_if_you_should(){
        if(age >= max_age || l_years >= max_l_years){
            die();
        }
    }

    void fate(){
        if(random(0, 1000000) == 1){
            die(); //that's your fate
        }
    }

    std::pair<int, int> reproduce(std::pair<int, int> parent_2){ // use coo

        std::pair<int, int> child_coo = cur_cycle.find_empty_near_this(this->get_position());

        if( child_coo.first==-1){
            child_coo = cur_cycle.find_empty_near_this(parent_2);
        }
        if(child_coo.first==-1){
            //don't let them born there is no space
            return child_coo;
        }
        ///create new object - caviar
        return child_coo;

    } /// не работает

    void move(std::pair<int, int> coo){
        this->x=coo.first;
        this->y=coo.second;
        next_cycle.add_entity(this); /// mistake
        return;
    } ///heeeeeeeeeeeeeeeeeeeeeeeeeeeeelp

    void random_move(){
        //randomly
        int n_move = random(0, 8);
        std::pair<int, int> moves[] = {{x, y}, {x+1, y}, {x, y+1}, {x-1, y}, {x, y-1}, {x+1, y+1}, {x-1, y-1}, {x+1, y-1}, {x-1, y+1} };
        for(int i = 0; i < 9; i++, n_move++){
            if(n_move==9){
                n_move=0;
            }
            if(cur_cycle.in_fild(moves[n_move]) && cur_cycle.is_empty(moves[n_move])){
                //do a move
                move(moves[i]);
                return;
            }
        }
        return;

    }


    std::future<void> tick() override{
        age++;
        std::pair<int, int> neighbour = the_op_is_near();
        if(neighbour.first!=-1){
            reproduce(neighbour);

        } else if(no_friend_is_near()){
            l_years++;
            random_move();
        } else if(cur_cycle.find_type_near_this(SHRIMP, this->get_position()).first != -1){
            move(cur_cycle.find_type_near_this(SHRIMP, this->get_position()));
            ///kill shrimp
        } // else do not move
        die_if_you_should();
        fate();

    } ///
};

class bad_carp : public Entity
{
    int max_age{100};
    int age;

public:

    std::pair<int, int> get_position() const override{
        return {this->x, this->y};
    }

    bad_carp(int x, int y, Type type) : Entity(x, y, type) { ///?
        age = 0;
    }

    std::pair<int, int> the_same_is_near(){
        return cur_cycle.find_type_near_this(this->type, this->get_position());
    }

    std::pair<int, int> food_is_near(){
        return cur_cycle.find_type_near_this(GOOD_CARP, this->get_position());
    }

    std::pair<int, int> where_is_food(){
        std::pair<int, int> moves[] = {{x+1, y+1}, {x-1, y-1}, {x+1, y-1}, {x-1, y+1}};
        for (int i = 0; i < 4; ++i) {
            if(cur_cycle.find_type_near_this(GOOD_CARP, moves[i]).first != -1){
                return moves[i];
            }
        }
        return {-1, -1};
    }

    virtual ~bad_carp() {
        // как деструктор писать ааааааааааа
        //this->~Entity();

    }

    void die(){
        ///delete from ocean
        this->~bad_carp();
    }

    void die_if_you_should(){

        if(age >= max_age){
            die();
        }
    }

    void fate(){
        if(random(0, 10000) == 1){
            die(); //that's your fate
        }
    }

    void move(std::pair<int, int> coo){
        this->x=coo.first;
        this->y=coo.second;
        next_cycle.add_entity(this); /// mistake
        return;
    } ///heeeeeeeeeeeeeeeeeeeeeeeeeeeeelp

    void random_move(){
        //randomly
        int n_move = random(0, 8);
        std::pair<int, int> moves[] = {{x, y}, {x+1, y}, {x, y+1}, {x-1, y}, {x, y-1}, {x+1, y+1}, {x-1, y-1}, {x+1, y-1}, {x-1, y+1} };
        for(int i = 0; i < 9; i++, n_move++){
            if(n_move==9){
                n_move=0;
            }
            if(cur_cycle.in_fild(moves[n_move]) && cur_cycle.is_empty(moves[n_move])){
                //do a move
                move(moves[i]);
                return;
            }
        }
        return;

    }

    void eat_move(std::pair<int, int> food_coo){
        move(food_coo);
        ///kill the food
    }

    std::future<void> tick() override{
        age++;
        std::pair<int, int> food = food_is_near();
        std::pair<int, int> where_is_the_next_food = where_is_food();
        if(food.first!=-1){
            eat_move(food);
        } else if(where_is_the_next_food.first!=-1){
            move(where_is_the_next_food);
        } else {
            random_move();
        }
        die_if_you_should();
        fate();

    }
};

class caviar_carp: public Entity{
    int age;
    int max_age{20};
    int waiting_time{0};
    int max_waiting_time{2};
public:

    caviar_carp(int x, int y, Type type) : Entity(x, y, type) {
        age=0;
    }

    bool find_adults(){
        if(cur_cycle.find_type_near_this(GOOD_CARP, this->get_position()).first!=-1){
            waiting_time++;
            return 0;
        } else {
            waiting_time = 0;
            return 1;
        }
    }

    virtual ~caviar_carp() {

    }

    void die(){
        this->~caviar_carp();
    }

    void die_if_you_should(){
        if(waiting_time > max_waiting_time){
            die();
        }
    }

    void evolution(){
        if(age>=max_age){
            /// create a couple of new random carps
            die();
        }
    } ///

    std::future<void> tick() override{
        age++;
        die_if_you_should();
        evolution();
        next_cycle.add_entity(this);
    } /// ээээээээээ чет хуйню написала
};

class stone: public Entity{

    int age;

public:

    stone(int x, int y, Type type) : Entity(x, y, type) {
        age = 0;
    }

    virtual ~stone() {

    }

    void die(){
        this->~stone();
    }

    void move(std::pair<int, int> coo){
        this->x=coo.first;
        this->y=coo.second;
        next_cycle.add_entity(this); /// mistake
        return;
    } ///heeeeeeeeeeeeeeeeeeeeeeeeeeeeelp


    void random_move(){
        //randomly
        int n_move = random(0, 8);
        std::pair<int, int> moves[] = {{x, y}, {x+1, y}, {x, y+1}, {x-1, y}, {x, y-1}, {x+1, y+1}, {x-1, y-1}, {x+1, y-1}, {x-1, y+1} };
        for(int i = 0; i < 9; i++, n_move++){
            if(n_move==9){
                n_move=0;
            }
            if(cur_cycle.in_fild(moves[n_move]) && cur_cycle.is_empty(moves[n_move])){
                //do a move
                move(moves[i]);
                return;
            }
        }
        return;

    }

    void evolution(){
        if(random(0, 1000000)==age%1000000){
            die();
        } else if(random(0, 100)==5){
            random_move();
        }
    }

    std::future<void> tick() override{
        age++;
        evolution();
    }


};

class water_lily : public Entity{

    int memory;

public:

    water_lily(int x, int y, Type type) : Entity(x, y, type) {
        memory = 0;
    }

    virtual ~water_lily() {
    }

    void move(std::pair<int, int> coo){
        this->x=coo.first;
        this->y=coo.second;
        if(!cur_cycle.in_fild(coo)){
            x = 0; y = 0;
        }
        next_cycle.add_entity(this); /// mistake
        return;
    } ///heeeeeeeeeeeeeeeeeeeeeeeeeeeeelp


    std::future<void> tick() override{
        memory++;
        memory=memory%5;
        if(random(0, memory)==1){
            move({this->x + 1, this->y + 1});
        }
    }
};

