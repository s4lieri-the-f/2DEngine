# OCEAN_SAMPLE
```sh
# Server start
sudo ./server.out

# Client start
sudo ./client.out
```

***УДАЧИ СО СБОРКОЙ***
Сервер: `g++ loopback.cpp ocean_sample/test_logic.cpp networking/server.cpp -o bin/server.out`
Клиент: `g++ networking/client.cpp graphical_engine/render.hpp -o bin/client-test.out -lGL -lGLU -lglut -lpthread -lboost_system -lboost_thread`
Настроено на `localhost`, конфиги и даже аргументы командной строки было влом добавлять

## Логика
*Анна Баурина*
- `ocean_sample/logic.hpp`

Обновляет океан по запросу извне.

## Нетворкинг
*Апрасидзе Георгий*
- `networking/server.hpp`
- `networking/client.hpp`

Запускает loopback-сервер с океаном на удаленной машине
Запускает клиент на локальной машине.
Отправляет данные по сокетам.

## Рендер/отрисовка
*Сапрыкина Ксения*
- `graphical_engine/render.cpp`

Отрисовывает (пока что попиксельно) полученную от `client.cpp` карту при помощи OpenGL + GLUT.
