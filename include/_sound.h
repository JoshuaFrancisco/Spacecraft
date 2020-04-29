#ifndef _SOUND_H
#define _SOUND_H

#include<snds/irrKlang.h>
#include<stdlib.h>
#include<iostream>

using namespace std;
using namespace irrklang;
class _sound
{
    public:
        _sound();
        virtual ~_sound();

        ISoundEngine *engine = createIrrKlangDevice();

        void playMusic(char *);
        void playSound(char *);
        void pauseSound(char *);
        int initSounds();

    protected:

    private:
};

#endif // _SOUND_H
