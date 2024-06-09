#pragma once // Zapewnia, �e ten plik nag��wkowy jest do��czany tylko raz podczas kompilacji
#include "Platform.h" // Do��cza plik nag��wkowy Platform
#include "Key.h" // Do��cza plik nag��wkowy Key

// Deklaracja wst�pna klasy GameManager
class GameManager;

// Klasa Player reprezentuje gracza w grze
class Player {
private:
    Texture m_Texture; // Tekstura gracza
    Sprite m_Sprite; // Sprite gracza
    float m_JumpVelocity = 1.0f, m_ElapsedTime = 0.0f, m_PowerJump = 1.0f; // Pr�dko�� skoku, czas od ostatniego skoku, moc skoku
    bool m_IsJumping = false, m_IsFalling = false, m_Splashed = false; // Flaga czy gracz skacze, czy spada, czy wpad� do wody
    int m_AnimationIndex = 0, m_FallTime = 0; // Indeks animacji, czas spadania
    vector<SoundBuffer*> m_SoundBuffers; // Bufory d�wi�k�w
    vector<Sound*> m_Sounds; // D�wi�ki
    class GameManager* m_GameManager; // Wska�nik do menad�era gry

    // Biblioteka d�wi�k�w
    vector<string> m_SoundLibrary = {
        "Jump.wav",
        "Slap.wav",
        "Coin.wav"
    };

    // Enum z efektami d�wi�kowymi
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

    // Metoda kontroluj�ca skok
    void jumpControl(vector<Platform*>, float);

    // Metoda kontroluj�ca animacje
    void animationControl(vector<Platform*>);

    // Metoda kontroluj�ca post�p gracza
    void progressionControl(vector<Key*>*);

    // Metoda kontroluj�ca przej�cie mi�dzy pokojami
    void roomControl(void);

    // Metoda wczytuj�ca d�wi�ki
    void loadSounds(void);

public:
    // Konstruktor klasy Player, kt�ry przyjmuje wska�nik do menad�era gry
    Player(GameManager*);

    // Metoda zwracaj�ca prostok�t kolizji gracza
    FloatRect getCollider(void) const;

    // Metoda zwracaj�ca pozycj� gracza
    Vector2f getPosition(void) { return this->m_Sprite.getPosition(); }

    // Metoda zwracaj�ca sprite gracza
    Sprite getSprite(void) { return this->m_Sprite; }

    // Metoda ustawiaj�ca pozycj� gracza
    void setPosition(float, float);

    // Metoda sprawdzaj�ca, czy gracz znajduje si� na platformie
    bool isOnPlatform(Platform*);

    // Metoda renderuj�ca gracza na podanym oknie renderowania
    void render(RenderWindow*);

    // Metoda aktualizuj�ca stan gracza
    void update(vector<Platform*>, vector<Key*>*);
};
