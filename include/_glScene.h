
#ifndef _GLSCENE_H
#define _GLSCENE_H

#include <windows.h>
#include<GL/glut.h>

#include<iostream>

using namespace std;

class _glScene
{
    public:
        _glScene();               // constructor
        virtual ~_glScene();      // Deconstructor
        GLint initGL();           // initialize OpenGL
        GLint drawScene();        // Renderer
        GLvoid reSizeScene(GLsizei, GLsizei); // screen size changes

        //game states identify which screen the game is in
        //enum gameState{ isSplash = 0, isMenu = 1, isPlay = 2, isHelp = 3};
        enum gameState{ isSplash = 0, isMenu = 1, isPlay = 2, isHelp = 3, isOver = 4, isCredits = 5};
        gameState state = isSplash; //initialize state to splash

        int winMsg(HWND, UINT, WPARAM, LPARAM);	// Callback of inputs

        //WPARAM wParm;

        float screenHeight, screenWidth; // to map background images
    protected:

    private:
};

#endif // _GLSCENE_H
