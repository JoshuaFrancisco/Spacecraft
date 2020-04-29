# Spacecraft
## Team: Snowstorm Entertainment

Game Development Project made with OpenGL and C++

### Description:

A top-down isometric space shooter where a player must defend his position before a swarm of enemies overwhelm's him

### Running Environment:
CodeBlocks, OpenGL/GLUT, SOIL, irrKlang.a 

#### NOTE: spacecraft.layout file is missing you can find that in the discord

### How to Run it:

#### 1.) First Create a new Glut Project

!['Step 1'](https://cdn.discordapp.com/attachments/185652814645690368/704954209707098183/step1.png)


Set the relative path for your common folder which should include dependency files such as irrKlang.a, SOIL, and GLUT

!['Step 1.1'](https://cdn.discordapp.com/attachments/185652814645690368/704954988102811728/step_1.1.png)

#### 2.) Create a new Class naming it whatever in this instance I am creating a _projectiles which will create a .ccp and .h file in a src and include folder 

!['Step 2'](https://cdn.discordapp.com/attachments/185652814645690368/704956241083891752/step2.png)


#### 3.) Copy and paste projectile.cpp and projectile.h code from the master into your new Glut Project (you can find the .cpp & .h files in master's src & include) 

!['Step 3'](https://cdn.discordapp.com/attachments/185652814645690368/704958088402436146/step2.2.png)

#### 4.) Copy paste main, bin, sounds, images, and all the files in include and src besides projectile.ccp & projectile.h into your new GLUT project 

!['Step 4'](https://cdn.discordapp.com/attachments/185652814645690368/704959353563643904/step4.png)

#### 5.) In your codeblocks manager on the left, right click on the src folder and add all the cpp files you copy pasted over into your new GLUT project and do the same for include by adding the header files

!['Step 5'](https://cdn.discordapp.com/attachments/185652814645690368/704959704899518494/step5.png)

#### 6.) Go to Project -> Properties -> linker settings-> add libSOIL.a found in common/lib and put on the top of all the other files-> next add libirrKlang.a in common/lib and leave as is.

!['Step 6'](https://cdn.discordapp.com/attachments/185652814645690368/704960592401661992/step6.png)

After you've done all this Build and Run and the game should work!

!['Game'](https://cdn.discordapp.com/attachments/185652814645690368/704963250172723271/final.png)
