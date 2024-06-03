#include "GameManager.h"

GameManager::GameManager() {
	this->m_Window = new RenderWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), GAME_TITLE);
	this->m_WindowHandler = this->m_Window->getSystemHandle();

    if (!DEBUGGING) {
        this->m_GameState = GAMESTATE::MAINMENU;
        this->m_Player = nullptr;
        this->m_CurrentLevel = nullptr;
        this->m_Menu = new MainMenu(*this);
    } else this->restartGame();

	this->loadSettings();
    this->render();
}

void GameManager::loadSettings() {
    srand(time(NULL));

    this->m_Window->setFramerateLimit(FRAMERATE_LIMIT);
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, ENABLE_CONSOLE);

    if (DISABLE_TASKBAR) {
        HWND hwnd = this->m_Window->getSystemHandle();
        LONG style = GetWindowLong(hwnd, GWL_STYLE);
        style &= ~WS_SYSMENU;
        style &= ~WS_CAPTION;
        style &= ~WS_THICKFRAME;
        style &= ~WS_MINIMIZEBOX;
        style &= ~WS_MAXIMIZEBOX;
        SetWindowLong(hwnd, GWL_STYLE, style);
        SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }
}

void GameManager::eventManager() {
    if (this->getGameStatus() != GAMESTATE::PLAYING)
        return;

    while(this->m_Window->pollEvent(this->m_Event))
        switch (this->m_Event.type) {
        case Event::Closed:
            this->m_Window->close();
            break;

        case Event::KeyPressed:
            if (this->m_Event.key.code == Keyboard::Escape &&
                this->getGameStatus() == GAMESTATE::PLAYING)
                this->setMenu(new PauseMenu(*this), GAMESTATE::PAUSED);
            break;
        }
}

void GameManager::setMenu(Menu* _menu, int _state) {
    this->m_GameState = _state;
    delete this->m_Menu;
    this->m_Menu = _menu;

    if (this->m_GameState == GAMESTATE::PLAYING &&
        (this->m_Player == nullptr || this->m_CurrentLevel == nullptr)) {
        this->m_Player = new Player(this);
        this->m_CurrentLevel = new TestLevel(this);
    }
}

void GameManager::restartGame(void) {
    delete this->m_Menu;
    delete this->m_Player;
    delete this->m_CurrentLevel;

    this->m_Menu = nullptr;
    this->m_GameState = GAMESTATE::PLAYING;
    this->m_Player = new Player(this);
    this->m_CurrentLevel = new TestLevel(this);
}

void GameManager::changeRoom(int _direction) {
    if (this->m_CurrentLevel != nullptr)
        if (this->m_CurrentLevel->changeRoom(_direction))
            switch (_direction) {
            case Level::DIRECTION::LEFT:
                this->m_Player->setPosition(WINDOW_X - this->m_Player->getCollider().width, this->m_Player->getPosition().y);
                break;

            case Level::DIRECTION::RIGHT:
                this->m_Player->setPosition(0.0f, this->m_Player->getPosition().y);
                break;

            case Level::DIRECTION::UP:
                this->m_Player->setPosition(this->m_Player->getPosition().x, WINDOW_Y - (this->m_Player->getCollider().height / 2));
                break;

            case Level::DIRECTION::DOWN:
                this->m_Player->setPosition(this->m_Player->getPosition().x, 0.0f);
                break;
            }
}

void GameManager::render() {
    while (this->m_Window->isOpen()) {

        this->eventManager();

        if (GetForegroundWindow() != this->m_WindowHandler &&
            this->getGameStatus() == GAMESTATE::PLAYING)
            this->setMenu(new PauseMenu(*this), GAMESTATE::PAUSED);

        this->m_Window->clear();
        //
        if (this->m_CurrentLevel != nullptr) {
            this->m_CurrentLevel->render(this->m_Window);
            this->m_CurrentLevel->manageMusic();
        }

        if (this->m_Player != nullptr) {
            this->m_Player->update(this->m_CurrentLevel->getCurrentRoom()->getPlatforms(), this->m_CurrentLevel->getCurrentRoom()->getKeys());
            this->m_Player->render(this->m_Window);
        }        

        if (this->m_Menu != nullptr) {
            this->m_Menu->render(this->m_Window);
            this->m_Menu->handleInput(this->m_Window, this->m_Event);
        }
        //
        this->m_Window->display();
    }
}