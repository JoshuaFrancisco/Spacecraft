#include "_enms.h"
#include <math.h>
#include <cstdlib>

_enms::_enms()
{
    //ctor
    xPos = yPos = 0.0;
    zPos = -4.95;

    xSize = 1.0;
    ySize = 0.5;

    rotateX=rotateY=rotateZ = 0.0;
    frames = 1;

    xMin=yMin=0.0;
    xMax=1.0/(float)frames;
    yMax=1.0;
    action =0;

    xMove= 0.005;

    theta =30*(PI/180);
    v=35;
    t=0;
}

_enms::~_enms()
{
    //dtor
}
void _enms::drawEnemy()
{

    glBindTexture(GL_TEXTURE_2D, EnemyTex);

    glPushMatrix(); // can do this in the scene
        glTranslatef(xPos,yPos,zPos);
        glRotatef(rotateX,1.0,0.0,0.0);
        glRotatef(rotateY,0.0,1.0,0.0);
        glRotatef(rotateZ,0.0,0.0,1.0);
        glScalef(xSize,ySize,1);

    glBegin(GL_POLYGON);
        glTexCoord2f(xMin,yMin);
        glVertex3f(1.0, 1.0, 0.0);
        glTexCoord2f(xMax,yMin);
        glVertex3f(-1.0, 1.0, 0.0);
        glTexCoord2f(xMax,yMax);
        glVertex3f(-1.0, -1.0, 0.0);
        glTexCoord2f(xMin,yMax);
        glVertex3f(1.0, -1.0, 0.0);
    glEnd();

    glPopMatrix();
}

void _enms::placeEnemy(float x, float y , float z)
{
        xPos = x;
        yPos = y;
        zPos = z;
}

void _enms::placeRandomly()
{
    //xPos = rand()/float(RAND_MAX)*5-2.5;
    xPos = (rand()%20*.1)-0.5;
    yPos = (rand()%25*.35)+1.5;
    zPos = -4.95;
}


void _enms::initEnemy(GLuint tex)
{
        EnemyTex = tex;
        TE->start();
}

void _enms::actions()
{
    drawEnemy();
}

void _enms::kill()
{
    xPos = yPos = 100;
    xMove = yMove = 0;
}
