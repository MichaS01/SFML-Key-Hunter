#pragma once
#include "../Engine/Menu.h"

class MainMenu : public Menu {
private:
	Texture m_BackgroundTexture, m_LogoTexture, m_IconTexture;
	Sprite m_BackgroundSprite, m_LogoSprite, m_IconSprite;
	Font m_TextFont;
	Text m_PlayText, m_ExitText;
	RectangleShape m_PlayButton, m_ExitButton;
	SoundBuffer m_Buffer;
	Sound m_Sound;
	class GameManager& m_GameManager;
	int m_Timer;

public:
	MainMenu(GameManager&);
	~MainMenu() {}
	void handleInput(RenderWindow*, Event&);
	void update(void);
	void render(RenderWindow*);
};