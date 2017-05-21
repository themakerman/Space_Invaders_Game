#Space_Invaders_Game 
How to setup your Computer for Allegro Environment :


1 Extract all the compiled version of ALLEGRO for Visual Studio allegro-5.0.10-msvc-10.0 to one place.Inside you will find out three folders : bin,include and lib.

2 Copy all the .dll files in bin folder to your computers windows directory inside system32(if x86 bit) else sysWOW64(if 64 bit system).

3 Next copy the remaning two folders i.e include and lib folder to the directory where Visual Studio 2010 is installed inside VC folder.

4 Last step is to configure visual studio. We have to tell VS that we are using Allegro library to avoid the linker error.Right click on your project_name in solutions explorer  --> properties --> Linker --> input --> additional_dependencies --> type --> allegro-5.0.1-monolith-md-debug.lib


Description: Space invaders is a 2d game developed using C build with Microsoft Visual Studio IDE. As the project involves graphics programming, a game library called Allegro was used to do all the graphics processing. Two counter variables to track lives and score are
programmed in the code. score++ is called when player hits the comet and lives-- is called when comet hits the spacecraft thereby decreasing the number of lives player has. By default lives is initialized to 3 giving player 3 lives at begining of the game. The game background uses the concept of “parallax” which gives the player illusion of moving ahead which is not the case as player/spacecraft always remains still. It is the background which moves from right to left, making the player believe that spacecraft is moving forward. Game play stops when player lives becomes 0 or when ESC key is pressed which quits the game window. Technology: Visual Studio 2010, C Programming, Allegro library Work link: https://www.youtube.com/watch?v=2PVWcBUek6U 



Below is the link of youtube video : 



![4](https://cloud.githubusercontent.com/assets/14818804/21540158/6a3a8c90-cdd3-11e6-9277-42568c518954.png)




https://www.youtube.com/watch?v=2PVWcBUek6U

