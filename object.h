enum IDS{PLAYER,BULLET,ENEMY};

struct SpaceShip
{
	int ID;
	int score;
	int lives;
	int x;
	int y;
	int xbound;
	int ybound;
	int speed;

};

struct Bullets
{
	int ID;
	int speed;
	int x;
	int y;
	bool alive;
};

struct Comets
{
	int ID;
	int speed;
	int x;
	int y;
	int alive;
	int xbound;
	int ybound;
};

struct Background
{
	float x;
	float y;
	float x_vel;
	float y_vel;
	float dirx;
	float diry;
	
	int background_height;
	int background_width;

	ALLEGRO_BITMAP *image;



};