/**
 * @file Display.hpp
 * @brief Classe de gestion de l'écran QSPI AXS15231B
 * 
 * Cette classe encapsule toute la logique d'affichage pour l'écran C3248W535C:
 * - Initialisation du bus QSPI (6 broches)
 * - Configuration du contrôleur AXS15231B
 * - Fonctions de dessin (texte, formes géométriques, remplissage)
 * - Gestion du rétro-éclairage
 * - Buffering avec Arduino_Canvas pour éviter le scintillement
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Arduino_GFX_Library.h>

/**
 * @class Display
 * @brief Classe d'abstraction pour l'écran LCD QSPI 480x320
 * 
 * Cette classe fournit une interface complète pour contrôler l'écran tactile
 * C3248W535C avec contrôleur AXS15231B via bus QSPI.
 * 
 * Caractéristiques:
 * - Résolution native: 320x480 (portrait) / 480x320 (paysage)
 * - Interface: QSPI 6 broches
 * - Format couleur: RGB565 (16 bits)
 * - Double buffering via Arduino_Canvas
 * - Support rotation 0-3
 * 
 * Exemple d'utilisation:
 * @code
 * Display screen;
 * screen.begin();
 * screen.setRotation(1);  // Mode paysage
 * screen.fillScreen(Display::COLOR_BLUE);
 * screen.setTextColor(Display::COLOR_WHITE);
 * screen.setCursor(10, 10);
 * screen.print("Hello World!");
 * screen.flush();  // Afficher sur l'écran physique
 * @endcode
 */
class Display {
private:
    // ========== Configuration matérielle ==========
    
    /** @brief Broche Chip Select du bus QSPI */
    static const uint8_t PIN_CS   = 45;
    /** @brief Broche Clock du bus QSPI */
    static const uint8_t PIN_SCK  = 47;
    /** @brief Broche Master Out Slave In du bus QSPI */
    static const uint8_t PIN_MOSI = 21;
    /** @brief Broche Master In Slave Out du bus QSPI */
    static const uint8_t PIN_MISO = 48;
    /** @brief Broche Data/Command du contrôleur */
    static const uint8_t PIN_DC   = 40;
    /** @brief Broche Reset du contrôleur */
    static const uint8_t PIN_RST  = 39;
    
    /** @brief Broche de contrôle du rétro-éclairage */
    static const uint8_t PIN_BL = 1;
    
    /** @brief Largeur de l'écran en mode portrait (rotation 0 ou 2) */
    static const uint16_t WIDTH_PORTRAIT  = 320;
    /** @brief Hauteur de l'écran en mode portrait (rotation 0 ou 2) */
    static const uint16_t HEIGHT_PORTRAIT = 480;
    
    // ========== Objets internes Arduino_GFX ==========
    
    /** @brief Pointeur vers le bus de communication QSPI */
    Arduino_DataBus *bus;
    /** @brief Pointeur vers le pilote du contrôleur AXS15231B */
    Arduino_GFX *display;
    /** @brief Pointeur vers le buffer graphique (double buffering) */
    Arduino_Canvas *canvas;
    
    /** @brief Rotation actuelle de l'écran (0=portrait, 1=paysage, 2=portrait inversé, 3=paysage inversé) */
    uint8_t currentRotation;

public:
    // ========== Constructeur et destructeur ==========
    
    /**
     * @brief Constructeur de la classe Display
     * 
     * Initialise les pointeurs à nullptr. Le matériel n'est pas configuré.
     * Appelez begin() pour initialiser l'écran physique.
     */
    Display();
    
    /**
     * @brief Destructeur de la classe Display
     * 
     * Libère automatiquement la mémoire allouée pour bus, display et canvas.
     */
    ~Display();
    
    // ========== Initialisation et configuration ==========
    
    /**
     * @brief Initialise le bus QSPI, le contrôleur AXS15231B et le rétro-éclairage
     * 
     * Séquence d'initialisation:
     * 1. Création du bus QSPI avec les broches configurées
     * 2. Création du pilote AXS15231B
     * 3. Initialisation du contrôleur
     * 4. Création du buffer canvas (480x320)
     * 5. Activation du rétro-éclairage
     * 
     * @return true si l'initialisation réussit, false en cas d'erreur
     * @note Cette méthode doit être appelée dans setup() avant toute autre opération
     */
    bool begin();
    
    /**
     * @brief Change l'orientation de l'écran
     * 
     * @param rotation Orientation souhaitée:
     *                 - 0: Portrait (320x480)
     *                 - 1: Paysage (480x320)
     *                 - 2: Portrait inversé (320x480)
     *                 - 3: Paysage inversé (480x320)
     * @note Pensez à synchroniser avec TouchScreen::setRotation()
     */
    void setRotation(uint8_t rotation);
    
    /**
     * @brief Retourne la rotation actuelle de l'écran
     * @return Valeur de rotation (0-3)
     */
    uint8_t getRotation() const { return currentRotation; }
    
    /**
     * @brief Retourne la largeur actuelle de l'écran
     * @return Largeur en pixels (320 pour portrait, 480 pour paysage)
     */
    uint16_t getWidth();
    
    /**
     * @brief Retourne la hauteur actuelle de l'écran
     * @return Hauteur en pixels (480 pour portrait, 320 pour paysage)
     */
    uint16_t getHeight();
    
    /**
     * @brief Contrôle l'état du rétro-éclairage
     * @param enabled true pour allumer, false pour éteindre
     */
    void setBacklight(bool enabled);
    
    // ========== Primitives de dessin ==========
    
    /**
     * @brief Remplit tout l'écran avec une couleur unie
     * @param color Couleur au format RGB565 (16 bits)
     * @note N'oubliez pas d'appeler flush() pour afficher
     */
    void fillScreen(uint16_t color);
    
    /**
     * @brief Dessine un pixel unique
     * @param x Position horizontale (0 à width-1)
     * @param y Position verticale (0 à height-1)
     * @param color Couleur RGB565
     */
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    
    /**
     * @brief Trace une ligne entre deux points
     * @param x0 Position X du point de départ
     * @param y0 Position Y du point de départ
     * @param x1 Position X du point d'arrivée
     * @param y1 Position Y du point d'arrivée
     * @param color Couleur de la ligne RGB565
     */
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
    
    /**
     * @brief Dessine le contour d'un rectangle
     * @param x Position X du coin supérieur gauche
     * @param y Position Y du coin supérieur gauche
     * @param w Largeur du rectangle
     * @param h Hauteur du rectangle
     * @param color Couleur du contour RGB565
     */
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    
    /**
     * @brief Dessine un rectangle plein
     * @param x Position X du coin supérieur gauche
     * @param y Position Y du coin supérieur gauche
     * @param w Largeur du rectangle
     * @param h Hauteur du rectangle
     * @param color Couleur de remplissage RGB565
     */
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    
    /**
     * @brief Dessine le contour d'un cercle
     * @param x Position X du centre
     * @param y Position Y du centre
     * @param r Rayon en pixels
     * @param color Couleur du contour RGB565
     */
    void drawCircle(int16_t x, int16_t y, int16_t r, uint16_t color);
    
    /**
     * @brief Dessine un cercle plein
     * @param x Position X du centre
     * @param y Position Y du centre
     * @param r Rayon en pixels
     * @param color Couleur de remplissage RGB565
     */
    void fillCircle(int16_t x, int16_t y, int16_t r, uint16_t color);
    
    /**
     * @brief Dessine le contour d'un triangle
     * @param x0 Position X du premier sommet
     * @param y0 Position Y du premier sommet
     * @param x1 Position X du deuxième sommet
     * @param y1 Position Y du deuxième sommet
     * @param x2 Position X du troisième sommet
     * @param y2 Position Y du troisième sommet
     * @param color Couleur du contour RGB565
     */
    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    
    /**
     * @brief Dessine un triangle plein
     * @param x0 Position X du premier sommet
     * @param y0 Position Y du premier sommet
     * @param x1 Position X du deuxième sommet
     * @param y1 Position Y du deuxième sommet
     * @param x2 Position X du troisième sommet
     * @param y2 Position Y du troisième sommet
     * @param color Couleur de remplissage RGB565
     */
    void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    
    // ========== Fonctions de rendu de texte ==========
    
    /**
     * @brief Positionne le curseur pour le prochain affichage de texte
     * @param x Position horizontale en pixels
     * @param y Position verticale en pixels
     */
    void setCursor(int16_t x, int16_t y);
    
    /**
     * @brief Définit la couleur du texte (fond transparent)
     * @param color Couleur RGB565 du texte
     */
    void setTextColor(uint16_t color);
    
    /**
     * @brief Définit la couleur du texte avec fond opaque
     * @param color Couleur RGB565 du texte
     * @param bgColor Couleur RGB565 du fond
     */
    void setTextColor(uint16_t color, uint16_t bgColor);
    
    /**
     * @brief Définit la taille du texte
     * @param size Facteur d'échelle (1=normal, 2=double, 3=triple, etc.)
     * @note Taille 1 = 6x8 pixels par caractère
     */
    void setTextSize(uint8_t size);
    
    /**
     * @brief Affiche du texte à la position du curseur (sans retour ligne)
     * @param text Chaîne de caractères à afficher
     */
    void print(const char* text);
    
    /**
     * @brief Affiche un String à la position du curseur
     * @param text Objet String à afficher
     */
    void print(const String& text);
    
    /**
     * @brief Affiche un entier signé
     * @param number Nombre à afficher
     */
    void print(int number);
    
    /**
     * @brief Affiche un entier non signé
     * @param number Nombre à afficher
     */
    void print(unsigned int number);
    
    /**
     * @brief Affiche un long signé
     * @param number Nombre à afficher
     */
    void print(long number);
    
    /**
     * @brief Affiche un long non signé
     * @param number Nombre à afficher
     */
    void print(unsigned long number);
    
    /**
     * @brief Affiche un nombre à virgule flottante
     * @param number Nombre à afficher
     * @param decimals Nombre de décimales (par défaut: 2)
     */
    void print(float number, int decimals = 2);
    
    /**
     * @brief Affiche du texte avec retour à la ligne
     * @param text Chaîne à afficher
     */
    void println(const char* text);
    
    /**
     * @brief Affiche un String avec retour à la ligne
     * @param text Objet String à afficher
     */
    void println(const String& text);
    
    /**
     * @brief Affiche un entier signé avec retour à la ligne
     * @param number Nombre à afficher
     */
    void println(int number);
    
    /**
     * @brief Affiche un entier non signé avec retour à la ligne
     * @param number Nombre à afficher
     */
    void println(unsigned int number);
    
    /**
     * @brief Affiche un long signé avec retour à la ligne
     * @param number Nombre à afficher
     */
    void println(long number);
    
    /**
     * @brief Affiche un long non signé avec retour à la ligne
     * @param number Nombre à afficher
     */
    void println(unsigned long number);
    
    /**
     * @brief Affiche un nombre flottant avec retour à la ligne
     * @param number Nombre à afficher
     * @param decimals Nombre de décimales (par défaut: 2)
     */
    void println(float number, int decimals = 2);
    
    // ========== Gestion du buffer graphique ==========
    
    /**
     * @brief Envoie le contenu du buffer canvas vers l'écran physique
     * 
     * Cette méthode est OBLIGATOIRE pour afficher les modifications.
     * Toutes les fonctions de dessin travaillent dans un buffer mémoire,
     * flush() copie ce buffer vers l'écran LCD.
     * 
     * @note Appelez flush() après avoir terminé tous vos dessins pour maximiser les performances
     */
    void flush();
    
    /**
     * @brief Efface le contenu du buffer (sans l'afficher)
     * @note Le buffer est rempli avec la couleur noire (0x0000)
     */
    void clear();
    
    // ========== Palette de couleurs RGB565 ==========
    
    /** @brief Noir pur (R:0 G:0 B:0) */
    static const uint16_t COLOR_BLACK   = 0x0000;
    /** @brief Blanc pur (R:255 G:255 B:255) */
    static const uint16_t COLOR_WHITE   = 0xFFFF;
    /** @brief Rouge pur (R:255 G:0 B:0) */
    static const uint16_t COLOR_RED     = 0xF800;
    /** @brief Vert pur (R:0 G:255 B:0) */
    static const uint16_t COLOR_GREEN   = 0x07E0;
    /** @brief Bleu pur (R:0 G:0 B:255) */
    static const uint16_t COLOR_BLUE    = 0x001F;
    /** @brief Jaune (R:255 G:255 B:0) */
    static const uint16_t COLOR_YELLOW  = 0xFFE0;
    /** @brief Cyan (R:0 G:255 B:255) */
    static const uint16_t COLOR_CYAN    = 0x07FF;
    /** @brief Magenta (R:255 G:0 B:255) */
    static const uint16_t COLOR_MAGENTA = 0xF81F;
    /** @brief Orange (R:255 G:165 B:0) */
    static const uint16_t COLOR_ORANGE  = 0xFD20;
    /** @brief Violet (R:128 G:0 B:128) */
    static const uint16_t COLOR_PURPLE  = 0x8010;
    /** @brief Gris moyen (R:128 G:128 B:128) */
    static const uint16_t COLOR_GRAY    = 0x8410;
};

#endif // DISPLAY_H
