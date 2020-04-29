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

    runSpeed =0;
    jumpSpeed =0;

    xPos=0.0;   //x position of the Player
    yPos=-2.0;   //y position of the Player
    zPos=-5.0;   //z position of the Player

    xSize =1.0;
    ySize =1.0;

    xRotation=0.0;
    yRotation=0.0;
    zRotation=0.0;

    action =-1;

    frames = 1;
    xMin=0.0;
    yMin=0.0;
    yMax=1.0;
    xMax=1.0;
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

    switch(action)
    {

        case 0: //left arrow
                if(tmr->getTicks()>60)
                {
                xMin+=1.0/frames*-1;
                xMax+=1.0/frames*-1;
                yMax=0.333;
                xMax=-1.0;
                if(xMax>=1){xMin=0.0; xMax=1/frames;}

                tmr->reset();
                }

            break;
        case 1: //right arrow
            if(tmr->getTicks()>60)
                {
                //xMin+=1.0/frames;
                xMin+=1.0/frames;
                xMax+=1.0/frames;
                yMax=0.333;
                xMax=-1.0;
                if(xMax>=1){xMin=1.0/frames; xMax=0.0/frames;}

                tmr->reset();
                }
            break;

        case 3:
            frames =1;
            xMin=1;
            yMin=-0.5;
            yMax=0.333;
            xMax=-1.0;
            break;


    }
    //Manages bullets
    for (int i = 0; i < bullets.size(); i++){
      if (!bullets.at(i)->expired()) {
        bullets.at(i)->move();
        bullets.at(i)->draw();
      }
      else {
        delete bullets.at(i);
        bullets.erase(bullets.begin()+i);
      }
    }


}

void _player::shoot(){
  _projectile *bullet = new _projectile();
  bullet->xSize = bullet->ySize = 0.20;
  //The following numbers are relative to sprite and player location on screen
  bullet->xPos = xPos + 0.0;
  bullet->yPos = yPos + 2.35;
  bullet->maxDistance = 300; // How far the bullet travels before disapear
  if (direction == "right") bullet->xMove = 0.01;
  else if (direction == "left") bullet->xMove = -0.01;
  else if (direction == "up") bullet->yMove = 0.01;
  else if (direction == "down") bullet->yMove = -0.01;
  bullet->init("images/PlayerProjectile.png");
  bullets.push_back(bullet);
}


