/**
 * @file TouchScreen.hpp
 * @brief Classe de gestion de l'écran tactile I2C
 * 
 * Cette classe encapsule la communication I2C avec le contrôleur tactile du C3248W535C:
 * - Initialisation du bus I2C à 400kHz
 * - Reset matériel du contrôleur via GPIO
 * - Lecture des coordonnées tactiles (mono-touch)
 * - Calibration automatique selon la rotation de l'écran
 * - Détection de pression et relâchement
 * 
 * Protocole I2C:
 * - Adresse: 0x3B
 * - Commande: 11 octets envoyés
 * - Réponse: 8 octets reçus (dont coordonnées X/Y)
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

#include <Arduino.h>
#include <Wire.h>

/**
 * @class TouchScreen
 * @brief Classe de gestion du contrôleur tactile I2C
 * 
 * Fournit une interface simple pour détecter et lire les touches sur l'écran.
 * Supporte la rotation pour synchronisation avec la classe Display.
 * 
 * Exemple d'utilisation:
 * @code
 * TouchScreen touch;
 * touch.begin();
 * touch.setRotation(1);  // Paysage
 * 
 * uint16_t x, y;
 * if (touch.getTouchPoint(x, y)) {
 *     Serial.printf("Touché en (%d, %d)\n", x, y);
 * }
 * @endcode
 */
class TouchScreen {
private:
    // ========== Configuration matérielle I2C ==========
    
    /** @brief Adresse I2C du contrôleur tactile */
    static const uint8_t I2C_ADDR = 0x3B;
    /** @brief Broche SDA du bus I2C */
    static const uint8_t PIN_SDA  = 4;
    /** @brief Broche SCL du bus I2C */
    static const uint8_t PIN_SCL  = 8;
    /** @brief Broche Reset du contrôleur tactile */
    static const uint8_t PIN_RST  = 12;
    /** @brief Broche Interrupt (non utilisée actuellement) */
    static const uint8_t PIN_INT  = 11;
    /** @brief Fréquence du bus I2C en Hz */
    static const uint32_t I2C_CLOCK = 400000;
    
    /** @brief Nombre de points de toucher supportés (mono-touch) */
    static const uint8_t MAX_TOUCH_POINTS = 1;
    
    /** @brief Flag d'initialisation */
    bool initialized;
    /** @brief Rotation actuelle (0-3) pour calibration */
    uint8_t screenRotation;
    
    /**
     * @brief Envoie la commande de lecture au contrôleur tactile
     * 
     * Envoie une séquence de 11 octets pour demander les données de toucher.
     * 
     * @return true si la commande a été envoyée avec succès
     * @note Méthode interne
     */
    bool sendReadCommand();
    
    /**
     * @brief Lit les données brutes du contrôleur tactile
     * 
     * Reçoit 8 octets contenant l'état du toucher et les coordonnées.
     * 
     * @param[out] data Buffer pour stocker les données (minimum 8 octets)
     * @return true si des données valides ont été lues
     * @note Méthode interne
     */
    bool readTouchData(uint8_t* data);
    
    /**
     * @brief Décode les coordonnées brutes du buffer de données
     * 
     * Extrait les positions X et Y des octets bruts reçus.
     * 
     * @param[in] data Buffer contenant les données brutes (8 octets)
     * @param[out] x Coordonnée X décodée
     * @param[out] y Coordonnée Y décodée
     * @return true si un toucher valide a été détecté
     * @note Méthode interne
     */
    bool decodeTouchData(uint8_t* data, uint16_t& x, uint16_t& y);
    
    /**
     * @brief Applique la calibration selon la rotation de l'écran
     * 
     * Transforme les coordonnées brutes pour qu'elles correspondent
     * à l'orientation actuelle de l'écran.
     * 
     * @param[in] rawX Coordonnée X brute
     * @param[in] rawY Coordonnée Y brute
     * @param[out] x Coordonnée X calibrée
     * @param[out] y Coordonnée Y calibrée
     * @note Méthode interne
     */
    void calibrateCoordinates(uint16_t rawX, uint16_t rawY, uint16_t& x, uint16_t& y);

public:
    // ========== Constructeur ==========
    
    /**
     * @brief Constructeur de la classe TouchScreen
     * 
     * Initialise les variables internes. Le matériel n'est pas configuré.
     * Appelez begin() pour initialiser le bus I2C.
     */
    TouchScreen();
    
    // ========== Initialisation ==========
    
    /**
     * @brief Initialise le bus I2C et effectue le reset du contrôleur
     * 
     * Séquence d'initialisation:
     * 1. Configuration des broches SDA/SCL
     * 2. Démarrage du bus I2C à 400kHz
     * 3. Reset matériel via broche RST
     * 4. Délai de stabilisation
     * 
     * @return true si l'initialisation réussit, false en cas d'erreur
     * @note Appelez cette méthode dans setup() avant d'utiliser le tactile
     */
    bool begin();
    
    /**
     * @brief Configure la rotation pour la calibration des coordonnées
     * 
     * @param rotation Orientation:
     *                 - 0: Portrait (320x480)
     *                 - 1: Paysage (480x320)
     *                 - 2: Portrait inversé (320x480)
     *                 - 3: Paysage inversé (480x320)
     * @note Synchronisez avec Display::setRotation() pour des coordonnées cohérentes
     */
    void setRotation(uint8_t rotation);
    
    /**
     * @brief Retourne la rotation actuelle
     * @return Valeur de rotation (0-3)
     */
    uint8_t getRotation() const { return screenRotation; }
    
    // ========== Détection de toucher ==========
    
    /**
     * @brief Vérifie si l'écran est actuellement touché
     * 
     * @return true si un toucher est détecté, false sinon
     * @note N'attend pas, vérification instantanée
     */
    bool isTouched();
    
    /**
     * @brief Lit la position du toucher avec coordonnées calibrées
     * 
     * @param[out] x Coordonnée horizontale (0 à largeur-1)
     * @param[out] y Coordonnée verticale (0 à hauteur-1)
     * @return true si un toucher valide a été lu, false sinon
     * @note Les coordonnées sont automatiquement ajustées selon la rotation
     */
    bool getTouchPoint(uint16_t& x, uint16_t& y);
    
    /**
     * @brief Attend qu'un toucher soit détecté (bloquant)
     * 
     * @param timeout_ms Timeout en millisecondes (0 = attente infinie)
     * @return true si un toucher a été détecté, false si timeout atteint
     * @warning Fonction bloquante! Utilisez un timeout pour éviter de bloquer indéfiniment
     */
    bool waitForTouch(uint32_t timeout_ms = 0);
    
    /**
     * @brief Attend que l'écran soit relâché (bloquant)
     * 
     * Utile pour éviter la détection de multiples clics lors d'un seul toucher.
     * 
     * @param timeout_ms Timeout en millisecondes (0 = attente infinie)
     * @return true si l'écran a été relâché, false si timeout atteint
     * @warning Fonction bloquante!
     */
    bool waitForRelease(uint32_t timeout_ms = 0);
};

#endif // TOUCHSCREEN_H
