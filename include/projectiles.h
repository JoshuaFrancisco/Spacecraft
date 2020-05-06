#ifndef _PROJECTILE_H
#define _PROJECTILE_H
#include <iostream>
#include <GL/gl.h>
#include <_textureLoader.h>

typedef struct
{
    float x;
    float y;
    float z;
}avec3;

class _projectile
{
    public:
        _projectile();
        virtual ~_projectile();
        float speed = 0.01;

        float scale[3]={1.0,1.0,1.0};
        avec3 verticies[4];
        float xSize, ySize, xPos, yPos, zPos, xMove, yMove;
        float xMax,xMin,yMax,yMin;
        float distTraveled, maxDistance;

        void init(char *);
        void draw();
        void move();
        bool expired();
};

#endif // _PROJECTILE_H
