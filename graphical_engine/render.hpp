#include <GL/glut.h>

class Window {
    int width;
    int height;
    int **grid;

    static void display()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        float cellWidth = 2.0f / width;
        float cellHeight = 2.0f / height;

        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {

                int value = grid[i][j];
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
        switch (key)
        {
        case 'w':
        case 'W':
        case GLUT_KEY_UP:
            // 
            break;
        case 'a':
        case 'A':
        case GLUT_KEY_LEFT:
            // 
            break;
        case 's':
        case 'S':
        case GLUT_KEY_DOWN:
            // 
            break;
        case 'd':
        case 'D':
        case GLUT_KEY_RIGHT:
            // 
            break;
        }
    }

public:
    Window(int width, int height, int** grid) : width(width), height(height), grid(grid) {
        // Инициализация OpenGL
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
        glutInitWindowSize(width, height);
        glutCreateWindow("Grid Window");

        // Ура колбэки
        glutDisplayFunc(display);

        // Reshape
        glutReshapeFunc(reshape);
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