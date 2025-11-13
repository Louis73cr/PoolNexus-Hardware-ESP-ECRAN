/**
 * @file interface-utils.hpp
 * @brief Classe utilitaire pour les opérations d'interface
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#ifndef INTERFACE_UTILS_H
#define INTERFACE_UTILS_H

#include <Arduino.h>
#include "Page.hpp"
#include "../../screen/Display.hpp"
#include <vector>
#include <iostream>

// Déclaration forward du SwitchButton global
struct SwitchButton;

class interfaceUtils {

public:
    enum PAGE_TYPE {
        START_PAGE,
        HOME,
        PAGE,
        INFO,
        CONFIRMATION
    };



    struct TextZone {
        int id;
        int16_t x, y;
        String text;
        uint16_t textColor;
        bool isDisplayed;
        int fontSize;
        
        TextZone(int id, int16_t x, int16_t y, 
                   const char* txt, uint16_t fg, bool displayed, int fontSize = 2) 
            : id(id), x(x), y(y), 
              text(txt), textColor(fg), isDisplayed(displayed), fontSize(fontSize) {}
    };

    struct ImageZone {
        int id;
        int16_t x, y, width, height;
        const uint8_t* imageData;
        bool isDisplayed;
    
        ImageZone(int id, int16_t x, int16_t y, int16_t w, int16_t h,
                  const uint8_t* data, bool displayed) 
            : id(id), x(x), y(y), width(w), height(h),
              imageData(data), isDisplayed(displayed) {}
    };

    /**
     * @struct ButtonZone
     * @brief Structure complète représentant un bouton avec toutes ses propriétés
     */
    struct ButtonZone {
        int id;
        int16_t x, y, width, height;
        uint16_t bgColor;
        bool isActive;
        TextZone* textContent;   // Contenu texte optionnel
        ImageZone* imageContent; // Contenu image optionnel
        void (*onClickCallback)(void* context); // Callback avec contexte
        void* callbackContext; // Pointeur vers l'objet (this)

        // Constructeur par défaut
        ButtonZone() : id(0), x(0), y(0), width(0), height(0), bgColor(0), isActive(false),
                      textContent(nullptr), imageContent(nullptr), onClickCallback(nullptr), callbackContext(nullptr) {}

        ButtonZone(int id, int16_t x, int16_t y, int16_t w, int16_t h, 
                   uint16_t bg, bool active, TextZone* text = nullptr, 
                   ImageZone* image = nullptr, void (*callback)(void*) = nullptr,
                   void* context = nullptr) 
            : id(id), x(x), y(y), width(w), height(h), 
              bgColor(bg), isActive(active), textContent(text), 
              imageContent(image), onClickCallback(callback), callbackContext(context) {}
        
        bool contains(int16_t touchX, int16_t touchY) const {
            return (touchX >= x && touchX <= x + width && 
                    touchY >= y && touchY <= y + height);
        }
        
        /**
         * @brief Exécute le callback si le bouton est actif et qu'un callback existe
         * @return true si le callback a été exécuté, false sinon
         */
        bool execute() const {
            if (isActive && onClickCallback != nullptr) {
                onClickCallback(callbackContext);
                return true;
            }
            return false;
        }
    };

    /**
     * @struct SwitchButton
     * @brief Structure représentant un bouton switch avec deux états (ON/OFF)
     */
    struct SwitchButton {
        int id;
        int16_t x, y;
        bool isActive;
        ImageZone* imageContentON;  // Image affichée quand state = true
        ImageZone* imageContentOFF; // Image affichée quand state = false
        void (*onClickCallbackON)(void* context);  // Callback appelé lors du passage à ON
        void (*onClickCallbackOFF)(void* context); // Callback appelé lors du passage à OFF
        void* callbackContext; // Pointeur vers l'objet (this)
        bool state; // État actuel: true = ON, false = OFF

        SwitchButton(int id, int16_t x, int16_t y, 
                   bool active, bool initialState = false,
                   ImageZone* imageON = nullptr, ImageZone* imageOFF = nullptr, 
                   void (*callbackON)(void*) = nullptr, void (*callbackOFF)(void*) = nullptr,
                   void* context = nullptr) 
            : id(id), x(x), y(y), isActive(active), state(initialState),
              imageContentON(imageON), imageContentOFF(imageOFF), 
              onClickCallbackON(callbackON), onClickCallbackOFF(callbackOFF),
              callbackContext(context) {}
        
        bool contains(int16_t touchX, int16_t touchY) const {
            if (imageContentON == nullptr && imageContentOFF == nullptr) return false;
            
            // Utiliser les dimensions de l'image active
            ImageZone* activeImage = state ? imageContentON : imageContentOFF;
            if (activeImage == nullptr) return false;
            
            return (touchX >= x && touchX <= x + activeImage->width && 
                    touchY >= y && touchY <= y + activeImage->height);
        }
        
        /**
         * @brief Bascule l'état du switch et exécute le callback approprié
         * @return true si le callback a été exécuté, false sinon
         */
        bool toggle() {
            if (!isActive) return false;
            
            state = !state; // Inverser l'état
            
            if (state && onClickCallbackON != nullptr) {
                onClickCallbackON(callbackContext);
                return true;
            } else if (!state && onClickCallbackOFF != nullptr) {
                onClickCallbackOFF(callbackContext);
                return true;
            }
            return false;
        }
        
        /**
         * @brief Définit l'état du switch et exécute le callback approprié
         * @param newState Nouvel état (true = ON, false = OFF)
         * @return true si le callback a été exécuté, false sinon
         */
        bool setState(bool newState) {
            if (!isActive || state == newState) return false;
            
            state = newState;
            
            if (state && onClickCallbackON != nullptr) {
                onClickCallbackON(callbackContext);
                return true;
            } else if (!state && onClickCallbackOFF != nullptr) {
                onClickCallbackOFF(callbackContext);
                return true;
            }
            return false;
        }
    };

    enum TEXTFIELD_TYPE {
        TEXTFIELD_TEXT,
        TEXTFIELD_NUMBER,
        TEXTFIELD_PASSWORD,
    };

    struct TextFieldZone {
        int id;
        int16_t x, y, width, height;
        uint16_t bgColor;
        bool isActive;
        TextZone* textContent;   // Contenu texte optionnel
        void (*onClickCallback)(); // Pointeur vers la fonction à appeler lors du clic
        TEXTFIELD_TYPE type;

        TextFieldZone(int id, int16_t x, int16_t y, int16_t w, int16_t h, 
                   uint16_t bg, bool active, TextZone* text = nullptr, TEXTFIELD_TYPE type = TEXTFIELD_TEXT) 
            : id(id), x(x), y(y), width(w), height(h), 
              bgColor(bg), isActive(active), textContent(text), type(type) {}
        
        bool contains(int16_t touchX, int16_t touchY) const {
            return (touchX >= x && touchX <= x + width && 
                    touchY >= y && touchY <= y + height);
        }
        
        /**
         * @brief Exécute le callback si le bouton est actif et qu'un callback existe
         * @return true si le callback a été exécuté, false sinon
         */
        bool execute() const {
            if (isActive && onClickCallback != nullptr) {
                onClickCallback();
                return true;
            }
            return false;
        }
    };

public:
    //hex color: ebebf0
    static const uint16_t COLOR_BLANC_CASER  = 0xEF5E;
    //hex color: ffffff
    static const uint16_t COLOR_BLANC  = 0xFFFF;
    //hex color: 0f103a
    static const uint16_t COLOR_BLEU_NEXUS  = 0x0887;
    //hex color: 004aad
    static const uint16_t COLOR_BLEU  = 0x0255;
    //hex color: ff3131
    static const uint16_t COLOR_RED  = 0xF986;
    //hex color: 000000    
    static const uint16_t COLOR_BLACK  = 0x0000;
    //hex color: d9d9d9
    static const uint16_t COLOR_GREY_LOW  = 0xDEDB;
    //hex color: 464650
    static const uint16_t COLOR_GREY_HIGH  = 0x422A;
    //hex color: 00bf63
    static const uint16_t COLOR_GREEN  = 0x05EC;
    //hex color: ffbd59
    static const uint16_t COLOR_ORANGE  = 0xFDEB;
    //hex color: 3fcabf
    static const uint16_t COLOR_TURQUOISE  = 0x3E57;

    static const int BORDER_RADIUS  = 5;


protected:
    Display* display;
    std::vector<ButtonZone> buttonZones;
    int nextButtonId;

public:

    interfaceUtils(Display* display) : display(display), nextButtonId(0) {}
    virtual ~interfaceUtils() {}
    
    /**
     * @brief Crée et dessine un bouton avec toutes ses propriétés
     * @param button Structure ButtonZone contenant toutes les propriétés du bouton
     * @return ID unique du bouton pour la gestion tactile
     */
    void createButton(ButtonZone button);
    
    /**
     * @brief Dessine un bouton existant par son ID
     * @param id ID du bouton à dessiner
     * @return true si le bouton existe et a été dessiné, false sinon
     */
    bool drawButton(int id);

    /**
     * @brief Redessine tous les boutons
     */
    void drawAllButtons();
    
    /**
     * @brief Modifie le texte d'un bouton et le redessine
     * @param id ID du bouton
     * @param newText Nouveau texte
     * @return true si le bouton existe, false sinon
     */
    bool setButtonText(int id, const char* newText);
    
    /**
     * @brief Modifie l'état actif d'un bouton et le redessine
     * @param id ID du bouton
     * @param active Nouvel état
     * @return true si le bouton existe, false sinon
     */
    bool setButtonActive(int id, bool active);

    /**
     * @brief Modifie la couleur de fond d'un bouton et le redessine
     * @param id ID du bouton
     * @param bgColor Nouvelle couleur de fond
     * @return true si le bouton existe, false sinon
     */
    bool setButtonColor(int id, uint16_t bgColor);
    
    /**
     * @brief Vérifie quel bouton a été touché
     * @param touchX Coordonnée X du touch
     * @param touchY Coordonnée Y du touch
     * @return ID du bouton touché, ou -1 si aucun
     */
    int getTouchedButton(int16_t touchX, int16_t touchY);
    
    /**
     * @brief Exécute le callback du bouton spécifié par son ID
     * @param buttonId ID du bouton dont il faut exécuter le callback
     * @return true si le callback a été exécuté, false sinon
     */
    bool executeButtonCallback(int buttonId);
    
    /**
     * @brief Réinitialise toutes les zones tactiles
     * À appeler au début du draw() pour recréer les boutons
     */
    void clearButtons();

    /**
     * @brief Dessine le fond d'écran en fonction du type de page
     * @param pageType Type de la page pour déterminer le fond à dessiner
     * @return int id de bouton crée (-1 si aucun bouton créé)
     */
    void drawBackground(PAGE_TYPE pageType, void (*callback)(void*), void* context = nullptr,  String title = "");

    void drawAlertBox(const char* title, const char* message, void (*callback)(void*), void* context = nullptr);

    void drawInfoBox(const char* message, void (*callback)(void*), void* context = nullptr);

    void drawMutltiPageBox(const std::vector<std::pair<String, void (*)(void*)>>& title, void* context = nullptr);

    void drawTextField(TextFieldZone textField);

    void drawSwitchButton(::SwitchButton switchButton);

    void drawText(TextZone* textZone);


};

// Alias globaux pour faciliter l'utilisation
using ButtonZone = interfaceUtils::ButtonZone;
using TextZone = interfaceUtils::TextZone;
using ImageZone = interfaceUtils::ImageZone;

/**
 * @struct SwitchButton
 * @brief Structure simplifée pour bouton switch avec label textuel
 * 
 * Version étendue pour les pages de paramètres avec support texte
 */
struct SwitchButton {
    int id;
    int16_t x, y, width, height;
    String label;
    bool hasInfoIcon;
    bool isOn;
    void (*onToggleCallback)(void* context);
    void* callbackContext;
    
    SwitchButton() : id(0), x(0), y(0), width(0), height(0), 
                     label(""), hasInfoIcon(false), isOn(false),
                     onToggleCallback(nullptr), callbackContext(nullptr) {}
    
    void toggle() {
        isOn = !isOn;
        if (onToggleCallback != nullptr) {
            onToggleCallback(callbackContext);
        }
    }
    
    void setState(bool newState) {
        if (isOn != newState) {
            isOn = newState;
            if (onToggleCallback != nullptr) {
                onToggleCallback(callbackContext);
            }
        }
    }
};

#endif // INTERFACE_UTILS_H
