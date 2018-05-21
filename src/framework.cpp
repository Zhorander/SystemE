//framework.cpp

#include "framework.h"

using namespace Framework;

/*--------------WINDOWOBSERVER-------------*/

void WindowObserver::notify(event e){}

/*--------------VERTEXBUFFEROBJECT---------*/

VertexBufferObject::VertexBufferObject()
{
    vb = new VertexBuffer(sf::Triangles);
}

VertexBufferObject::VertexBufferObject(Vertex *vertArray)
{
    vb = new VertexBuffer(sf::Triangles);
}

void VertexBufferObject::update(Vertex *vertArray)
{
}

void VertexBufferObject::draw(Window *win)
{
}

VertexBufferObject::~VertexBufferObject()
{
    delete vb;
}

/*--------------WINDOW---------------------*/

Window::Window()
{
    createWindow(480, 480, "System E");
}

Window::Window(int height, int width, std::string name)
{
    createWindow(height, width, name);
}

/** create_window
 * Initializes the window
 * The specific window shouldn't matter to the engine
 */
void Window::createWindow(int height, int width, std::string name)
{
    win = new RenderWindow(sf::VideoMode(height, width), "hello world!");
}

bool Window::isOpen()
{
    return win->isOpen();
}

/** closeWindow
 * close an open window
 */
void Window::closeWindow()
{
    if (win != nullptr) {
        win->close();
        delete win;
    }
}

/** clearWindow
 * clear the window
 * with either no arguments, rgb, or rgba
 */
void Window::clearWindow()
{
    win->clear();
}

void Window::displayWindow()
{
    win->display();
}

void Window::clearWindow(int r, int g, int b)
{
    win->clear(Color(r, g, b));
}

void Window::clearWindow(int r, int g, int b, int a)
{
    win->clear(Color(r, g, b, a));
}

event Window::getNextEvent()
{
    if (win && !win->waitEvent(window_event)) {
        fprintf(stderr, "Error: error getting window event\n");
    }

    return window_event;
}

bool Window::pollEvent(event *e)
{
    return win->pollEvent(*e);
}

Window::~Window()
{
    if (win != NULL && win != nullptr)
        delete win;
}

