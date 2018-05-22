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

#pragma once

#include <SFML/Graphics.hpp>
//#include "json.hpp"

namespace Framework {

    class Window;
    class WindowObserver;
    class VertexBufferObject;

    typedef sf::RenderWindow RenderWindow;
    typedef sf::Event event;
    typedef sf::Event::EventType input_type;
    typedef sf::Color Color;
    typedef sf::Drawable Drawable;
    typedef sf::Vertex Vertex;
    typedef sf::VertexBuffer VertexBuffer;
    typedef sf::VertexArray VertexArray;
    typedef sf::Vector2f Vector2f;

    class WindowObserver {
    public:
        virtual void notify(event e);
    };

    /** VertexBufferObject
     * Wrapper around sfml's VertexBuffer class
     */
    class VertexBufferObject {
    public:
        VertexBufferObject();
        VertexBufferObject(Vertex *vertArray);
        ~VertexBufferObject();
        void update(Vertex *vertArray);
        void draw(Window *win);
    private:
        VertexBuffer *vb;
    };

    class Window {
    public:
        Window();
        Window(int height, int width, std::string title);
        ~Window();
        void closeWindow();
        void print(RenderWindow *win, int x, int y, std::string msg);
        void clearWindow();
        void displayWindow();
        bool isOpen();
        void clearWindow(int r, int g, int b);
        void clearWindow(int r, int g, int b, int a);
        void setInputHandler(WindowObserver *in);
        event getNextEvent();
        bool pollEvent(event *e);
    private:
        RenderWindow *win;
        event window_event;
        void createWindow(int height, int width, std::string name);
    };

    class Sound {
    public:
        void play_sound ();
    };

    namespace Utilities {
    };
};
