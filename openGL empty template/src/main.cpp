#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

/**
 * Default OpenGL template
 */
int main () {
    sf::Window window(sf::VideoMode (800, 600), "Wawsom!", sf::Style::Default, sf::ContextSettings(24, 0, 0, 3, 3));
    window.setVerticalSyncEnabled( true );

    GLenum glewResult = glewInit();
    if (glewResult != GLEW_OK) {
        cout << "Could not initialize glew, byeeee!" << endl;
        return -1;
    }

    //TODO: your OpenGL setup code, load models, create shaders, go crazy

    while (window.isOpen()) {

        //TODO: render selected opengl models etc to the back framebuffer

        //SFML is double buffered by default, switch front & back buffers,
        //so that everything in the back buffer is now on screen:
        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::Resized) glViewport(0, 0, event.size.width, event.size.height);
        }
    }

    return 0;
}


