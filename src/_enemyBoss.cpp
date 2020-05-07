#include "_enemyBoss.h"

_enemyBoss::_enemyBoss()
{
    //ctor
    //Same constructor as regular enemy
    xPos = yPos = 0.0;
    zPos = -4.85;
    xSize = ySize = 0.5;

    rotateX = rotateY = rotateZ = 0.0;

    frames = 1;
    xMin = yMin = 0.0;
    xMax = 1.0/(float)frames;
    yMax = 1.0;
    action = 0;

    xMove = yMove = 0.0;
    theta = 30 * (PI/180);
    v=35;
    t=0;

    health = 35;
    cycles = 0;
    redeployed = false;
}

_enemyBoss::~_enemyBoss()
{
    //dtor
}

void _enemyBoss::actions()
{
  switch (action)
  {
    //Movement case
    case 0:
      if(xPos<=-1.75) xMove *= -1;
      else if (xPos>1.75) xMove *= -1;
      xPos += xMove;
      yPos += yMove;
      if (TE->getTicks()>=5000){
        action++;
        cout << "Boss action is now: " << action << endl;
        TE->reset();
      }
      break;

    //Attack prep case
    case 1:
      if (TE->getTicks()>=500){
        action++;
        cout << "Boss action is now: " << action << endl;
        TE->reset();
      }
      break;

    //Attack case
    case 2:
      if (TE->getTicks()%1000 == 0) shoot();
      if (TE->getTicks() >= 10000){
        action++;
        cout << "Boss action is now: " << action << endl;
        TE->reset();
      }
      break;

    //Attack cool down case
    case 3:
      ;
      if (TE->getTicks() >= 500){
        cycles++;
        redeployed = false;
        action = 0;
        cout << "Boss action is now: " << action << endl;
        TE->reset();
      }
      break;
  }

  //Enemy bullet management
  for (int i = 0; i < bullets.size(); i++){
    if (!bullets.at(i)->expired()){
      bullets.at(i)->move();
      bullets.at(i)->draw();
    }
    else {
      _projectile *bullet = bullets.at(i);
      bullets.erase(bullets.begin()+i);
      i -=1;
      delete bullet;
    }
  }

  drawEnemy();
}

void _enemyBoss::shoot(){
  //Fires 3 bullets in a cone
  _projectile *bullet1 = new _projectile();
  _projectile *bullet2 = new _projectile();
  _projectile *bullet3 = new _projectile();

  //Bullet sizes and positions
  bullet1->xSize = bullet1->ySize = bullet2->xSize = bullet2->ySize = bullet3->xSize = bullet3->ySize = 0.2;
  bullet1->xPos = bullet2->xPos = bullet3->xPos = (xPos*.8) + 0.05;
  bullet1->yPos = bullet2->yPos = bullet3->yPos = (yPos*.8) - 0;

  //Bullet speeds
  bullet1->speed = bullet2->speed = bullet3->speed = 0.0025;

  //Make bullets hostile to player
  bullet1->isHostile = bullet2->isHostile = bullet3->isHostile = true;

  //Bullet velocities
  bullet1->yMove -= bullet1->speed;
  bullet2->yMove -= bullet2->speed;
  bullet2->xMove -= bullet2->speed;
  bullet3->yMove -= bullet3->speed;
  bullet3->xMove += bullet3->speed;

  bullet1->init("images/PlayerProjectile.png");
  bullet2->init("images/PlayerProjectile.png");
  bullet3->init("images/PlayerProjectile.png");

  bullets.push_back(bullet1);
  bullets.push_back(bullet2);
  bullets.push_back(bullet3);
}

bool _enemyBoss::isDead(){
  return health <= 0;
}
