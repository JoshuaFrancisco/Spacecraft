#ifndef _ENMS_H
#define _ENMS_H

#include <GL/gl.h>
#include <_textureLoader.h>
#include <_timer.h>
#include <math.h>

#define PI 3.14159
#define gravity 9.81

class _enms
{
    public:
        _enms();
        virtual ~_enms();

        void drawEnemy(); //drawing enemies
        void placeEnemy(float,float,float); //placing enemies with a three dimensional atmosphere
        void initEnemy(GLuint);
        void actions(); //movements and actions you want to add

        bool isEnemyLive; //Status of the enemy
        GLuint EnemyTex; //Texture handler

        float xPos, yPos, zPos; //Placements
        float xSize, ySize; //Scaling Factor

        float rotateX, rotateY, rotateZ; //rotations

        int frames; //number of frames
        float xMove, yMove; //moving speed on x axis
        int action;  //to make an action for an enemy
        _timer *TE = new _timer();

        float theta,v,t; //angle , velocity, time

    protected:

    private:
        float xMin, yMin, xMax, yMax;
};

#endif // _ENMS_H
