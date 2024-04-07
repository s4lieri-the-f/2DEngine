# OCEAN_SAMPLE
```sh
# Server start
sudo ./Server.out <width> <height>

# Client start
sudo ./Client.out <host> <port>
```

## Логика
*Анна Баурина*
- `ocean_sample/logic.hpp`
Обновляет океан по запросу извне.
Пользователи ещё не дописаны, могут только смотреть происходящее

## Нетворкинг
*Апрасидзе Георгий*
- `networking/server.hpp`
- `networking/client.hpp`
Запускает loopback-сервер с океаном на локальной машине
Запускает клиент на удаленной машине.
Отправляет данные по WebSocketStream.

## Рендер/отрисовка
*Сапрыкина Ксения*
- `graphical_engine/render.cpp`
Отрисовывает (пока что попиксельно) полученную от `client.cpp` карту при помощи OpenGL + GLUT, может принимать действия пользователя, но пока нет реализации в логике -- ничего не делает.
