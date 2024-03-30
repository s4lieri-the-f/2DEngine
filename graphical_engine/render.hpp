//учитывая что у меня несчастный мак, которому не нравится glut, надеюсь это компилится 
#include "GL/glut.h"

class Window {
    int width;
    int height;
    int **grid;

    static Window* currentInst; //указатель чтобы в display передавались стат данные
    
    static void display()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        float cellWidth = 2.0f / currentInst->width;
        float cellHeight = 2.0f / currentInst->height;

        for (int i = 0; i < currentInst->width; i++)
        {
            for (int j = 0; j < currentInst->height; j++)
            {

                int value = currentInst->grid[i][j];
                glColor3f(value / 255.0f, value / 255.0f, value / 255.0f);

                float x = -1.0f + i * cellWidth;
                float y = -1.0f + j * cellHeight;

                glBegin(GL_QUADS);
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

public:
    Window(int width, int height, int** grid) : width(width), height(height), grid(grid) {
        // Инициализация OpenGL
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
        glutInitWindowSize(width, height);
        glutCreateWindow("Grid Window");

        // Ура колбэки
        // о нет, колбэки
        glutDisplayFunc(display);

        // Reshape
        glutReshapeFunc(reshape);

        currentInst = this;
    }

    void run() {
        // GLUT main loop
        glutKeyboardFunc(keyboard);
        glutMainLoop();
    }
    
};

// ТОЛЬКО ИСПРАВИТЬ И РАСШИРИТЬ ЭТОТ КЛАСС,
// ПЕРЕПИШИ КОНСТРУКТОР НА int**, Я ЭТО ДЕЛАЛ ПОЛУПЬЯНО
// Будет вызываться в другом месте.

Window* Window::currentInst = nullptr;

// пример мейна чисто чтобы был, а то мне не нравится что у меня даже мейна нет(
int main() {
    int width = 800;
    int height = 600;
    int** grid; 
    // несчастный грид

    Window window(width, height, grid);
    window.run();

    return 0;
}