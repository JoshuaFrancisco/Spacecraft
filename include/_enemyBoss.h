#ifndef _ENEMYBOSS_H
#define _ENEMYBOSS_H
#include <_enms.h>
#include <projectiles.h>
#include <vector>
#include <iostream>

using namespace std;

class _enemyBoss: public _enms
{
    public:
        _enemyBoss();
        virtual ~_enemyBoss();

        //Variables
        int health, cycles;
        bool redeployed;
        vector<_projectile*> bullets;

        //Functions
        void actions();
        void shoot();
        bool isDead();

    protected:
    private:
};

#endif // _ENEMYBOSS_H
