
#ifndef _GLSCENE_H
#define _GLSCENE_H

#include <windows.h>
#include<GL/glut.h>
#include <_Model.h>
#include <_inputs.h>
#include <_parallax.h>
#include <_player.h>
#include <_enms.h>
#include <_checkCollision.h>
#include <_sound.h>
#include <menu.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class _glScene
{
    public:
        _glScene();               // constructor
        virtual ~_glScene();      // Deconstructor
        GLint initGL();           // initialize OpenGL
        GLint drawScene();        // Renderer
        GLvoid reSizeScene(GLsizei, GLsizei); // screen size changes

        //Manage levels
        bool doneLoading, level1, level2, level3;
        int kills = 0;

        //Game states identify which screen the game is in
        enum gameState{isSplash = 0, isMenu = 1, isPlay = 2, isHelp = 3, isOver = 4, isCredits = 5, isWin = 6};
        gameState state = isSplash; //initialize state to first cut scene

        //WPARAM wParm;
        int winMsg(HWND, UINT, WPARAM, LPARAM);	// Callback of inputs

        float screenHeight, screenWidth; // to map background images

        //Game objects
        _Model *myModel = new _Model();
        _inputs *kBMs = new _inputs();
        _parallax *plxSky = new _parallax();
        _parallax *plxFloor = new _parallax();
        _player *ply = new _player();
        _checkCollision *hit = new _checkCollision();
        _sound *snds = new _sound();

        //Menus
        menu *mnu = new menu();
        menu *splash = new menu();
        menu *hlp = new menu();
        menu *over = new menu();
        menu *cred = new menu();
        menu *win = new menu();

        //Cut scenes
        bool intro1 = true, intro2 = false, intro3 = false, spl = false;

        //Enemy texture loaders
        _textureLoader *enmsTex = new _textureLoader();
        _textureLoader *enmsTex2 = new _textureLoader();
        _textureLoader *bossTex = new _textureLoader();

        //Enemies
        _enms enms[5];
        _enms enms2[10];
        _enms boss[1];

    protected:
    private:
};

#endif // _GLSCENE_H
