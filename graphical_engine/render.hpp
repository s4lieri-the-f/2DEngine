// учитывая что у меня несчастный мак, которому не нравится glut, надеюсь это компилится
#include "GL/glut.h"
#include <unordered_map>
#include <tuple>

// я же надеюсь мы можем просто оставить это глобальными с какими нибудь цифорками, оставила это для примера
const int width = 800;
const int height = 600;
// туплю и не понимаю как сравнивать не на границе ли мы поля, если нет точных n*m, ааааааа
const int n = 20;
const int m = 15;

// цвета
std::unordered_map<int, std::tuple<GLfloat, GLfloat, GLfloat>> hashMap = {
    {0, {0.0f, 0.0f, 0.0f}}, // черный, пустая клеточка
    {1, {0.0f, 0.0f, 1.0f}}, // синий (единичку я поставила как челика в keyboard)
    {2, {1.0f, 0.0f, 0.0f}}, // красный
    {3, {0.0f, 1.0f, 0.0f}}, // зеленый
    {4, {1.0f, 1.0f, 0.0f}}, // желтый
    // {5, ""}
};

class Window
{
    int **grid;

    static int **currentGrid; // чтобы передавались стат данные

    void updateGrid(int **grid)
    {
        currentGrid = grid;
    }

    static void
    display()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        float cellWidth = 2.0f / ::width;
        float cellHeight = 2.0f / ::height;

        for (int i = 0; i < ::width; i++)
        {
            for (int j = 0; j < ::height; j++)
            {

                int value = currentGrid[i][j];
                auto it = hashMap.find(value);
                if (it != hashMap.end())
                {
                    auto [r, g, b] = it->second;
                    glColor3f(r, g, b);
                }
                float x = -1.0f + i * cellWidth;
                float y = -1.0f + j * cellHeight;

                if (value == 0)
                    glBegin(GL_LINE_LOOP); // квадрат без заливки
                else
                    glBegin(GL_QUADS); // с заливкой

                glVertex2f(x, y);
                glVertex2f(x + cellWidth, y);
                glVertex2f(x + cellWidth, y + cellHeight);
                glVertex2f(x, y + cellHeight);
                glEnd();
            }
        }

        glutSwapBuffers();
    }

    static void reshape(int w, int h)
    {
        glViewport(0, 0, w, h);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    static void keyboard(unsigned char key, int x, int y)
    {
        // Я НЕ УВЕРЕНА ЧТО ТАК, Я НЕ РАЗБИРАЮСЬ В КООРДИНАТАХ ОПЕНГЛ
        // диапазон координат OpenGL от -1 до 1
        int i = (x + 1.0f) / (2.0f / ::width);
        int j = (1.0f - y) / (2.0f / ::height);

        if (key == 'w' || key == 'W' || key == GLUT_KEY_UP)
        {
            if (currentGrid[i][(j - 1 + m) % m] == 0)
            {
                currentGrid[i][j] = 0;
                currentGrid[i][(j - 1 + m) % m] = 1;
                //
            }
        }
        else if (key == 'a' || key == 'A' || key == GLUT_KEY_LEFT)
        {
            if (currentGrid[(i - 1 + n) % n][j] == 0)
            {
                currentGrid[i][j] = 0;
                currentGrid[(i - 1 + n) % n][j] = 1;
                //
            }
        }
        else if (key == 's' || key == 'S' || key == GLUT_KEY_DOWN)
        {
            if (currentGrid[i][(j + 1) % m] == 0)
            {
                currentGrid[i][j] = 0;
                currentGrid[i][(j + 1) % m] = 1;
                //
            }
        }
        else if (key == 'd' || key == 'D' || key == GLUT_KEY_RIGHT)
        {
            if (currentGrid[(i + 1) % n][j] == 0)
            {
                currentGrid[i][j] = 0;
                currentGrid[(i + 1) % n][j] = 1;
                //
            }
        }
        glutPostRedisplay();
    }
    static void timer(int value)
    {
        // перерисовка
        glutPostRedisplay();
        // таймер на секунду
        glutTimerFunc(1000, timer, 0);
    }

public:
    Window(int **grid) : grid(grid)
    {
        // Инициализация OpenGL
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
        glutInitWindowSize(::width, ::height);
        glutCreateWindow("ababbaba"); // хочу тут хихи хаха

        // Ура колбэки
        // о нет, колбэки
        glutDisplayFunc(display);

        // Reshape
        glutReshapeFunc(reshape);

        currentGrid = grid;

        glutTimerFunc(1000, timer, 0); // запуск таймера
    }

    void run()
    {
        // GLUT main loop
        glutKeyboardFunc(keyboard);
        glutMainLoop();
    }

    // деструктор просто чтобы был
    ~Window()
    {
        for (int i = 0; i < width; i++)
        {
            delete[] grid[i];
        }
        delete[] grid;
    }
};
int **Window::currentGrid = nullptr;
