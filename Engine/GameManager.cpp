#include "GameManager.h" // Do��cza plik nag��wkowy GameManager

// Konstruktor klasy GameManager
GameManager::GameManager() {
    // Tworzy nowe okno renderowania z okre�lonym trybem wideo i tytu�em gry
    this->m_Window = new RenderWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), GAME_TITLE);
    // Pobiera uchwyt systemowy okna
    this->m_WindowHandler = this->m_Window->getSystemHandle();

    // Je�li tryb debugowania jest wy��czony
    if (!DEBUGGING) {
        this->m_GameState = GAMESTATE::MAINMENU; // Ustawia stan gry na MENU G��WNE
        this->m_Player = nullptr; // Inicjalizuje wska�nik gracza jako nullptr
        this->m_CurrentLevel = nullptr; // Inicjalizuje wska�nik bie��cego poziomu jako nullptr
        this->m_Menu = new MainMenu(*this); // Tworzy nowe menu g��wne
    }
    else this->restartGame(); // Restartuje gr� w trybie debugowania ( pomija menu g��wne )

    this->loadSettings(); // �aduje ustawienia gry
    this->render(); // Uruchamia renderowanie gry
}

// Funkcja �aduj�ca ustawienia gry
void GameManager::loadSettings() {
    srand(time(NULL)); // Inicjalizuje generator liczb losowych

    this->m_Window->setFramerateLimit(FRAMERATE_LIMIT); // Ustawia limit liczby klatek na sekund�
    HWND hwnd = GetConsoleWindow(); // Pobiera uchwyt okna konsoli
    ShowWindow(hwnd, ENABLE_CONSOLE); // Wy�wietla okno konsoli

    // Je�li taskbar ma by� wy��czony
    if (DISABLE_TASKBAR) {
        HWND hwnd = this->m_Window->getSystemHandle(); // Pobiera uchwyt systemowy okna gry
        LONG style = GetWindowLong(hwnd, GWL_STYLE); // Pobiera styl okna
        style &= ~WS_SYSMENU; // Usuwa menu systemowe
        style &= ~WS_CAPTION; // Usuwa pasek tytu�owy
        style &= ~WS_THICKFRAME; // Usuwa mo�liwo�� zmiany rozmiaru okna
        style &= ~WS_MINIMIZEBOX; // Usuwa przycisk minimalizacji
        style &= ~WS_MAXIMIZEBOX; // Usuwa przycisk maksymalizacji
        SetWindowLong(hwnd, GWL_STYLE, style); // Ustawia nowy styl okna
        SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER); // Aktualizuje pozycj� okna
    }
}

// Funkcja zarz�dzaj�ca zdarzeniami w grze
void GameManager::eventManager() {
    // Je�li stan gry nie jest PLAYING, zako�cz
    if (this->getGameStatus() != GAMESTATE::PLAYING)
        return;

    // Przechwytywanie zdarze� w oknie gry
    while (this->m_Window->pollEvent(this->m_Event))
        switch (this->m_Event.type) {
        case Event::Closed: // Je�li okno zosta�o zamkni�te
            this->m_Window->close(); // Zamknij okno
            break;

        case Event::KeyPressed: // Je�li klawisz zosta� naci�ni�ty
            // Je�li klawisz to Escape i stan gry to PLAYING
            if (this->m_Event.key.code == Keyboard::Escape &&
                this->getGameStatus() == GAMESTATE::PLAYING)
                this->setMenu(new PauseMenu(*this), GAMESTATE::PAUSED); // Ustaw menu pauzy
            break;
        }
}

// Funkcja ustawiaj�ca menu i stan gry
void GameManager::setMenu(Menu* _menu, int _state) {
    this->m_GameState = _state; // Ustawia stan gry
    delete this->m_Menu; // Usuwa poprzednie menu
    this->m_Menu = _menu; // Ustawia nowe menu

    // Je�li stan gry to PLAYING i wska�niki gracza lub bie��cego poziomu s� nullptr
    if (this->m_GameState == GAMESTATE::PLAYING &&
        (this->m_Player == nullptr || this->m_CurrentLevel == nullptr)) {
        this->m_Player = new Player(this); // Tworzy nowego gracza
        this->m_CurrentLevel = new TestLevel(this); // Tworzy nowy poziom testowy
    }
}

// Funkcja restartuj�ca gr�
void GameManager::restartGame(void) {
    delete this->m_Menu; // Usuwa aktualne menu
    delete this->m_Player; // Usuwa obiekt gracza
    delete this->m_CurrentLevel; // Usuwa bie��cy poziom

    this->m_Menu = nullptr; // Ustawia wska�nik menu na nullptr
    this->m_GameState = GAMESTATE::PLAYING; // Ustawia stan gry na PLAYING
    this->m_Player = new Player(this); // Tworzy nowego gracza
    this->m_CurrentLevel = new TestLevel(this); // Tworzy nowy poziom testowy

    this->m_GameTime = 0; // Zeruje up�yni�ty czas gry
    this->m_ElapsedTime = 0.f; // Zeruje czas zegara
}

// Funkcja zmieniaj�ca pok�j w poziomie
void GameManager::changeRoom(int _direction) {
    // Je�li bie��cy poziom nie jest nullptr
    if (this->m_CurrentLevel != nullptr)
        // Je�li zmiana pokoju powiod�a si�
        if (this->m_CurrentLevel->changeRoom(_direction))
            switch (_direction) {
            case Level::DIRECTION::LEFT: // Je�li zmiana pokoju na lewo
                this->m_Player->setPosition(WINDOW_X - this->m_Player->getCollider().width, this->m_Player->getPosition().y); // Ustaw pozycj� gracza na prawy brzeg ekranu
                break;

            case Level::DIRECTION::RIGHT: // Je�li zmiana pokoju na prawo
                this->m_Player->setPosition(0.0f, this->m_Player->getPosition().y); // Ustaw pozycj� gracza na lewy brzeg ekranu
                break;

            case Level::DIRECTION::UP: // Je�li zmiana pokoju w g�r�
                this->m_Player->setPosition(this->m_Player->getPosition().x, WINDOW_Y - (this->m_Player->getCollider().height / 2)); // Ustaw pozycj� gracza na dolny brzeg ekranu
                break;

            case Level::DIRECTION::DOWN: // Je�li zmiana pokoju w d�
                this->m_Player->setPosition(this->m_Player->getPosition().x, 0.0f); // Ustaw pozycj� gracza na g�rny brzeg ekranu
                break;
            }
}

// Funkcja ko�cz�ca gr�
void GameManager::gameOver(void) {
    this->setMenu(new GameOverMenu(*this), GameManager::GAMESTATE::OVER);

    // Zapis wyniku gry
    ofstream scoreBoard("Scoreboard.txt", std::ios::app);
    if (scoreBoard.is_open()) {
        int minutes = this->m_GameTime / 60;
        int hours = minutes / 60;
        scoreBoard << getenv("USERNAME") << " | " << hours << ":" << minutes % 60 << ":" << this->m_GameTime % 60 << '\n';
        scoreBoard.close();
    }
}

// Funkcja renderuj�ca stan gry
void GameManager::render() {
    // Dop�ki okno jest otwarte
    while (this->m_Window->isOpen()) {

        this->eventManager(); // Zarz�dzaj zdarzeniami

        // Je�li okno gry nie jest na pierwszym planie i stan gry to PLAYING
        if (GetForegroundWindow() != this->m_WindowHandler &&
            this->getGameStatus() == GAMESTATE::PLAYING)
            this->setMenu(new PauseMenu(*this), GAMESTATE::PAUSED); // Ustaw menu pauzy

        // Je�li stan gry to PLAYING odmierza czas
        if (this->getGameStatus() == GAMESTATE::PLAYING) {
            this->m_ElapsedTime += this->m_Clock.restart().asSeconds();
            
            if (this->m_ElapsedTime >= 1.f) {
                this->m_ElapsedTime = 0.f;
                this->m_GameTime++;
                std::cout << this->m_ElapsedTime << std::endl;
            }
        }

        this->m_Window->clear(); // Wyczy�� okno
        //
        if (this->m_CurrentLevel != nullptr) {
            this->m_CurrentLevel->render(this->m_Window); // Renderuj bie��cy poziom
            this->m_CurrentLevel->manageMusic(); // Zarz�dzaj muzyk� poziomu
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
        this->m_Window->display(); // Wy�wietl zawarto�� okna
    }
}
