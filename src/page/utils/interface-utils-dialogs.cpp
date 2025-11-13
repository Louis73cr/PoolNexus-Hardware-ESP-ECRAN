/**
 * @file interface-utils-dialogs.cpp
 * @brief Implémentation des boîtes de dialogue (Alert, Info, etc.)
 * 
 * @author PoolNexus Hardware Team
 * @date 2025
 */

#include "interface-utils.hpp"

/**
 * @brief Dessine une boîte d'alerte avec titre, message et bouton OK
 */
void interfaceUtils::drawAlertBox(const char* title, const char* message, void (*callback)(void*), void* context) {
    const int16_t boxWidth = 300;
    const int16_t boxHeight = 200;
    const int16_t boxX = (display->getWidth() - boxWidth) / 2;
    const int16_t boxY = (display->getHeight() - boxHeight) / 2;
    
    // Fond semi-transparent (overlay)
    display->fillScreen(COLOR_BLACK);
    
    // Boîte principale
    display->fillRoundRect(boxX, boxY, boxWidth, boxHeight, BORDER_RADIUS * 2, COLOR_BLANC);
    display->drawRoundRect(boxX, boxY, boxWidth, boxHeight, BORDER_RADIUS * 2, COLOR_RED);
    
    // Barre de titre rouge
    display->fillRoundRect(boxX, boxY, boxWidth, 40, BORDER_RADIUS * 2, COLOR_RED);
    display->fillRect(boxX, boxY + 30, boxWidth, 10, COLOR_RED); // Coins carrés en bas
    
    // Titre en blanc
    display->setCursor(boxX + 10, boxY + 15);
    display->setTextColor(COLOR_BLANC);
    display->setTextSize(2);
    display->print(title);
    
    // Message
    display->setCursor(boxX + 10, boxY + 60);
    display->setTextColor(COLOR_BLACK);
    display->setTextSize(1);
    display->print(message);
    
    // Bouton OK
    TextZone* btnText = new TextZone(nextButtonId, 0, 0, "OK", COLOR_BLANC, true);
    ButtonZone okButton(
        nextButtonId++,
        boxX + (boxWidth - 100) / 2,
        boxY + boxHeight - 60,
        100, 40,
        COLOR_RED,
        true,
        btnText,
        nullptr,
        callback,
        context
    );
    
    createButton(okButton);
    display->flush();
}

/**
 * @brief Dessine une boîte d'information avec message et bouton OK
 */
void interfaceUtils::drawInfoBox(const char* message, void (*callback)(void*), void* context) {
    const int16_t boxWidth = 280;
    const int16_t boxHeight = 150;
    const int16_t boxX = (display->getWidth() - boxWidth) / 2;
    const int16_t boxY = (display->getHeight() - boxHeight) / 2;
    
    // Fond semi-transparent
    display->fillScreen(COLOR_GREY_HIGH);
    
    // Boîte principale
    display->fillRoundRect(boxX, boxY, boxWidth, boxHeight, BORDER_RADIUS * 2, COLOR_BLANC);
    display->drawRoundRect(boxX, boxY, boxWidth, boxHeight, BORDER_RADIUS * 2, COLOR_BLEU);
    
    // Icône info (i dans un cercle)
    display->fillCircle(boxX + 30, boxY + 40, 15, COLOR_BLEU);
    display->setCursor(boxX + 25, boxY + 30);
    display->setTextColor(COLOR_BLANC);
    display->setTextSize(2);
    display->print("i");
    
    // Message
    display->setCursor(boxX + 60, boxY + 30);
    display->setTextColor(COLOR_BLACK);
    display->setTextSize(1);
    display->print(message);
    
    // Bouton OK
    TextZone* btnText = new TextZone(nextButtonId, 0, 0, "OK", COLOR_BLANC, true);
    ButtonZone okButton(
        nextButtonId++,
        boxX + (boxWidth - 100) / 2,
        boxY + boxHeight - 50,
        100, 35,
        COLOR_BLEU,
        true,
        btnText,
        nullptr,
        callback,
        context
    );
    
    createButton(okButton);
    display->flush();
}

/**
 * @brief Dessine une boîte avec plusieurs options (menu)
 */
void interfaceUtils::drawMutltiPageBox(const std::vector<std::pair<String, void (*)(void*)>>& options, void* context) {
    const int16_t boxWidth = 350;
    const int16_t itemHeight = 50;
    const int16_t spacing = 10;
    const int16_t boxHeight = (itemHeight + spacing) * options.size() + spacing;
    const int16_t boxX = (display->getWidth() - boxWidth) / 2;
    const int16_t boxY = (display->getHeight() - boxHeight) / 2;
    
    // Fond
    display->fillRoundRect(boxX, boxY, boxWidth, boxHeight, BORDER_RADIUS * 2, COLOR_BLANC_CASER);
    display->drawRoundRect(boxX, boxY, boxWidth, boxHeight, BORDER_RADIUS * 2, COLOR_BLEU_NEXUS);
    
    // Créer les boutons pour chaque option
    for (size_t i = 0; i < options.size(); i++) {
        int16_t btnY = boxY + spacing + (itemHeight + spacing) * i;
        
        TextZone* btnText = new TextZone(nextButtonId, 0, 0, options[i].first.c_str(), COLOR_BLANC, true);
        ButtonZone optionButton(
            nextButtonId++,
            boxX + spacing,
            btnY,
            boxWidth - (spacing * 2),
            itemHeight,
            COLOR_BLEU,
            true,
            btnText,
            nullptr,
            options[i].second,
            context
        );
        
        createButton(optionButton);
    }
    
    display->flush();
}
