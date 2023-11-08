#define OLC_PGE_APPLICATION

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define SCREEN_WIDTH 680
#define SCREEN_HEIGHT 480

#include "olcPixelGameEngine.h"

class RayCaster : public olc::PixelGameEngine {
public:
	RayCaster() {
		sAppName = "RayCaster";
	}

public:
	bool OnUserCreate() override {
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
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