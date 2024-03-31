// учитывая что у меня несчастный мак, которому не нравится glut, надеюсь это компилится 
#include "GL/glut.h"

// я же надеюсь мы можем просто оставить это глобальными с какими нибудь цифорками
const int width = 800;
const int height = 600;

class Window {
    int **grid;

    static int** currentGrid; // указатель чтобы в display передавались стат данные
    
    // определить цвет для челиков, хз как там аня данные хранит
    static void assignColor(int value) {
    if (value == 1) {
        glColor3f(0.0f, 0.0f, 1.0f); // синий 
    } else if (value == 2) {
        glColor3f(1.0f, 0.0f, 0.0f); // красный 
    } else if (value == 3) {
        glColor3f(1.0f, 1.0f, 0.0f); // желтый 
    } else {
        glColor3f(0.0f, 0.0f, 0.0f); // черный
    }
}

    static void display()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        float cellWidth = 2.0f / ::width; 
        float cellHeight = 2.0f / ::height;

        for (int i = 0; i < ::width; i++)
        {
            for (int j = 0; j < ::height; j++)
            {

                int value = currentGrid[i][j];
                // glColor3f(value / 255.0f, value / 255.0f, value / 255.0f);
                assignColor(value); 
                float x = -1.0f + i * cellWidth;
                float y = -1.0f + j * cellHeight;

                if (value == 0) glBegin(GL_LINE_LOOP); // квадрат без заливки ?для пустой клеточки?
                else glBegin(GL_QUADS); // с заливкой
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
        if (key == 'w' || key == 'W'|| key == GLUT_KEY_UP){
            //
        }
        else if (key == 'a' || key == 'A'|| key == GLUT_KEY_LEFT){
            //
        }
        else if (key == 's' || key == 'S'|| key == GLUT_KEY_DOWN){
            //
        }
        else if (key == 'd' || key == 'D'|| key == GLUT_KEY_RIGHT){
            //
        }
    }
    static void timer(int value) {
        // перерисовка
        glutPostRedisplay();
        // таймер на секунду
        glutTimerFunc(1000, timer, 0);
    }

public:
    Window(int** grid) : grid(grid) {
        // Инициализация OpenGL
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
        glutInitWindowSize(::width, ::height);
        glutCreateWindow("Grid Window");

        // Ура колбэки
        // о нет, колбэки
        glutDisplayFunc(display);

        // Reshape
        glutReshapeFunc(reshape);

        currentGrid = grid;

        glutTimerFunc(1000, timer, 0); // запуск таймера
    }

    void run() {
        // GLUT main loop
        glutKeyboardFunc(keyboard);
        glutMainLoop();
    }

    // деструктор просто чтобы был
    ~Window() {
        for (int i = 0; i < width; i++) {
            delete[] grid[i];
        }
        delete[] grid;
    }
    
};

// ТОЛЬКО ИСПРАВИТЬ И РАСШИРИТЬ ЭТОТ КЛАСС,
// ПЕРЕПИШИ КОНСТРУКТОР НА int**, Я ЭТО ДЕЛАЛ ПОЛУПЬЯНО
// Будет вызываться в другом месте.

int** Window::currentGrid = nullptr;

// пример мейна чисто чтобы был, а то мне не нравится что у меня даже мейна нет(
int main(int argc, char* argv[]) {
    // инициализация GLUT 
    glutInit(&argc, argv);

    // грид со случайными значениями, ну а че
    int** grid = new int*[width];
    for (int i = 0; i < width; i++) {
        grid[i] = new int[height];
        for (int j = 0; j < height; j++) {
            grid[i][j] = rand() % 5;
        }
    }

    Window window(grid);
    window.run();

    return 0;
}