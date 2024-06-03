#pragma once
#include "../Engine/Level.h"


class TestLevel : public Level {
public:
	TestLevel(GameManager* _gameManager) : Level(_gameManager, 3, 3, 7, Level::LEVELS::DARKFOREST) {

		//	X X X
		//	X X X
		//	X O X

		addMusic("Assets/Sounds/Music/DarkForest.ogg");

		addRoom(0, { PlatformAdder({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 13, 1 }),
			PlatformAdder({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1, 10 }),
			PlatformAdder({ 220.0f, 590.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 510.0f, 470.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 300.0f, 280.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 70.0f, 225.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 710.0f, 250.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			KeyAdder({ 80.0f, 160.0f }, { 0.75f, 0.75f }),
		});

		addRoom(1, { PlatformAdder({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 13, 1 }),
			PlatformAdder({ 80.0f, 180.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 280.0f, 220.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 480.0f, 260.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 480.0f, 530.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 730.0f, 350.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 260.0f, 550.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			KeyAdder({ 300.0f, 160.0f }, { 0.75f, 0.75f }),
		});

		addRoom(2, { PlatformAdder({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 13, 1 }),
			PlatformAdder({ WINDOW_X - 64.0f, 0.0f }, { 1.0f, 1.0f }, { 1, 13 }),
			PlatformAdder({ 120.0f, 270.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 330.0f, 250.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 680.0f, 390.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 600.0f, 140.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 490.0f, 550.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 120.0f, 540.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			KeyAdder({ 620.0f, 80.0f }, { 0.75f, 0.75f }),
		});

		addRoom(3, { PlatformAdder({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1, 10 }),
			PlatformAdder({ 390.0f, 590.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 180.0f, 490.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 64.0f, 315.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 375.0f, 275.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 220.0f, 100.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 620.0f, 185.0f }, { 1.0f, 0.1f }, { 1, 1 }),
		});

		addRoom(4, { PlatformAdder({ 690.0f, 560.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 510.0f, 460.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 600.0f, 280.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 290.0f, 360.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 290.0f, 360.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 170.0f, 180.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 460.0f, 40.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 70.0f, 540.0f }, { 1.0f, 0.1f }, { 1, 1 }),
		});

		addRoom(5, { PlatformAdder({ WINDOW_X - 64.0f, 0.0f }, { 1.0f, 1.0f }, { 1, 10 }),
			PlatformAdder({ 600.0f, 190.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 480.0f, 340.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 260.0f, 470.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 10.0f, 570.0f }, { 1.0f, 0.1f }, { 1, 1 }),
		});

		addRoom(6, { PlatformAdder({ 0.0f, WINDOW_Y - 64.0f }, { 1.0f, 1.0f }, { 13, 1 }),
			PlatformAdder({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1, 10 }),
			PlatformAdder({ 440.0f, 80.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 200.0f, 440.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 75.0f, 300.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 330.0f, 250.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 580.0f, 200.0f }, { 1.0f, 0.1f }, { 1, 1 }),
		});

		addRoom(7, { PlatformAdder({ 0.0f, WINDOW_Y - 64.0f }, { 1.0f, 1.0f }, { 13, 1 }),
			PlatformAdder({ 190.0f, 90.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 350.0f, 220.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 560.0f, 340.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 220.0f, 380.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 730.0f, 240.0f }, { 1.0f, 0.1f }, { 1, 1 }),
		});

		addRoom(8, { PlatformAdder({ 0.0f, WINDOW_Y - 64.0f }, { 1.0f, 1.0f }, { 13, 1 }),
			PlatformAdder({ WINDOW_X - 64.0f, 0.0f }, { 1.0f, 1.0f }, { 1, 10 }),
			PlatformAdder({ 120.0f, 360.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 370.0f, 500.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 420.0f, 320.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 650.0f, 180.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 280.0f, 140.0f }, { 1.0f, 0.1f }, { 1, 1 }),
			PlatformAdder({ 10.0f, 10.0f }, { 1.0f, 0.1f }, { 1, 1 }),
		});
	}
};