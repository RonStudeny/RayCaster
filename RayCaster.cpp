#define OLC_PGE_APPLICATION

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define SCREEN_WIDTH 24
#define SCREEN_HEIGHT 24

#include "olcPixelGameEngine.h"

class RayCaster : public olc::PixelGameEngine {
	int map[MAP_HEIGHT][MAP_WIDTH] = {
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
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		//for (int x = 0; x < (int) (ScreenWidth()); x++)
		//	for (int y = 0; y < (int)(ScreenHeight()); y++) {
		//		switch (map[(int)(y / MAP_HEIGHT)][(int)(x / MAP_WIDTH)]) {
		//		case 0:
		//			Draw(x, y, olc::Pixel(0, 0, 0));
		//			break;
		//		case 1:
		//			Draw(x, y, olc::Pixel(105, 105, 105));
		//			break;
		//		default:
		//			Draw(x, y, olc::Pixel(105, 105, 105));

		//		}
		//	}
		//		//Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
		for (int x = 0; x < (int)(sizeof(map[0]) / sizeof(int)); x++)
			for (int y = 0; y < (int)(sizeof(map) / sizeof(map[0])); y++) {
				switch (map[(int)(y)][(int)(x)]) {
				case 0:
					Draw(x, y, olc::Pixel(0, 0, 0));
					break;
				case 1:
					Draw(x, y, olc::Pixel(105, 105, 105));
					break;
				default:
					Draw(x, y, olc::Pixel(105, 105, 105));
				}
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