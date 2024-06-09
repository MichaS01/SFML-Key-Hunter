#include "GameManager.h" // Do³¹cza plik nag³ówkowy GameManager

// Konstruktor klasy GameManager
GameManager::GameManager() {
    // Tworzy nowe okno renderowania z okreœlonym trybem wideo i tytu³em gry
    this->m_Window = new RenderWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), GAME_TITLE);
    // Pobiera uchwyt systemowy okna
    this->m_WindowHandler = this->m_Window->getSystemHandle();

    // Jeœli tryb debugowania jest wy³¹czony
    if (!DEBUGGING) {
        this->m_GameState = GAMESTATE::MAINMENU; // Ustawia stan gry na MENU G£ÓWNE
        this->m_Player = nullptr; // Inicjalizuje wskaŸnik gracza jako nullptr
        this->m_CurrentLevel = nullptr; // Inicjalizuje wskaŸnik bie¿¹cego poziomu jako nullptr
        this->m_Menu = new MainMenu(*this); // Tworzy nowe menu g³ówne
    }
    else this->restartGame(); // Restartuje grê w trybie debugowania ( pomija menu g³ówne )

    this->loadSettings(); // £aduje ustawienia gry
    this->render(); // Uruchamia renderowanie gry
}

// Funkcja ³aduj¹ca ustawienia gry
void GameManager::loadSettings() {
    srand(time(NULL)); // Inicjalizuje generator liczb losowych

    this->m_Window->setFramerateLimit(FRAMERATE_LIMIT); // Ustawia limit liczby klatek na sekundê
    HWND hwnd = GetConsoleWindow(); // Pobiera uchwyt okna konsoli
    ShowWindow(hwnd, ENABLE_CONSOLE); // Wyœwietla okno konsoli

    // Jeœli taskbar ma byæ wy³¹czony
    if (DISABLE_TASKBAR) {
        HWND hwnd = this->m_Window->getSystemHandle(); // Pobiera uchwyt systemowy okna gry
        LONG style = GetWindowLong(hwnd, GWL_STYLE); // Pobiera styl okna
        style &= ~WS_SYSMENU; // Usuwa menu systemowe
        style &= ~WS_CAPTION; // Usuwa pasek tytu³owy
        style &= ~WS_THICKFRAME; // Usuwa mo¿liwoœæ zmiany rozmiaru okna
        style &= ~WS_MINIMIZEBOX; // Usuwa przycisk minimalizacji
        style &= ~WS_MAXIMIZEBOX; // Usuwa przycisk maksymalizacji
        SetWindowLong(hwnd, GWL_STYLE, style); // Ustawia nowy styl okna
        SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER); // Aktualizuje pozycjê okna
    }
}

// Funkcja zarz¹dzaj¹ca zdarzeniami w grze
void GameManager::eventManager() {
    // Jeœli stan gry nie jest PLAYING, zakoñcz
    if (this->getGameStatus() != GAMESTATE::PLAYING)
        return;

    // Przechwytywanie zdarzeñ w oknie gry
    while (this->m_Window->pollEvent(this->m_Event))
        switch (this->m_Event.type) {
        case Event::Closed: // Jeœli okno zosta³o zamkniête
            this->m_Window->close(); // Zamknij okno
            break;

        case Event::KeyPressed: // Jeœli klawisz zosta³ naciœniêty
            // Jeœli klawisz to Escape i stan gry to PLAYING
            if (this->m_Event.key.code == Keyboard::Escape &&
                this->getGameStatus() == GAMESTATE::PLAYING)
                this->setMenu(new PauseMenu(*this), GAMESTATE::PAUSED); // Ustaw menu pauzy
            break;
        }
}

// Funkcja ustawiaj¹ca menu i stan gry
void GameManager::setMenu(Menu* _menu, int _state) {
    this->m_GameState = _state; // Ustawia stan gry
    delete this->m_Menu; // Usuwa poprzednie menu
    this->m_Menu = _menu; // Ustawia nowe menu

    // Jeœli stan gry to PLAYING i wskaŸniki gracza lub bie¿¹cego poziomu s¹ nullptr
    if (this->m_GameState == GAMESTATE::PLAYING &&
        (this->m_Player == nullptr || this->m_CurrentLevel == nullptr)) {
        this->m_Player = new Player(this); // Tworzy nowego gracza
        this->m_CurrentLevel = new TestLevel(this); // Tworzy nowy poziom testowy
    }
}

// Funkcja restartuj¹ca grê
void GameManager::restartGame(void) {
    delete this->m_Menu; // Usuwa aktualne menu
    delete this->m_Player; // Usuwa obiekt gracza
    delete this->m_CurrentLevel; // Usuwa bie¿¹cy poziom

    this->m_Menu = nullptr; // Ustawia wskaŸnik menu na nullptr
    this->m_GameState = GAMESTATE::PLAYING; // Ustawia stan gry na PLAYING
    this->m_Player = new Player(this); // Tworzy nowego gracza
    this->m_CurrentLevel = new TestLevel(this); // Tworzy nowy poziom testowy
}

// Funkcja zmieniaj¹ca pokój w poziomie
void GameManager::changeRoom(int _direction) {
    // Jeœli bie¿¹cy poziom nie jest nullptr
    if (this->m_CurrentLevel != nullptr)
        // Jeœli zmiana pokoju powiod³a siê
        if (this->m_CurrentLevel->changeRoom(_direction))
            switch (_direction) {
            case Level::DIRECTION::LEFT: // Jeœli zmiana pokoju na lewo
                this->m_Player->setPosition(WINDOW_X - this->m_Player->getCollider().width, this->m_Player->getPosition().y); // Ustaw pozycjê gracza na prawy brzeg ekranu
                break;

            case Level::DIRECTION::RIGHT: // Jeœli zmiana pokoju na prawo
                this->m_Player->setPosition(0.0f, this->m_Player->getPosition().y); // Ustaw pozycjê gracza na lewy brzeg ekranu
                break;

            case Level::DIRECTION::UP: // Jeœli zmiana pokoju w górê
                this->m_Player->setPosition(this->m_Player->getPosition().x, WINDOW_Y - (this->m_Player->getCollider().height / 2)); // Ustaw pozycjê gracza na dolny brzeg ekranu
                break;

            case Level::DIRECTION::DOWN: // Jeœli zmiana pokoju w dó³
                this->m_Player->setPosition(this->m_Player->getPosition().x, 0.0f); // Ustaw pozycjê gracza na górny brzeg ekranu
                break;
            }
}

// Funkcja renderuj¹ca stan gry
void GameManager::render() {
    // Dopóki okno jest otwarte
    while (this->m_Window->isOpen()) {

        this->eventManager(); // Zarz¹dzaj zdarzeniami

        // Jeœli okno gry nie jest na pierwszym planie i stan gry to PLAYING
        if (GetForegroundWindow() != this->m_WindowHandler &&
            this->getGameStatus() == GAMESTATE::PLAYING)
            this->setMenu(new PauseMenu(*this), GAMESTATE::PAUSED); // Ustaw menu pauzy

        this->m_Window->clear(); // Wyczyœæ okno
        //
        if (this->m_CurrentLevel != nullptr) {
            this->m_CurrentLevel->render(this->m_Window); // Renderuj bie¿¹cy poziom
            this->m_CurrentLevel->manageMusic(); // Zarz¹dzaj muzyk¹ poziomu
        }

        if (this->m_Player != nullptr) {
            this->m_Player->update(this->m_CurrentLevel->getCurrentRoom()->getPlatforms(), this->m_CurrentLevel->getCurrentRoom()->getKeys()); // Aktualizuj stan gracza
            this->m_Player->render(this->m_Window); // Renderuj gracza
        }

        if (this->m_Menu != nullptr) {
            this->m_Menu->render(this->m_Window); // Renderuj menu
            this->m_Menu->handleInput(this->m_Window, this->m_Event); // Przechwytuj zdarzenia menu
        }
        //
        this->m_Window->display(); // Wyœwietl zawartoœæ okna
    }
}
