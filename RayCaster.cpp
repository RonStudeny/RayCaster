#include <iostream>

#define OLC_PGE_APPLICATION
#include"olcPixelGameEngine.h"


#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define SCREEN_WIDTH 200
#define SCREEN_HEIGHT 200

#define MINIMAP_WIDTH 32
#define MINIMAP_HEIGHT 32


struct vector2i {
	int x, y;
};

struct vector2d {
	double x, y;
};

struct Camera {
	vector2d plane{ 0, 0.66 };
};

struct Player {
	vector2d pos{ 2, 2 };
	vector2d dir{ 0, 0 };

	double speed{ 0.007 };
	double turnRate{ 0.007 };
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
	Camera cam;
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
		Clear(olc::DARK_GREY);

		// PLAYER MOVEMENT
		/* nornalize with delta time, dumb ass*/
		if (GetKey(olc::Key::A).bHeld) {
			player.pos.x += player.dir.y * player.speed;
			player.pos.y -= player.dir.x * player.speed;
		}
		if (GetKey(olc::Key::D).bHeld) {
			player.pos.x -= player.dir.y * player.speed;
			player.pos.y += player.dir.x * player.speed;
		}

		if (GetKey(olc::Key::W).bHeld) {
			player.pos.x += player.dir.x * player.speed;
			player.pos.y += player.dir.y * player.speed;
		}
		if (GetKey(olc::Key::S).bHeld) {
			player.pos.x -= player.dir.x * player.speed;
			player.pos.y -= player.dir.y * player.speed;
		}

		if (GetKey(olc::Key::Q).bHeld) {
			rotateBy(player.dir, -player.turnRate);
			rotateBy(cam.plane, -player.turnRate);
		}
		if (GetKey(olc::Key::E).bHeld) {
			rotateBy(player.dir, player.turnRate);
			rotateBy(cam.plane, player.turnRate);
		}


		//RAY CASTING

		for (size_t x = 0; x < SCREEN_WIDTH; x++)
		{
			double cameraX = 2 * x / double(SCREEN_WIDTH) - 1;
			vector2d rayDir;
			rayDir.x = player.dir.x + cam.plane.x * cameraX;
			rayDir.y = player.dir.y + cam.plane.y * cameraX;
			
			vector2i rayPosInMap {(int)player.pos.x, (int)player.pos.y};
			vector2d sideDist;
			vector2d deltaDist;
				
			deltaDist.x = (rayDir.x == 0) ? 1e30 : std::abs(1 / rayDir.x);
			deltaDist.y = (rayDir.y == 0) ? 1e30 : std::abs(1 / rayDir.y);

			double perpWallDist;
			vector2i step;

			int hit = 0;
			int side;

			if (rayDir.x < 0) {
				step.x = -1;
				sideDist.x = (player.pos.x - rayPosInMap.x) * deltaDist.x;
			}
			else {
				step.x = 1;
				sideDist.x = (rayPosInMap.x + 1.0 - player.pos.x) * deltaDist.x;
			}
			if (rayDir.y < 0) {
				step.y = -1;
				sideDist.y = (player.pos.y - rayPosInMap.y) * deltaDist.y;
			}
			else {
				step.y = 1;
				sideDist.y = (rayPosInMap.y + 1.0 - player.pos.y) * deltaDist.y;
			}

			// DDA

			while (hit == 0) {
				if (sideDist.x < sideDist.y) {
					sideDist.x += deltaDist.x;
					rayPosInMap.x += step.x;
					side = 0;
				}
				else {
					sideDist.y += deltaDist.y;
					rayPosInMap.y += step.y;
					side = 1;
				}
				if (worldMap[rayPosInMap.x][rayPosInMap.y] > 0) hit = 1;
			}

			if (side == 0) {
				perpWallDist = (sideDist.x - deltaDist.x);
			}
			else perpWallDist = (sideDist.y - deltaDist.y);

			int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

			int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
			if (drawStart < 0) drawStart = 0;
			int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
			if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

			olc::Pixel color;

			switch (worldMap[rayPosInMap.x][rayPosInMap.y]) {
			case 1: color = olc::RED; break;
			case 2: color = olc::GREEN; break;
			case 3: color = olc::BLUE; break;
			case 4: color = olc::DARK_MAGENTA; break;
			case 5: color = olc::YELLOW; break;
			}

			if (side == 1) color = color / 2;

			DrawLine(x, drawStart, x, drawEnd, color);
		}





		//rasterize minimap

		float cellWidth = (float)MINIMAP_WIDTH / mapWidth;
		float cellHeight = (float)MINIMAP_HEIGHT / mapHeight;

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
					FillRect(cellX, cellY, cellSizeX, cellSizeY, olc::Pixel(olc::DARK_GREY));
					break;
				case 2:
					FillRect(cellX, cellY, cellSizeX, cellSizeY, olc::Pixel(olc::YELLOW));
					break;
				case 3:
					FillRect(cellX, cellY, cellSizeX, cellSizeY, olc::Pixel(olc::BLUE));
					break;	
				default:
					FillRect(cellX, cellY, cellSizeX, cellSizeY, olc::Pixel(olc::DARK_RED));
					
				}
			}


		double endY = player.pos.y + 5 * player.dir.y;
		double endX = player.pos.x + 5 * player.dir.x;
		 
		DrawLine(player.pos.x, player.pos.y, endX, endY, olc::Pixel(olc::DARK_CYAN));
		FillRect(player.pos.x, player.pos.y, 1, 1, olc::Pixel(olc::RED));

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

