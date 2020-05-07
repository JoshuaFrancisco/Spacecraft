#ifndef _PLAYER_H
#define _PLAYER_H

#include <GL/gl.h>
#include <_textureLoader.h>
#include <_timer.h>
#include <projectiles.h>
#include <vector>

typedef struct
{
    float x;
    float y;
    float z;
}vec3;

class _player
{
    public:
        _player();
        virtual ~_player();

        float scale[3]={1.0,1.0,1.0};
        vec3 verticies[4];

        float xPos;   //x position of the Player
        float yPos;   //y position of the Player
        float zPos;   //z position of the Player

        float xSize, ySize;
        float xRotation, yRotation, zRotation;
        float xMove, yMove, speed;

        string direction = "up";
        bool movingLeft, movingRight, movingUp, movingDown;
        int maxBullets = 3, bulletCount = 0;
        vector<_projectile*> bullets;

        void drawPlayer();
        void placePlayer();
        void initPlayer(char *);
        void shoot();

        void actions();   // may have to pass different frame numbers
        int action, health;          // give values for run jump etc.
        float frames;
        float xMax,xMin,yMax,yMin;

    protected:

    private:
};

#endif // _PLAYER_H
