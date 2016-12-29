#Space_Invaders_Game 
How to setup your Computer for Allegro Environment :


1 Extract all the compiled version of ALLEGRO for Visual Studio allegro-5.0.10-msvc-10.0 to one place.Inside you will find out three folders : bin,include and lib.

2 Copy all the .dll files in bin folder to your computers windows directory inside system32(if x86 bit) else sysWOW64(if 64 bit system).

3 Next copy the remaning two folders i.e include and lib folder to the directory where Visual Studio 2010 is installed inside VC folder.

4 Last step is to configure visual studio. We have to tell VS that we are using Allegro library to avoid the linker error.Right click on your project_name in solutions explorer  --> properties --> Linker --> input --> additional_dependencies --> type --> allegro-5.0.1-monolith-md-debug.lib


Below is the link of youtube video : 

![4](https://cloud.githubusercontent.com/assets/14818804/21540158/6a3a8c90-cdd3-11e6-9277-42568c518954.png)

https://www.youtube.com/watch?v=2PVWcBUek6U

