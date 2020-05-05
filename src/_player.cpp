#include "_player.h"

_textureLoader *T= new _textureLoader();
_timer *tmr = new _timer();


_player::_player()
{
    //ctor
    verticies[0].x=0.0; verticies[0].y=0.0;verticies[0].z=-1.0;
    verticies[1].x=1.0; verticies[1].y=0.0;verticies[1].z=-1.0;
    verticies[2].x=1.0; verticies[2].y=1.0;verticies[2].z=-1.0;
    verticies[3].x=0.0; verticies[3].y=1.0;verticies[3].z=-1.0;

    xPos = 0.0;   //x position of the Player
    yPos = -2.0;   //y position of the Player
    zPos = -5.0;   //z position of the Player
    xMin = yMin = 0.0;
    yMax = xMax = 1.0;
    xSize = ySize = 1.0;
    xRotation, yRotation, zRotation=0.0;
    xMove = yMove = speed = 0.005;
    movingLeft = movingRight = movingUp = movingDown = false;
    action =-1;
    frames = 1;
}

_player::~_player()
{
    //dtor
}

void _player::placePlayer()
{

}

void _player::drawPlayer()
{
    glColor3f(1.0,0.0,0.0);
   // glPushMatrix();  //ouping the Quad
    T->TextureBinder();

    glTranslatef(xPos,yPos,zPos);
    glRotatef(xRotation,1.0,0.0,0.0);
    glRotatef(yRotation,0.0,1.0,0.0);
    glRotatef(zRotation,0.0,0.0,1.0);
    glScalef(xSize,ySize,1);

    glBegin(GL_QUADS);
      glTexCoord2f(xMin,yMax);
      glVertex3f(verticies[0].x, verticies[0].y,verticies[0].z);
      glTexCoord2f(xMax,yMax);
      glVertex3f(verticies[1].x, verticies[1].y,verticies[1].z);
      glTexCoord2f(xMax,yMin);
      glVertex3f(verticies[2].x, verticies[2].y,verticies[2].z);
      glTexCoord2f(xMin, yMin);
      glVertex3f(verticies[3].x, verticies[3].y,verticies[3].z);
    glEnd();
  //  glPopMatrix();

}

void _player::initPlayer(char *fileName)
{
   // T->TextureBinder();


   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    T->loadTexture(fileName);
    tmr->start();
}

void _player::actions()
{
    if(movingLeft) xPos -= xMove;
    if(movingRight) xPos += xMove;
    if(movingDown) yPos -= yMove;
    if(movingUp) yPos += yMove;
    //Manages bullets
    for (int i = 0; i < bullets.size(); i++){
      if (!bullets.at(i)->expired()) {
        bullets.at(i)->move();
        bullets.at(i)->draw();
      }
      else {
        _projectile *bullet = bullets.at(i);
        bullets.erase(bullets.begin()+i);
        i -= 1;
        delete bullet;
      }
    }
}

void _player::shoot(){
  _projectile *bullet = new _projectile();
  bullet->xSize = bullet->ySize = 0.20;
  //The following numbers are relative to sprite and player location on screen
  bullet->xPos = (xPos*.8) + 0.4;
  bullet->yPos = (yPos*.8) + 0.5;
  bullet->maxDistance = 1.5; // How far the bullet travels before disapear
  //if (direction == "right") bullet->xMove = 0.01;
  //else if (direction == "left") bullet->xMove = -0.01;
  //else if (direction == "up") bullet->yMove = 0.003;
  //else if (direction == "down") bullet->yMove = -0.01;
  if (direction == "right") bullet->xMove = bullet->speed;
  else if (direction == "left") bullet->xMove -= bullet->speed;
  else if (direction == "up") bullet->yMove = bullet->speed;
  else if (direction == "down") bullet->yMove -= bullet->speed;
  bullet->init("images/PlayerProjectile.png");
  bullets.push_back(bullet);
}
