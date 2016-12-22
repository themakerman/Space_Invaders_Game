/*
Author : Gaurav Harchwani
Project Started : January 28th 2014
Project Completed : March 4th 2014
Project Name : SpaceInvaders : Save the earth from Metorite shower
*/


#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_native_dialog.h>
#include"object.h"
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>
#include<allegro5\allegro_audio.h>
#include<allegro5\allegro_acodec.h>
#include<allegro5\allegro_image.h>



//Global Declarations

enum KEYS{UP,DOWN,LEFT,RIGHT,SPACE};
bool workdone = false;
const int width = 1366;
const int height = 768;
bool keys[5] = {false,false,false,false,false};
bool redraw = true;
float FPS = 60.0;
const int number_of_bullets = 15;
const int number_of_comets = 10;
bool is_game_over	= false;



//Prototypes

void initShip(SpaceShip &ship);
void displayShip(SpaceShip &ship);
void moveShip(SpaceShip &ship);


void initBullets(Bullets bullets[],int number_of_bullets);
void displayBullets(Bullets bullets[],int number_of_bullets);
void fireBullets(Bullets bullets[],int number_of_bullets,SpaceShip &ship);
void updateBullets(Bullets bullets[],int number_of_bullets);


void initComets(Comets comets[],int number_of_comets);
void displayComets(Comets comets[],int number_of_comets);
void startComets(Comets comets[],int number_of_comets);
void updateComets(Comets comets[],int number_of_comets);
void collideBullet(Bullets bullets[],int number_of_bullets,Comets comets[],int number_of_comets,SpaceShip &ship);
void collideComet(Comets comets[],int number_of_comets,SpaceShip &ship);


void initBackground(float x,float y,float dirx,float diry,float velx,float vely,int background_width,int background_height,ALLEGRO_BITMAP *image,Background &bg);
void updateBackground(Background &bg);
void displayBackground(Background &bg,ALLEGRO_BITMAP *Background_image1);


void main()
{
	//Initializing Display
	ALLEGRO_DISPLAY *display = NULL;

	//Font
	ALLEGRO_FONT *catholic_girls = NULL;
	ALLEGRO_FONT *font = NULL;

	//Audio sample
	ALLEGRO_SAMPLE *sample = NULL;

	//Background Initialization
	ALLEGRO_BITMAP *background_image1 = NULL;
	ALLEGRO_BITMAP *background_image2 = NULL;
	ALLEGRO_BITMAP *background_image3 = NULL;

	if(al_init() == false )
	{
		al_show_native_message_box(NULL,"Allegro.exe","Error","Allegro Initialization Failed",NULL,NULL);
	}

	display = al_create_display(width,height);

	if(display == false)
	{
		al_show_native_message_box(NULL,"Allegro.exe","Error","Allegro Display Failed",NULL,NULL);
	}

	//Adding Primitives
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();

	//Insatalling Keyboard
	al_install_keyboard();

	  catholic_girls = al_load_font("bloodlust.ttf",30,NULL);
	  font = al_load_font("BlackWidow.ttf",30,NULL);

	//Creating Event Queue 
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	
	//Load image
	background_image1 = al_load_bitmap("starBG.png");
	background_image2 = al_load_bitmap("starFG.png");
	background_image3 = al_load_bitmap("starMG.png");

	//Load sample
	sample = al_load_sample("binarysolo.ogg");
	al_reserve_samples(1);

	
	//Initializing Allegro Event timer
	ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);

	//Registering Events
	al_register_event_source(event_queue,al_get_keyboard_event_source());
	al_register_event_source(event_queue,al_get_display_event_source(display));
	al_register_event_source(event_queue,al_get_timer_event_source(timer));

	//Structure Variable Created
	SpaceShip ship;
	Bullets bullets[15];
	Comets comets[number_of_comets];
	Background bg1;
	Background bg2;
	Background bg3;
	

	//Initializing Ship
	initShip(ship);
	al_hide_mouse_cursor(display);
	

	//Initializing and displaying Bullets
	initBullets(bullets,number_of_bullets);

	//Initialize Comets
	initComets(comets,number_of_comets);

	//Initialize background
	initBackground(0,0,-1,0,1,0,800,600,background_image1,bg1);
	initBackground(0,0,-1,0,1,0,1000,600,background_image2,bg2);
	initBackground(0,0,-1,0,1,0,1600,600,background_image3,bg3);
	

	//Starting Timer
	al_start_timer(timer);

	al_play_sample(sample,2,0,1,ALLEGRO_PLAYMODE_LOOP,NULL);

	while(workdone == false)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue,&ev);

	     if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;

			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				fireBullets(bullets,number_of_bullets,ship);
				break;

			case ALLEGRO_KEY_ESCAPE:
				workdone = true;
				break;

				}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
			
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;

			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			
			case ALLEGRO_KEY_ESCAPE:
				workdone = true;
				break;
		
			}
	
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			workdone = true;
		}
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;	
			moveShip(ship);
			updateBackground(bg1);
			updateBackground(bg2);
			updateBackground(bg3);
			
			if(is_game_over == false && ship.lives != 0)
			{
				updateBullets(bullets,number_of_bullets);
				startComets(comets,number_of_comets);
				updateComets(comets,number_of_comets);
				collideBullet(bullets,number_of_bullets,comets,number_of_comets,ship);
				collideComet(comets,number_of_comets,ship);
			}

		
		}
				
		if(redraw && al_is_event_queue_empty(event_queue) )
		{
				redraw = false;		
				if(is_game_over == false && ship.lives != 0)
				{
					displayShip(ship);
					displayBullets(bullets,number_of_bullets);
					displayComets(comets,number_of_comets);
					displayBackground(bg1,background_image1);
					displayBackground(bg2,background_image1);
					displayBackground(bg3,background_image1);
					
					al_draw_textf(catholic_girls,al_map_rgb(0,255,255),1300,5,ALLEGRO_ALIGN_RIGHT,"Lives %i ",ship.lives);
					al_draw_textf(catholic_girls,al_map_rgb(0,255,255),30,5,ALLEGRO_ALIGN_LEFT,"Score %i ",ship.score);
					al_draw_textf(font,al_map_rgb(0,255,255),1330,5,ALLEGRO_ALIGN_RIGHT,"%i",ship.lives);
					al_draw_textf(font,al_map_rgb(0,255,255),300,5,ALLEGRO_ALIGN_LEFT,"%i",ship.score);
				
				
				}
				else
				{
					al_draw_textf(catholic_girls,al_map_rgb(0,255,255),width/2,height/2,ALLEGRO_ALIGN_CENTER,"Game Over. Your Score is %i ",ship.score);
					al_draw_textf(font,al_map_rgb(0,255,255),1050,height/2,ALLEGRO_ALIGN_LEFT,"%i",ship.score);
					
				
				}
				al_flip_display();
				al_clear_to_color(al_map_rgb(0,0,0));	
				


		}
		


			
			 
		}

		


	}
	
	


void initShip(SpaceShip &ship)
{
	ship.ID = PLAYER ;
	ship.lives = 3;
	ship.score = 0;
	ship.speed = 5;
	ship.x = 20;
	ship.y = height/2;
	ship.xbound = 6;
	ship.ybound = 7;

}

void displayShip(SpaceShip &ship)
{

	al_draw_filled_rectangle(ship.x, ship.y - 9, ship.x + 10, ship.y - 7, al_map_rgb(255, 0, 0));
	al_draw_filled_rectangle(ship.x, ship.y + 9, ship.x + 10, ship.y + 7, al_map_rgb(255, 0, 0));

	al_draw_filled_triangle(ship.x - 12, ship.y - 17, ship.x +12, ship.y, ship.x - 12, ship.y + 17, al_map_rgb(0, 255, 0));
	al_draw_filled_rectangle(ship.x - 12, ship.y - 2, ship.x +15, ship.y + 2, al_map_rgb(0, 0, 255));
	
}

void moveShip(SpaceShip &ship)
{
	if(keys[UP] == true)
	{
		ship.y -= ship.speed;
			if(ship.y < 0)
				ship.y = 0;
	
	}

	if(keys[DOWN] == true)
	{
		ship.y += ship.speed;
			if(ship.y > width )
				ship.y = width;
		
	}
	
	if(keys[LEFT] == true)
	{
	   ship.x -= ship.speed;
			if(ship.x < 0)
				ship.x = 0;
	}
	if(keys[RIGHT] == true)
	{
		ship.x += ship.speed;
			if(ship.x > 600)
				ship.x = 600;

	}

}

void initBullets(Bullets bullets[],int number_of_bullets )
{
	for(int i=0;i<15;i++)
	{
		bullets[i].ID = BULLET;
		bullets[i].alive = false;
		bullets[i].speed = 10;
	}
}

void displayBullets(Bullets bullets[],int number_of_bullets )
{
	for(int i=0;i<15;i++)
	{
		if(bullets[i].alive == true)
			al_draw_filled_circle(bullets[i].x,bullets[i].y,4,al_map_rgb(rand(),rand(),rand()));
	}
}

void fireBullets(Bullets bullets[],int number_of_bullets,SpaceShip &ship)
{
	for(int i=0;i<15;i++)
	{
		if(bullets[i].alive == false)
		{
			bullets[i].x = ship.x + 17;
			bullets[i].y = ship.y;
			bullets[i].alive = true;
			break;
			
		}
	}
}

void updateBullets(Bullets bullets[],int number_of_bullets)
{
	for(int i=0;i<15;i++)
	{
		if(bullets[i].alive == true )
		{
			bullets[i].x += bullets[i].speed;
			if(bullets[i].x > width)
				bullets[i].alive = false;
		}
	}
}


void initComets(Comets comets[],int number_of_comets)
{
	for(int i=0; i<number_of_comets; i++)
	{
		comets[i].alive = false;
		comets[i].ID = ENEMY;
		comets[i].speed = 5;
		comets[i].xbound = 18;
		comets[i].ybound = 18;

	}

}

void displayComets(Comets comets[],int number_of_comets)
{
	for(int i=0; i<number_of_comets; i++)
	{
		if(comets[i].alive == true )
		{
			al_draw_filled_circle(comets[i].x,comets[i].y,20,al_map_rgb(255,0,0));
		}
	}

}
void startComets(Comets comets[],int number_of_comets)
{
	for(int i=0 ; i< number_of_comets ; i++)
	{
		if(comets[i].alive == false)
		{
			if(rand() % 300 == 0)
			{
				comets[i].alive = true;
				comets[i].x = width + 20;
				comets[i].y = (60 + rand()) % (768-30);

			}

		}
	}


}
void updateComets(Comets comets[],int number_of_comets)
{
	for(int i=0;i<number_of_bullets;i++)
	{
		if(comets[i].alive == true )
		{
			comets[i].x -= comets[i].speed;
			
		}
	}
}

void collideBullet(Bullets bullets[],int number_of_bullets,Comets comets[],int number_of_comets,SpaceShip &ship)
{
	for(int i=0 ; i<number_of_bullets ; i++)
	{
		//Collision will happen only with live bullets
		if(bullets[i].alive == true)
		{
			for(int j=0;j<number_of_comets ; j++)
			{
				if(comets[j].alive == true)
				{
					//Collision Detection Logic
					
					if(	bullets[i].x < (comets[j].x - comets[j].xbound) ||
						bullets[i].x > (comets[j].x + comets[j].xbound) ||
						bullets[i].y < (comets[j].y - comets[j].ybound) ||
						bullets[i].y > (comets[j].y + comets[j].ybound)  )
					{
						
						comets[j].alive = true;
					}
					else
					{
						comets[j].alive = false;
						bullets[i].alive = false ;
						ship.score++;

					}
					

				}


			}
			
		}

	}


}


void collideComet(Comets comets[],int number_of_comets,SpaceShip &ship)
{
	for(int i = 0 ; i<number_of_comets ; i++ )
	{
		if(comets[i].alive == true)
		{
			if( comets[i].x - comets[i].xbound < ship.x + ship.xbound &&
				comets[i].x + comets[i].xbound > ship.x - ship.xbound &&
				comets[i].y - comets[i].ybound < ship.y + ship.ybound && 
				comets[i].y + comets[i].ybound > ship.y - ship.ybound)
				{
					ship.lives--;
					comets[i].alive = false;
				}	
			else if(comets[i].x < 0)
				{
					comets[i].alive = false;
				}

		}


	}


}

void initBackground(float x,float y,float dirx,float diry,float velx,float vely,int background_width,int background_height,ALLEGRO_BITMAP *image,Background &bg)
{
	bg.x = x;
	bg.y = y;
	bg.dirx = dirx;
	bg.diry = diry;
	bg.x_vel = velx;
	bg.y_vel = vely;
	bg.background_width = background_width;
	bg.background_height = background_height;
	bg.image = image;



}

void updateBackground(Background &bg)
{
	bg.x += bg.x_vel * bg.dirx;

	if(bg.x + bg.background_width <= 0 )
		bg.x = 0;
	
}


void displayBackground(Background &bg_image,ALLEGRO_BITMAP *background_image)
{
	al_draw_bitmap(bg_image.image,bg_image.x,bg_image.y,0);
	al_draw_bitmap(background_image,bg_image.x,620,0);
	

	if(bg_image.x + bg_image.background_width < width)
	{
		al_draw_bitmap(bg_image.image,bg_image.x + bg_image.background_width ,bg_image.y,0);
		al_draw_bitmap(background_image,bg_image.x + bg_image.background_width,620,0);

	}
}










