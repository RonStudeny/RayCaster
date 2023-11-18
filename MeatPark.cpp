#include"olcPixelGameEngine.h"

#define OLC_PGE_APPLICATION

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define SCREEN_WIDTH 200
#define SCREEN_HEIGHT 200


struct vector2i {
	int x, y;
};

struct vector2d {
	double x, y;
};

struct Player {
	vector2d pos{ 10, 10 };
	vector2d dir{ 0, 0 };

};

void setDir(vector2d& dir, double angle) {
	dir.x = cos(angle);
	dir.y = sin(angle);
}

void rotateBy(vector2d& dir, double angle) {
	double newDirX = dir.x * cos(angle) - dir.y * sin(angle);
	double newDirY = dir.x * sin(angle) + dir.y * cos(angle);

	dir.x = newDirX;
	dir.y = newDirY;
}


class RayCaster : public olc::PixelGameEngine {

	Player player;
	int worldMap[MAP_HEIGHT][MAP_WIDTH] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

public:
	RayCaster() {
		sAppName = "RayCaster";
	}

public:
	bool OnUserCreate() override {
		setDir(player.dir, 0);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {		

		int mapWidth = (int)(sizeof(worldMap[0]) / sizeof(int));
		int mapHeight = (int)(sizeof(worldMap) / sizeof(worldMap[0]));
		Clear(olc::DARK_BLUE);

		//rasterize minimap

		float cellWidth = (float)SCREEN_WIDTH / mapWidth;
		float cellHeight = (float)SCREEN_HEIGHT / mapHeight;

		for (int x = 0; x < mapWidth; x++)
			for (int y = 0; y < mapHeight; y++) {

				int cellX = x * cellWidth;
				int cellY = y * cellHeight;
				int cellSizeX = (x + 1) * cellWidth - cellX;
				int cellSizeY = (y + 1) * cellHeight - cellY;

				switch (worldMap[(int)(y)][(int)(x)]) {
				case 0:
					//Draw(x, y, olc::Pixel(0, 0, 0));
					FillRect(cellX, cellY, cellSizeX, cellSizeY, olc::Pixel(0, 0, 0));
					break;
				case 1:
					FillRect(cellX, cellY, cellSizeX, cellSizeY, olc::Pixel(105, 105, 105));
					break;
				default:
					FillRect(cellX, cellY, cellSizeX, cellSizeY, olc::Pixel(255, 0, 0));
					
				}
			}
		/* nornalize with delta time, dumb ass*/
		if (GetKey(olc::Key::A).bHeld) player.pos.x -= 0.1;
		if (GetKey(olc::Key::D).bHeld) player.pos.x += 0.1;
		if (GetKey(olc::Key::W).bHeld) player.pos.y -= 0.1;
		if (GetKey(olc::Key::S).bHeld) player.pos.y += 0.1;

		if (GetKey(olc::Key::Q).bHeld) {
			rotateBy(player.dir, -0.01);
		}
		if (GetKey(olc::Key::E).bHeld) {
			rotateBy(player.dir, 0.01);
		}


		//Draw(player.pos.x, player.pos.y, olc::Pixel(0, 0, 255));

		FillRect(player.pos.x - 1, player.pos.y - 1, 3, 3, olc::Pixel(0, 0, 255));
		//rotateBy(player.dir, 1); 
		double endY = player.pos.y + 10 * player.dir.y;
		double endX = player.pos.x + 10 * player.dir.x;

		DrawLine(player.pos.x, player.pos.y, endX, endY, olc::Pixel(olc::DARK_CYAN));

		return true;
	}
};


int main() {
	RayCaster rc;
	if (rc.Construct(SCREEN_WIDTH, SCREEN_HEIGHT, 4, 4)) {
		rc.Start();
	}
	return 0;
}

