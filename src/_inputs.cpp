#include "_inputs.h"

_inputs::_inputs()
{
    //ctor
    Mouse_Rotate=false;
    Mouse_Translate=false;
}

_inputs::~_inputs()
{
    //dtor
}

void _inputs::keyEnv(_parallax* plx, float speed)
{
    switch(wParam){
            case VK_LEFT:
            plx->xMin +=speed;
            plx->xMax +=speed;
            break;
        case VK_RIGHT:
            plx->xMin -=speed;
            plx->xMax -=speed;
             break;
        case VK_DOWN:
             plx->yMin +=speed;
             plx->yMax +=speed;
            break;
        case VK_UP:
            plx->yMin -=speed;
            plx->yMax -=speed;
            break;
    }
}

void _inputs::keyPressed(_Model* Mdl)
{
    switch(wParam)
    {
        case VK_LEFT:
            Mdl->rotateY +=1.0;
            break;
        case VK_RIGHT:
            Mdl->rotateY -=1.0;
             break;
        case VK_DOWN:
             Mdl->rotateX -=1.0;
            break;
        case VK_UP:
            Mdl->rotateX +=1.0;
            break;
        case VK_ADD:break;
            Mdl->posZ +=1.0;
        case VK_SUBTRACT: break;
            Mdl->posZ -=1.0;
    }
}

void _inputs::keyPressed(_player* ply)
{
        switch(wParam)
    {
       case VK_LEFT:
            //ply->distTraveled -= 1;
            //ply->direction = "left";
            /*
            if (ply->xPos > -2.5) {
              ply->action=0;
              ply->xPos-=.05;
            }
            */
            ply->movingLeft = true;
            ply->movingRight = false;
            ply->movingUp = false;
            ply->movingDown = false;
            break;
        case VK_RIGHT:
            //ply->distTraveled += 1;
            //ply->direction = "right";
            /*
            if (ply->xPos < 2.5){
              ply->action=1;
              ply->xPos+=.05;
            }
            */
            ply->movingLeft = false;
            ply->movingRight = true;
            ply->movingUp = false;
            ply->movingDown = false;
            break;
        case VK_DOWN:
            //ply->direction = "down";
            //if (ply->yPos > -2) ply->yPos-=.05;
            ply->movingLeft = false;
            ply->movingRight = false;
            ply->movingUp = false;
            ply->movingDown = true;
            break;
        case VK_UP:
            //ply->direction = "up";
            //if (ply->yPos < 2) ply->yPos+=.05;
            ply->movingLeft = false;
            ply->movingRight = false;
            ply->movingUp = true;
            ply->movingDown = false;
            break;
        case VK_SPACE:
            //shoot
            ply->shoot();
            break;
        case VK_RETURN:
            break;
    }
}


void _inputs::keyPressed(_sound* snd)
{
     switch(wParam)
    {
        case VK_SPACE:
             snd->playSound("sounds/pew.mp3");
             break;
        /*case VK_DOWN:
             snd->playSound("sounds/p.mp3");
             break;
    */
    }
}


void _inputs::keyUp(_player* ply)
{
     switch(wParam)
    {
       case VK_LEFT:
          ply->movingLeft = false;
            break;
       case VK_RIGHT:
          ply->movingRight = false;
            break;
       case VK_DOWN:
          ply->movingDown = false;
            break;
       case VK_UP:
          ply->movingUp = false;
            break;
    }

}


void _inputs::keyUp()   // Fill this depending on your game actions
{
    switch(wParam)
    {
        default: break;
    }
}

void _inputs::mouseEventDown(_Model* Mdl, double x, double y)
{
    prev_Mouse_X =x;
    prev_Mouse_Y =y;

    switch(wParam)
    {

        case MK_LBUTTON:
            Mouse_Rotate=true;
           //Mouse_Translate=false;
            break;
        case MK_RBUTTON:
            Mouse_Translate=true;
          //  Mouse_Rotate =false;
            break;
        case MK_MBUTTON:break;

        default: break;
    }
}

void _inputs::mouseEventUp()
{
    Mouse_Rotate=false;
    Mouse_Translate=false;
}

void _inputs::mouseWheel(_Model* Mdl, double Delta)
{
    Mdl->posZ +=Delta/100;
}

void _inputs::mouseMove(_Model* Mdl, double x, double y)
{
    if(Mouse_Rotate)
    {
        Mdl->rotateY +=(x-prev_Mouse_X)/3;
        Mdl->rotateX +=(y-prev_Mouse_Y)/3;
    }

    if(Mouse_Translate)
    {
       Mdl->posX +=(x-prev_Mouse_X)/100;
       Mdl->posY -=(y-prev_Mouse_Y)/100;
    }
    prev_Mouse_X =x;
    prev_Mouse_Y =y;
}
