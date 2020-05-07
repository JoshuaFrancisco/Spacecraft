#include "menu.h"
#include <_textureLoader.h>

_textureLoader *mTex = new _textureLoader();
//similar to parallax but without scroll

menu::menu()
{
    //ctor
    Xmax= 1.0f;
    Ymax= 0.0f;
    Xmin= 0.0f;
    Ymin= 1.0f;
}

menu::~menu()
{
    //dtor
}

void menu::drawMenu(float width, float height)
{
    glColor3f(1.0,1.0,1.0);
    mTex->TextureBinder();
    glBegin(GL_POLYGON);
        glTexCoord2f(Xmin,Ymin);
        glVertex3f(-width/height,-1,0);

        glTexCoord2f(Xmax,Ymin);
        glVertex3f(width/height,-1,0);

        glTexCoord2f(Xmax,Ymax);
        glVertex3f(width/height,1,0);

        glTexCoord2f(Xmin,Ymax);
        glVertex3f(-width/height,1,0);
     glEnd();
}

void menu::menuInit(char *fileName)
{
    mTex->TextureBinder();
    mTex->loadTexture(fileName);
}
