#ifndef _CHECKCOLLISION_H
#define _CHECKCOLLISION_H


class _checkCollision
{
    public:
        _checkCollision();
        virtual ~_checkCollision();

        //used for 2d
        bool isLinearCollision(float,float);
        bool isRadialCollision(float,float,float,float,float,float);


        //below mostly for 3d
        bool isCircleRayCollision(float,float,float,float,float);
        bool isCubic(float,float,float,float);
        bool isSphereCollision(float,float,float,float);

        bool isCollisionFloot(float,float,float);

    protected:

    private:
};

#endif // _CHECKCOLLISION_H
