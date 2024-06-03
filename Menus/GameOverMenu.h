#pragma once
#include "../Engine/Menu.h"

class GameOverMenu : public Menu {
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
	GameOverMenu(GameManager&);
	~GameOverMenu(void) {}
	void handleInput(RenderWindow*, Event&);
	void update(void);
	void render(RenderWindow*);
};