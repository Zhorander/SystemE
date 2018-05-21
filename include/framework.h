//framework.h

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
