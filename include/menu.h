#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string.h>
#include <gl/gl.h>
#include <windows.h>
using namespace std;

class menu
{
    public:
        menu();
        virtual ~menu();
        void drawMenu(float,float);
        void menuInit(char *);

        float Xmax,Ymax,Xmin,Ymin;

    protected:

    private:
};

#endif // MENU_H
