#include "projectiles.h"
_textureLoader *Tt = new _textureLoader();

_projectile::_projectile()
{
    //ctor
    verticies[0].x=0.0; verticies[0].y=0.0;verticies[0].z=-1.0;
    verticies[1].x=1.0; verticies[1].y=0.0;verticies[1].z=-1.0;
    verticies[2].x=1.0; verticies[2].y=1.0;verticies[2].z=-1.0;
    verticies[3].x=0.0; verticies[3].y=1.0;verticies[3].z=-1.0;
    xSize = ySize = 0.25;
    xPos = yPos = xMove = yMove = xMin = yMin = 0.0;
    zPos = -4.85;
    xMax = yMax = 1.0;
    distTraveled = maxDistance = 0;
}

_projectile::~_projectile()
{
    //dtor
}

void _projectile::init(char *fileName)
{
   // T->TextureBinder();
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    Tt->loadTexture(fileName);
}

void _projectile::draw(){
    glColor3f(1.0,1.0,1.0);
    Tt->TextureBinder();
    glPushMatrix();

    glTranslatef(xPos,yPos,zPos);
    glRotatef(0.0,1.0,0.0,0.0);
    glRotatef(0.0,0.0,1.0,0.0);
    glRotatef(0.0,0.0,0.0,1.0);
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

void _projectile::move(){
  distTraveled += speed;
  //xPos += speed;
  yPos += speed;
}

bool _projectile::expired(){
  return distTraveled >= maxDistance;
}
