#pragma once // Zapewnia, ¿e ten plik nag³ówkowy jest do³¹czany tylko raz podczas kompilacji
#include "Platform.h" // Do³¹cza plik nag³ówkowy Platform
#include "Key.h" // Do³¹cza plik nag³ówkowy Key

// Deklaracja wstêpna klasy GameManager
class GameManager;

// Klasa Player reprezentuje gracza w grze
class Player {
private:
    Texture m_Texture; // Tekstura gracza
    Sprite m_Sprite; // Sprite gracza
    float m_JumpVelocity = 1.0f, m_ElapsedTime = 0.0f, m_PowerJump = 1.0f; // Prêdkoœæ skoku, czas od ostatniego skoku, moc skoku
    bool m_IsJumping = false, m_IsFalling = false, m_Splashed = false; // Flaga czy gracz skacze, czy spada, czy wpad³ do wody
    int m_AnimationIndex = 0, m_FallTime = 0; // Indeks animacji, czas spadania
    vector<SoundBuffer*> m_SoundBuffers; // Bufory dŸwiêków
    vector<Sound*> m_Sounds; // DŸwiêki
    class GameManager* m_GameManager; // WskaŸnik do menad¿era gry

    // Biblioteka dŸwiêków
    vector<string> m_SoundLibrary = {
        "Jump.wav",
        "Slap.wav",
        "Coin.wav"
    };

    // Enum z efektami dŸwiêkowymi
    enum SFXS {
        JUMPSOUND,
        SPLASHSOUND,
        COINSOUND
    };

    // Enum z ramkami animacji
    enum ANIMATIONFRAMES {
        DEFAULT,
        WALK00,
        WALK01,
        WALK02,
        DOWN,
        JUMP,
        FALL,
        FLAT,
        OBLIQUE,
        TPOSE00,
        TPOSE01,
        TPOSE02,
        TPOSE03,
        UP
    };

    // Wektor ramek animacji
    vector<IntRect> m_AnimationFrames = {
        IntRect(0, 0, 64, 64),
        IntRect(64, 0, 64, 64),
        IntRect(128, 0, 64, 64),
        IntRect(192, 0, 64, 64),
        IntRect(0, 64, 64, 64),
        IntRect(64, 64, 64, 64),
        IntRect(128, 64, 64, 64),
        IntRect(192, 64, 64, 64),
        IntRect(0, 128, 64, 64),
        IntRect(64, 128, 64, 64),
        IntRect(128, 128, 64, 64),
        IntRect(192, 128, 64, 64),
        IntRect(0, 192, 64, 64),
        IntRect(64, 192, 64, 64)
    };

    // Metoda kontroluj¹ca skok
    void jumpControl(vector<Platform*>, float);

    // Metoda kontroluj¹ca animacje
    void animationControl(vector<Platform*>);

    // Metoda kontroluj¹ca postêp gracza
    void progressionControl(vector<Key*>*);

    // Metoda kontroluj¹ca przejœcie miêdzy pokojami
    void roomControl(void);

    // Metoda wczytuj¹ca dŸwiêki
    void loadSounds(void);

public:
    // Konstruktor klasy Player, który przyjmuje wskaŸnik do menad¿era gry
    Player(GameManager*);

    // Metoda zwracaj¹ca prostok¹t kolizji gracza
    FloatRect getCollider(void) const;

    // Metoda zwracaj¹ca pozycjê gracza
    Vector2f getPosition(void) { return this->m_Sprite.getPosition(); }

    // Metoda zwracaj¹ca sprite gracza
    Sprite getSprite(void) { return this->m_Sprite; }

    // Metoda ustawiaj¹ca pozycjê gracza
    void setPosition(float, float);

    // Metoda sprawdzaj¹ca, czy gracz znajduje siê na platformie
    bool isOnPlatform(Platform*);

    // Metoda renderuj¹ca gracza na podanym oknie renderowania
    void render(RenderWindow*);

    // Metoda aktualizuj¹ca stan gracza
    void update(vector<Platform*>, vector<Key*>*);
};
