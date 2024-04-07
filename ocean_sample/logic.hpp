#include <vector>
#include <queue>
#include <unordered_map>
#include <future>
#include <ctime>

/*
1) добавить конструктор для продолжения жизни объекта - готово (мб идея хуйня)
2) переписать выход координат за поле внутри классов - готово (руки кривые, да)
3) переписать движение (не менять коо внутри класса, а создавать новый объект) - готово
4) переписать смерть (через kill_it() и is_dead()) - +-готово, осталось внутри океана сделать это рабочим
5) внутри океана - то что помечено коммами ЕЩЕ НЕ ГОТОВО
6) class SHRIMP - мб без него поживем
7) очередь - написать методы НЕ ГОТОВО
8) class PLAYER
9) caviar evolution - оно пустое ЕЩЕ НЕ ГОТОВО
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

enum Priority //we need it for queue
{
    LOW,
    MEDIUM,
    HIGH
};

class Entity{ // fishes, animals, stones, etc
    int alive{1};
    int x, y; // ok, it's like coordinates

public:

    Type type;
    Priority priority;

    void kill_it(){
        alive = 0;
    }

    bool is_dead(){
        return !alive;
    }

    Entity(int x, int y, Type type) : x(x), y(y), type(type){}; // create new ocean being
    virtual std::pair<int, int> get_position() const = 0; /// return coordinates

    virtual std::future<void> tick() = 0; /// update a life cycle

    ~Entity(); ///wipe it off the face of ocean

};

template <typename T, typename Priority> class PriorityQueueMap
{
    std::unordered_map<std::pair<int, int>, T> map;
    std::priority_queue<std::pair<Priority, T>> queue; // Т ссылается на объекты в мэпе

public:
    PriorityQueueMap();

    ~PriorityQueueMap();

    void insert(const T &key, const Priority &priority, const Type t){
        // вставка нового элемента
    }

    void erase(const T &key){
        // стереть отовсюду
    }

    std::pair<Priority, T> top(){
        // вернуть ссылку на объект
    }

    void pop(){
        // вернуть верхний и стереть его из очереди
    }

    std::pair<Priority, T> find(std::pair<int, int> coo, Type type){
        // вернуть ссылку на объект
    }


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
        entities.insert({entity.get_position()}, entity.priority, entity.type);


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
    }


    Type check_who_is_there(std::pair<int, int> coo){
        return pond[coo.first][coo.second];
    }

    std::pair<int, int> kill_it(std::pair<int, int> coo, Type type){
        entities.find(coo, type).second->kill_it;
    }///
};

///
Ocean cur_cycle({100,100}); // я нихуя не понимаю как писать логику не обращаясь напрямую к полю ааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааааа
Ocean next_cycle({100,100});
///





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

    bool find_adults(){
        if(cur_cycle.find_type_near_this(GOOD_CARP, this->get_position()).first!=-1){
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
        this->~caviar_carp();
    }

    void die_if_you_should(){
        if(waiting_time > max_waiting_time){
            this->kill_it();
        }
    } //ok

    void evolution(){
        if(age>=max_age){
            /// create a couple of new random carps
            this->kill_it();
        }
    } /// дописать

    std::future<void> tick() override{
        age++;
        find_adults();
        die_if_you_should();
        evolution();
        if(this->is_dead()){
            die();
        }
        caviar_carp new_caviar(this->get_position().first, this->get_position().second, age, waiting_time);
        next_cycle.add_entity(new_caviar);
    } /// ээээээээээ чет хуйню написала - создание нового не работает
}; ///дописать 1 метод

class good_carp : public Entity
{
    int max_age{100};
    int max_l_years{20};

    int l_years{0};
    int age;

public:

    good_carp(int x, int y) : Entity(x, y, GOOD_CARP) {
        age = 0;
        this->priority=LOW;
    }//все ок

    good_carp(int x, int y, int a, int l) : Entity(x, y, GOOD_CARP) {
        age = a;
        l_years = l;
        this->priority=LOW;
    }//все ок

    std::pair<int, int> partner_is_near(){ //only good_carp can be a partner
        return cur_cycle.find_type_near_this(this->type, this->get_position());
    }//все ок

    bool no_friend_is_near(){
        // check the circle around this carp
        // all carps are friends of good ones
        if(cur_cycle.find_type_near_this(this->type, this->get_position()).first==-1 && cur_cycle.find_type_near_this(BAD_CARP, this->get_position()).first != -1){
            return 1;
        } return 0;

    }//все ок

    virtual ~good_carp() {
        // как деструктор писать ааааааааааа
    } //тут нет нихуя внутри

    void die(){
        this->~good_carp();
    }///delete from ocean - нет удаления с океана

    void die_if_you_should(){
        if(age >= max_age || l_years >= max_l_years){
            this->kill_it();
        }
    }

    void fate(){
        if(random(0, 1000000) == 1){
            this->kill_it(); //that's your fate
        }
    }

    std::pair<int, int> reproduce(std::pair<int, int> parent_2){ // use coo

        std::pair<int, int> child_coo = cur_cycle.find_empty_near_this(this->get_position());

        if(child_coo.first==-1){
            child_coo = cur_cycle.find_empty_near_this(parent_2);
        }
        if(child_coo.first==-1){
            //don't let them born there is no space
            return child_coo;
        }
        //create new object - caviar
        if(child_coo.first!=-1){
            caviar_carp child = new caviar_carp(child_coo.first, child_coo.second);
            next_cycle.add_entity(child);
        }
        return child_coo;

    } /// не работает - создание икры

    void move(std::pair<int, int> coo){
        good_carp new_carp(this->get_position().first, this->get_position().second, age, l_years);
        next_cycle.add_entity(new_carp); /// mistake
        return;
    } ///heeeeeeeeeeeeeeeeeeeeeeeeeeeeelp - создание нового карпа

    void random_move(){
        //randomly
        int n_move = random(0, 8);
        int X = get_position().first;
        int Y = get_position().second;
        std::pair<int, int> moves[] = {{X, Y}, {X+1, Y}, {X, Y+1}, {X-1, Y}, {X, Y-1}, {X+1, Y+1}, {X-1, Y-1}, {X+1, Y-1}, {X-1, Y+1} };
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
        ///
        return;
    } //все ок

    std::pair<int, int> where_is_predator(){
        int X = get_position().first;
        int Y = get_position().second;
        std::pair<int, int> moves[] = {{X+1, Y+1}, {X-1, Y-1}, {X+1, Y-1}, {X-1, Y+1}};
        for (int i = 0; i < 4; ++i) {
            if(cur_cycle.find_type_near_this(GOOD_CARP, moves[i]).first != -1){
                return moves[i];
            }
        }
        return {-1, -1};
    } //все ок

    void move_away(std::pair<int, int> predator_coo){
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
        if(cur_cycle.is_empty(cur_cycle.new_coo({x1, y1}))){
            move(cur_cycle.new_coo({x1, y1}));
        } else {
            random_move();
        }
        return;

    } ///логику передумать в корне - просто тупо
    //мы тупо двигаемся в противоположную сторону, а если не вышло то на рандоме.
    //как бы если не вышло, то надо не на рандоме, а в другие клетки в противоположном направлении от противника пытаться попасть...


    std::future<void> tick() override{
        age++;
        die_if_you_should();
        fate();

        if(!this->is_dead()){
            std::pair<int, int> neighbour = partner_is_near();
            if(neighbour.first!=-1){
                reproduce(neighbour);

            } else if(where_is_predator().first!=-1){
                move_away(where_is_predator());

            } else if(no_friend_is_near()){
                l_years++;
                random_move();
            }  /*else if(cur_cycle.find_type_near_this(SHRIMP, this->get_position()).first != -1){
                move(cur_cycle.find_type_near_this(SHRIMP, this->get_position()));
                ///kill shrimp
            } // else do not move
            */
        } else {
            die();
        }
    } //тут все ок

}; //создание и удаление с океана не работают

class bad_carp : public Entity
{
    int max_age{100};
    int age;

public:

    std::pair<int, int> get_position() const override{
        return this->get_position();
    }

    bad_carp(int x, int y) : Entity(x, y, BAD_CARP) {
        age = 0;
        this->priority=MEDIUM;
    }

    bad_carp(int x, int y, int c_age) : Entity(x, y, BAD_CARP) {
        age = c_age;
        this->priority=MEDIUM;
    }

    std::pair<int, int> the_same_is_near(){
        return cur_cycle.find_type_near_this(this->type, this->get_position());
    }

    std::pair<int, int> food_is_near(){
        return cur_cycle.find_type_near_this(GOOD_CARP, this->get_position());
    }

    std::pair<int, int> where_is_food(){
        int X = get_position().first;
        int Y = get_position().second;
        std::pair<int, int> moves[] = {{X+1, Y+1}, {X-1, Y-1}, {X+1, Y-1}, {X-1, Y+1}};
        for (int i = 0; i < 4; ++i) {
            moves[i]=cur_cycle.new_coo(moves[i]);
            if(cur_cycle.find_type_near_this(GOOD_CARP, moves[i]).first != -1){
                return moves[i];
            }
        }
        return {-1, -1};
    }

    ~bad_carp() {
    }

    void die(){
        this->~bad_carp();
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

    void move(std::pair<int, int> coo){
        bad_carp new_carp(this->get_position().first, this->get_position().second, age)
        next_cycle.add_entity(new_carp); /// mistake
        return;
    } ///heeeeeeeeeeeeeeeeeeeeeeeeeeeeelp - создание нового не работает

    void random_move(){
        //randomly
        int n_move = random(0, 8);
        int X = get_position().first;
        int Y = get_position().second;
        std::pair<int, int> moves[] = {{X, Y}, {X+1, Y}, {X, Y+1}, {X-1, Y}, {X, Y-1}, {X+1, Y+1}, {X-1, Y-1}, {X+1, Y-1}, {X-1, Y+1} };
        for(int i = 0; i < 9; i++, n_move++){
            if(n_move==9){
                n_move=0;
            }
            moves[i]=cur_cycle.new_coo(moves[i]);
            if(cur_cycle.is_empty(moves[n_move])){
                //do a move
                move(moves[i]);
                return;
            }
        }
        return;
    }

    void eat_move(std::pair<int, int> food_coo){
        move(food_coo);
        //kill the food
        cur_cycle.kill_it(food_coo, GOOD_CARP);
    } ///

    std::future<void> tick() override{
        age++;
        die_if_you_should();
        fate();
        if(!this->is_dead()){
            std::pair<int, int> food = food_is_near();
            std::pair<int, int> where_is_the_next_food = where_is_food();
            if(food.first!=-1){
                eat_move(food);
            } else if(where_is_the_next_food.first!=-1){
                move(where_is_the_next_food);
            } else {
                random_move();
            }
        }else{
            die();
        }

    }
}; //создание и удаление с океана не работают

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
        this->~stone();
    }

    void move(std::pair<int, int> coo){
        stone new_stone(coo.first, coo.second, age); /// mistake
        next_cycle.add_entity(new_stone);
        return;
    } ///heeeeeeeeeeeeeeeeeeeeeeeeeeeeelp


    void random_move(){
        //randomly
        int n_move = random(0, 8);
        int X = get_position().first;
        int Y = get_position().second;
        std::pair<int, int> moves[] = {{X, Y}, {X+1, Y}, {X, Y+1}, {X-1, Y}, {X, Y-1}, {X+1, Y+1}, {X-1, Y-1}, {X+1, Y-1}, {X-1, Y+1} };
        for(int i = 0; i < 9; i++, n_move++){
            moves[i]=cur_cycle.new_coo(moves[i]);
            if(n_move==9){
                n_move=0;
            }
            if(cur_cycle.check_who_is_there(moves[n_move])!= this->type){
                //do a move
                if(!cur_cycle.is_empty(moves[n_move]) && cur_cycle.check_who_is_there(moves[n_move])!=WATER_LILY){
                    // kill it
                    cur_cycle.kill_it(moves[n_move], cur_cycle.check_who_is_there(moves[n_move])); ///
                }
                move(moves[i]);
                return;
            }
        }
        return;

    } ///

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


}; //создание и удаление с океана не работают

class water_lily : public Entity{

    int memory;

public:

    water_lily(int x, int y) : Entity(x, y, WATER_LILY) {
        memory = 0;
        this->priority=HIGH;
    }
    water_lily(int x, int y, int m) : Entity(x, y, WATER_LILY) {
        memory = m;
        this->priority=HIGH;
    }

    virtual ~water_lily() {
    }

    void move(std::pair<int, int> coo){
        coo = cur_cycle.new_coo(coo);
        if(cur_cycle.check_who_is_there(coo) != this->type){
            next_cycle.add_entity(this); /// mistake
        }

        return;
    } ///heeeeeeeeeeeeeeeeeeeeeeeeeeeeelp


    std::future<void> tick() override{
        memory++;
        memory=memory%5;
        if(random(0, memory)==1){
            move({this->get_position().first + (random(0, 4) > 0), this->get_position().second + (random(0, 3) > 0)});
        }
    }
}; //создание с океана не работают
