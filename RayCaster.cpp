#define OLC_PGE_APPLICATION

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define SCREEN_WIDTH 340
#define SCREEN_HEIGHT 240

#include "olcPixelGameEngine.h"


struct vector2f {
	float x, y;
};
struct vector2d {
	double x, y;
};
struct vector2i {
	int x, y;
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

	vector2f pos;
	vector2f dir;
	vector2f camPlane;

	double time; // time of the current frame
	double prevTime; // time of the previous frame

public:
	RayCaster() {
		sAppName = "RayCaster";
	}

public:
	bool OnUserCreate() override {

		pos = { 22, 12 };
		dir = { -1, 0 };
		camPlane = { 0, 0.66f };

		time = 0; // time of the current frame
		prevTime = 0; // time of the previous frame
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		int mapWidth = (int)(sizeof(worldMap[0]) / sizeof(int));
		int mapHeight = (int)(sizeof(worldMap) / sizeof(worldMap[0]));

		//rasterize minimap

		//float cellWidth = (float)SCREEN_WIDTH / mapWidth;
		//float cellHeight = (float)SCREEN_HEIGHT / mapHeight;

		//for (int x = 0; x < mapWidth; x++)
		//	for (int y = 0; y < mapHeight; y++) {

		//		int cellX = x * cellWidth;
		//		int cellY = y * cellHeight;
		//		int cellSizeX = (x + 1) * cellWidth - cellX;
		//		int cellSizeY = (y + 1) * cellHeight - cellY;

		//		switch (worldMap[(int)(y)][(int)(x)]) {
		//		case 0:
		//			//Draw(x, y, olc::Pixel(0, 0, 0));
		//			FillRect(cellX, cellY, cellSizeX, cellSizeY, olc::Pixel(0, 0, 0));
		//			break;
		//		case 1:
		//			FillRect(cellX, cellY, cellSizeX, cellSizeY, olc::Pixel(105, 105, 105));
		//			break;
		//		default:
		//			FillRect(cellX, cellY, cellSizeX, cellSizeY, olc::Pixel(255, 0, 0));
		//			
		//		}
		//	}


		for (size_t x = 0; x < mapWidth; x++)
		{
			double cameraX = 2 * x / double(mapWidth) - 1;
			vector2d rayDir;
			rayDir.x = dir.x + camPlane.x * cameraX;
			rayDir.y = dir.y + camPlane.y * cameraX;

			vector2i map{ int(pos.x), int(pos.y) }; // current mapbox
			vector2d sideDist; // distance from current pos to next x or y side
			vector2d deltaDist{
				(rayDir.x == 0) ? 1e30 : std::abs(1 / rayDir.x),
				(rayDir.y == 0) ? 1e30 : std::abs(1 / rayDir.y)
			};
			double perpWallDist;

			vector2i step; // what dir to take step in
			int hit = 0; // wall hit?
			int side; // NS or EW wall hit?

			if (rayDir.x < 0) {
				step.x = -1;
				sideDist.x = (pos.x - map.x) * deltaDist.x;
			}
			else {
				step.x = 1;
				sideDist.x = (map.x + 1.0 - pos.x) * deltaDist.x;
			}

			if (rayDir.y < 0) {
				step.y = -1;
				sideDist.y = (pos.y - map.y) * deltaDist.y;
			}
			else {
				step.y = 1;
				sideDist.y = (map.y + 1.0 - pos.y) * deltaDist.y;
			}
			// DDA
			while (hit == 0) {
				if (sideDist.x < sideDist.y) {
					map.x += deltaDist.x;
					side = 0;
				}
				else {
					sideDist.y += deltaDist.y;
					map.y += step.y;
					side = 1;
				}
				// check if wall hit
				if (worldMap[map.x][map.y > 0]) {
					hit = 1;
				}
			}
			// dist from hit to cam plane 
			if (side == 0)  perpWallDist = (sideDist.x - deltaDist.x);
			else			perpWallDist = (sideDist.y - deltaDist.y);

			int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

			int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
			if (drawStart < 0) drawStart = 0;
			int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
			if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;


			olc::Pixel color;

			switch (worldMap[map.x][map.y])
			{
			case 1: color = { 255, 0, 0 }; // red
				  break;
			case 2: color = { 0, 255, 0 }; // green
				  break;
			case 3: color = { 0, 0, 255 }; // blue
				  break;
			case 4: color = { 255, 255, 255 }; // white
				  break;
			default: color = { 0, 255, 255 }; // yellow
				  break;
			}

		//	if (side == 1) color /= 2;

			DrawLine(x, drawEnd, x, drawStart, color);		
		}
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