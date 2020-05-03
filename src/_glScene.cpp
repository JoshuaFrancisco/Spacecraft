#include "_glScene.h"
#include <_glLight.h>
#include <_Model.h>
#include <_inputs.h>
#include <_parallax.h>
#include <_player.h>
#include <_enms.h>
#include <_checkCollision.h>
#include <_sound.h>
#include <menu.h>
#include <iostream>

using namespace std;

_Model *myModel = new _Model();
_inputs *kBMs = new _inputs();
_parallax *plxSky = new _parallax();
_parallax *plxFloor = new _parallax();
_player *ply = new _player();
_checkCollision *hit = new _checkCollision();
_sound *snds = new _sound();

menu *mnu = new menu();
menu *splash = new menu();
menu *hlp = new menu();
menu *over = new menu();
menu *cred = new menu();

_textureLoader *enmsTex = new _textureLoader();
_enms enms[5];

_glScene::_glScene()
{
  //ctor
  screenWidth = GetSystemMetrics(SM_CXSCREEN);
  screenHeight = GetSystemMetrics(SM_CYSCREEN);
}

_glScene::~_glScene()
{
  //dtor
}
GLint _glScene::initGL()
{

  glShadeModel(GL_SMOOTH);    // to make graphics nicer
  glClearColor(1.0f,0.5f,0.0f,1.0f); // background color R,G,B,Alpha
  glClearDepth(1.0f);          // Depth Clearance
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);


  _glLight Light(GL_LIGHT0);

  myModel->initModel();
  enmsTex->loadTexture("images/enemy-03.png");
  plxSky->parallaxInit("images/stage-back.png");
  //plxFloor->parallaxInit("images/asteroid-01.png");
  ply->initPlayer("images/ship-02.png");
  ply->xPos = -0.5; //changes x position
  ply->yPos = -1.5; //change y position
  //ply->zPos = -2.0; //change z position, changes the size of player
  //glEnable(GL_COLOR_MATERIAL);

  for (int i = 0; i <sizeof(enms)/sizeof(enms[0]); i++)
  {
    enms[i].initEnemy(enmsTex->tex);
    enms[i].placeRandomly();
    //enms[i].placeEnemy((float)(rand()/float(RAND_MAX))*5-2.5,(float)(rand()/float(RAND_MAX))*3+2,-2.5);
    //enms[i].placeEnemy((float)(rand()/float(RAND_MAX))*5-2.5,-0.2,-2.5);
    enms[i].xMove = (float) (rand()/float(RAND_MAX))/100;
    enms[i].xSize = enms[i].ySize = 0.1;

    if (rand()%1 == 1) enms[i].xMove *= -1;
    enms[i].yMove = -0.0005;
  }

  snds->initSounds();
  snds->playMusic("sounds/background-music.mp3");
  return true;

}

GLint _glScene::drawScene()
{
  switch(state) {
    //splash screen
    case isSplash:
    {
      splash->menuInit("images/splash.png"); //load image for splash, 1920 x 1080 image
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
      glLoadIdentity();									// Reset The Current Modelview Matrix
      glPushMatrix();
      glTranslated(0,0,-4.5); //move image back
      glScalef(2,2,1); //scale image
      splash->drawMenu(screenWidth, screenHeight); //draw splash
      glPopMatrix();
      break;
    }

    //main menu
    case isMenu:
    {
      mnu->menuInit("images/menu.png"); //load image for menu, 1920 x 1080 image
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
      glLoadIdentity();									// Reset The Current Modelview Matrix
      glPushMatrix();
      glTranslated(0,0,-4.0); //move image back
      glScalef(2,2,1); //scale image
      mnu->drawMenu(screenWidth, screenHeight); //draw main menu
      glPopMatrix();
      break;
    }

    //help menu
    case isHelp:
    {
      hlp->menuInit("images/help.png"); //load image for help
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
      glLoadIdentity();									// Reset The Current Modelview Matrix
      glPushMatrix();
      glTranslated(0,0,-4.0); //move image back
      glScalef(2,2,1); //scale image
      hlp->drawMenu(screenWidth, screenHeight); //draw help
      glPopMatrix();
      break;
    }
    //credits menu
    case isCredits:
    {
      cred->menuInit("images/credits.png"); //load image for credits
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear Screen And Depth Buffer
      glLoadIdentity();                                    // Reset The Current Modelview Matrix
      glPushMatrix();
      glTranslated(0,0,-4.0); //move image back
      glScalef(2,2,1); //scale image
      cred->drawMenu(screenWidth, screenHeight); //draw credits
      glPopMatrix();
      break;
    }
    //game over
    case isOver:
    {
      over->menuInit("images/gameover.png");
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Clear Screen And Depth Buffer
      glLoadIdentity();                                    // Reset The Current Modelview Matrix
      glPushMatrix();
      glTranslated(0,0,-4.0); //move image back
      glScalef(2,2,1); //scale image
      mnu->drawMenu(screenWidth, screenHeight); //draw main menu
      glPopMatrix();

      //Resets enemies for New game
      for (int i = 0; i <sizeof(enms)/sizeof(enms[0]); i++)
      {
        enms[i].initEnemy(enmsTex->tex);
        enms[i].placeRandomly();
        //enms[i].placeEnemy((float)(rand()/float(RAND_MAX))*5-2.5,(float)(rand()/float(RAND_MAX))*3+2,-2.5);
        //enms[i].placeEnemy((float)(rand()/float(RAND_MAX))*5-2.5,-0.2,-2.5);
        enms[i].xMove = (float) (rand()/float(RAND_MAX))/100;
        enms[i].xSize = enms[i].ySize = 0.1;

        if (((float) (rand()/float(RAND_MAX))/100) == 1) enms[i].xMove *= -1;
        enms[i].yMove = -0.0005;
      }
      break;
    }

    case isPlay:
    {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
      glLoadIdentity();
      // glColor3f(1.0,0.0,0.0);              // setting colors

      glPushMatrix();
      glTranslated(0,0,-4.0);                    //placing objects
      glScalef(6.3,6.3,1);
      plxSky->drawSquare(screenWidth,screenHeight); // draw sky background
      plxSky->scroll(true,"up",0.0005);            // Automatic background movement

      //plxFloor->drawSquare(screenWidth,screenHeight); // draw floor background
      //plxFloor->scroll(true,"down",0.0005);            // Automatic background movement
      glPopMatrix();


      glPushMatrix();                      // grouping starts
      glTranslated(0,0,-8.0);              //placing objects
      myModel->drawModel();

      glPopMatrix();                       // grouping ends
      glPushMatrix();
      ply->actions();
      ply->drawPlayer();
      for (int i = 0; i < ply->bullets.size(); i++) ply->bullets.at(i)->draw();
      glPopMatrix();

      //Handles Enemy
      for (int i = 0; i <sizeof(enms)/sizeof(enms[0]); i++) {
        if(enms[i].xPos<=-1.75)
        {
          enms[i].action =0;
          enms[i].xMove *= -1;
          enms[i].rotateZ = 0;
        }
        else if (enms[i].xPos>=1.75)
        {
          enms[i].action = 1;
          enms[i].xMove *= -1;
        }
        enms[i].xPos += enms[i].xMove;
        enms[i].yPos += enms[i].yMove;

        //Game over check, prints in console, resets y position
        if(enms[i].yPos <= -.70 && enms[i].xPos>=-1.75 && enms[i].xPos<=1.75) {
          /* code */
          cout << "Game Over!" << endl;
          state = isOver;
          enms[i].yPos = 1.0;
        }

        //Handles Collision
        for (int j = 0; j < ply->bullets.size();j++)
        {
          if(ply->bullets.at(j)->yPos >= enms[i].yPos)
          {
            if((hit->isLinearCollision(ply->bullets.at(j)->xPos,enms[i].xPos)) && (hit->isLinearCollision(ply->bullets.at(j)->yPos,enms[i].yPos)))
            {
              cout << "enemy died" << endl;
              cout << "Bullet pos: " << ply->bullets.at(j)->xPos << "," << ply->bullets.at(j)->yPos << endl;
              cout << "Enemy pos: " << enms[i].xPos << "," << enms[i].yPos << endl;
              enms[i].placeRandomly();
              //delete ply->bullets.at(j);
              //ply->bullets.erase(ply->bullets.begin()+j);
            }
          }
          enms[i].actions();

        }

      }
    }
  }
}

GLvoid _glScene::reSizeScene(GLsizei width, GLsizei height)
{
  GLfloat aspectRatio = (GLfloat)width/(GLfloat) height; // ratio for window mode
  glViewport(0,0,width,height);                          // setting view port
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0,aspectRatio,0.1,100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
int _glScene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
    case WM_KEYDOWN:

    kBMs->wParam = wParam;
    //kBMs->keyPressed(myModel); //handling Model Movements
    kBMs->keyEnv(plxSky,0.0005);   //handling Env fast
    //kBMs->keyEnv(plxFloor,0.005);   //handling Env slow
    kBMs->keyPressed(ply);     // handling player movement
    kBMs->keyPressed(snds);
    break;

    case WM_KEYUP:
    kBMs->keyUp(ply);
    break;

    case WM_LBUTTONDOWN:
    kBMs->wParam = wParam;
    kBMs->mouseEventDown(myModel,LOWORD(lParam),HIWORD(lParam));
    if(state == isSplash){
      state = isMenu;
    }
    break;
    case WM_RBUTTONDOWN:
    kBMs->wParam = wParam;
    kBMs->mouseEventDown(myModel,LOWORD(lParam),HIWORD(lParam));
    break;
    case WM_MBUTTONDOWN:
    kBMs->wParam = wParam;
    kBMs->mouseEventDown(myModel,LOWORD(lParam),HIWORD(lParam));
    break;

    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    kBMs->mouseEventUp();
    break;

    case WM_MOUSEMOVE:
    kBMs->mouseMove(myModel,LOWORD(lParam),HIWORD(lParam));
    break;
    case WM_MOUSEWHEEL:
    kBMs->mouseWheel(myModel,(double)GET_WHEEL_DELTA_WPARAM(wParam));
    break;
  }
}
