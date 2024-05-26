#ifndef RENDER_HPP
#define RENDER_HPP

#include <GL/gl.h>
#include <GL/glut.h>
#include <unordered_map>
#include <iostream>
#include <tuple>

// Global constants for window dimensions
const int width = 600;
const int height = 600;

class Window
{
public:
    int **grid;
    int n, m;

    static int **currentGrid; // to store current grid data
    static int currentN, currentM;

    void updateGrid(int **newGrid)
    {
        currentGrid = newGrid;
    }

    static void display()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        float cellWidth = 2.0f / currentN;
        float cellHeight = 2.0f / currentM;

        for (int i = 0; i < currentN; ++i)
        {
            for (int j = 0; j < currentM; ++j)
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
                    glBegin(GL_LINE_LOOP); // unfilled square
                else
                    glBegin(GL_QUADS); // filled square

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

    Window(int size, int **grid) : grid(grid), n(size), m(size)
    {
        currentGrid = grid;
        currentN = n;
        currentM = m;

        // Initialize OpenGL
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
        glutInitWindowSize(::width, ::height);
        glutCreateWindow("Grid Visualization");

        // Set callback functions
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
    }

    void run()
    {
        glutMainLoop();
    }

    ~Window()
    {
        for (int i = 0; i < n; ++i)
        {
            delete[] grid[i];
        }
        delete[] grid;
    }

private:
    static std::unordered_map<int, std::tuple<GLfloat, GLfloat, GLfloat>> hashMap;
};

std::unordered_map<int, std::tuple<GLfloat, GLfloat, GLfloat>> Window::hashMap = {
    {0, {0.0f, 0.0f, 0.0f}}, // black, empty cell
    {1, {0.0f, 0.0f, 1.0f}}, // blue
    {2, {1.0f, 0.0f, 0.0f}}, // red
    {3, {0.0f, 1.0f, 0.0f}}, // green
    {4, {1.0f, 1.0f, 0.0f}}, // yellow
};

int **Window::currentGrid = nullptr;
int Window::currentN = 0;
int Window::currentM = 0;

#endif // RENDER_HPP
