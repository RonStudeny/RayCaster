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

class RayCaster : public olc::PixelGameEngine {

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

	vector2d playerPos {10, 10};

public:
	RayCaster() {
		sAppName = "RayCaster";
	}

public:
	bool OnUserCreate() override {

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

		if (GetKey(olc::Key::A).bHeld) playerPos.x -= 1;
		if (GetKey(olc::Key::D).bHeld) playerPos.x += 1;

		if (GetKey(olc::Key::S).bHeld) playerPos.y -= 1;
		if (GetKey(olc::Key::W).bHeld) playerPos.y += 1;

		

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

