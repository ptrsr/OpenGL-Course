 #include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

#include "ShaderUtil.h"

/**
 * In this sample we switch to using the basics of the programmable pipeline of opengl without using VBO's yet.
 * We'll show those in the next sample.
 */

const GLfloat vertices[] = {
    0.75f ,  -0.75f, 0, 1,
    0.75f ,  0.75f , 0, 1,
    -0.75f,  -0.75f, 0, 1,
    -0.75f,  0.75f , 0, 1,
    -0.75f,  -0.75f, 0, 1,
    0.75f ,  0.75f , 0, 1
};

const GLfloat uvs[] = {
    1,0,
    1,1,
    0,0,
    0,1,
    0,0,
    1,1
};

int main () {
    sf::Window window(sf::VideoMode (800, 600), "Assignment 1");
    window.setVerticalSyncEnabled( true );

	//Initializing glew
    cout << "Initializing GlEW..." << endl;
    bool glewInitResult = (glewInit() == GLEW_OK);
    cout << "GlEW Initialized:" << glewInitResult  << endl;

	//Creating and assigning a program made from the vertex and fragment shader
    GLuint programID = ShaderUtil::createProgam("vertexshader.vs", "fragmentshader.fs");
    glUseProgram (programID);

	//creating vertex buffer
    GLuint vertexBufferId;
    glGenBuffers (1, &vertexBufferId);
    glBindBuffer (GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer (GL_ARRAY_BUFFER, 0);

	//craeting fragment buffer
    GLuint uvBufferId;
    glGenBuffers (1, &uvBufferId);
    glBindBuffer (GL_ARRAY_BUFFER, uvBufferId);
    glBufferData (GL_ARRAY_BUFFER, sizeof (uvs), uvs, GL_STATIC_DRAW);
    glBindBuffer (GL_ARRAY_BUFFER, 0);

    glClearColor(0,0,0,1);

	//get handles for attributes in program
    GLint vertexIndex = glGetAttribLocation(programID, "vertex");
    GLint offsetIndex = glGetUniformLocation(programID, "offset");
    GLint uvIndex = glGetAttribLocation(programID, "uv");
    GLint checkercountIndex = glGetUniformLocation(programID, "checkerCount");
    GLint mouseposIndex = glGetUniformLocation(programID, "mousepos");


    while (window.isOpen()) {
        glClear( GL_COLOR_BUFFER_BIT );

		//parse the offset to the shader
        GLfloat offset[] = {0.25f * cos (clock()/500.0f), 0.25f * sin (clock()/500.0f)};
        glUniform2fv (offsetIndex, 1, offset);

		//parse the checkercount to the shader
        GLfloat checkercount = 20;
        glUniform1f(checkercountIndex, checkercount);

		//parse the mouseposition to the shader
        GLfloat mousepos[] = {sf::Mouse::getPosition(window).x, window.getSize().y - sf::Mouse::getPosition(window).y};
        glUniform2fv(mouseposIndex, 1, mousepos);

        glEnableVertexAttribArray(vertexIndex);
        glBindBuffer (GL_ARRAY_BUFFER, vertexBufferId);
        glVertexAttribPointer(vertexIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);

        glEnableVertexAttribArray(uvIndex);
        glBindBuffer (GL_ARRAY_BUFFER, uvBufferId);
        glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glDrawArrays( GL_TRIANGLES, 0, 6);

        glDisableVertexAttribArray(vertexIndex);
        glDisableVertexAttribArray(uvIndex);

        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::Resized) glViewport(0, 0, event.size.width, event.size.height);
        }
    }

    return 0;
}

