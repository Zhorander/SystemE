/*
 *  System E is a general use 2D game engine mostly built for learning
 *  Copyright (C) 2018  Elias Flores
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  contact information: elias_50@live.com
 */

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

