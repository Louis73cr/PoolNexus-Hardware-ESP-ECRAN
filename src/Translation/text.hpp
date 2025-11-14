/* **************************************************************************** */
/*                                                                              */
/*                                                  ::::    :::     ::::::::    */
/*   text.hpp                                       :+:+:   :+:    :+:    :+:   */
/*                                                  :+:+:+  +:+    +:+          */
/*   By: Louis Croci <louis.croci@epitech.eu>       +#+ +:+ +#+    +#++:++#++   */
/*                                                  +#+  +#+#+#           +#+   */
/*   Created: 2025/11/14 21:08:26 by Louis Croci    #+#   #+#+#    #+#    #+#   */
/*   Updated: 2025/11/14 21:08:26 by Louis Croci    ###    ####     ########    */
/*                                                                              */
/* **************************************************************************** */

/**
 * @file text.hpp
 * @brief Text translation and language management for UI.
 *
 * Provides language selection and translated text for UI elements.
 * Supports direct access to translated strings for main pages, settings, and pool parameters.
 */
#pragma once

#include <cstdint>

/**
 * @class Text
 * @brief Manages UI text translations and language selection.
 *
 * Use this class to get translated strings for different UI elements based on the selected language.
 */
class Text {
public:
    /**
     * @brief Supported languages for translation.
     */
    enum class Language : uint8_t {
        FRENCH = 0,
        ENGLISH = 1,
        LANGUAGE_COUNT  // Keep this last
    };

    /**
     * @brief Set the current language for translations.
     * @param lang Language to set.
     */
    void setLanguage(Language lang) {
        currentLanguage = lang;
    }

    /**
     * @brief Get the currently selected language.
     * @return Current language.
     */
    Language getCurrentLanguage() const {
        return currentLanguage;
    }

    /**
     * @brief Get the display name of a language.
     * @param lang Language to get name for.
     * @return Name of the language as a string.
     */
    const char* getLanguageName(Language lang) const {
        static constexpr const char* languageNames[] = {
            "Francais",
            "English"
        };
        
        const uint8_t index = static_cast<uint8_t>(lang);
        if (index >= static_cast<uint8_t>(Language::LANGUAGE_COUNT)) return "";
        return languageNames[index];
    }

    
    /**
     * @struct MainPage
     * @brief Provides translated strings for main page UI elements.
     */
    struct MainPage {
        static const char* temperature(Language lang) {
            static constexpr const char* t[][2] = {{"Temp", "Temp"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
        static const char* regulations_switch(Language lang) {
            static constexpr const char* t[][2] = {{"Regulations", "Regulations"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
        static const char* pomp_switch(Language lang) {
            static constexpr const char* t[][2] = {{"Regulations", "Regulations"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
        static const char* settings(Language lang) {
            static constexpr const char* t[][2] = {{"Paramètres", "Settings"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
        static const char* alert(Language lang) {
            static constexpr const char* t[][2] = {{"Alertes", "Alerts"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
        static const char* historique(Language lang) {
            static constexpr const char* t[][2] = {{"Historique pH/Redox", "pH/Redox History"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
    };

    /**
     * @struct Settings
     * @brief Provides translated strings for settings page UI elements.
     */
    struct Settings {
        static const char* pump(Language lang) {
            static constexpr const char* t[][2] = {{"Pompe", "Pump"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
        static const char* calibration_Redox(Language lang) {
            static constexpr const char* t[][2] = {{"Calibration Redox", "Redox Calibration"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
        static const char* calibration_pH(Language lang) {
            static constexpr const char* t[][2] = {{"Calibration pH", "pH Calibration"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
        static const char* wifi(Language lang) {
            static constexpr const char* t[][2] = {{"WiFi", "WiFi"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
        static const char* language(Language lang) {
            static constexpr const char* t[][2] = {{"Langue", "Language"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
        static const char* pool_fill(Language lang) {
            static constexpr const char* t[][2] = {{"Remplissage piscine", "Pool Fill"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
        static const char* switch_(Language lang) {
            static constexpr const char* t[][2] = {{"Interrupteur", "Switch"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
        static const char* product_level(Language lang) {
            static constexpr const char* t[][2] = {{"Sonde de niveau de produit", "Product Level Sensor"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
        static const char* lock_screen(Language lang) {
            static constexpr const char* t[][2] = {{"Ecran de verrouillage", "Lock Screen"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
        static const char* screen(Language lang) {
            static constexpr const char* t[][2] = {{"Ecran", "Screen"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
        static const char* cloud(Language lang) {
            static constexpr const char* t[][2] = {{"Cloud", "Cloud"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
        static const char* reset(Language lang) {
            static constexpr const char* t[][2] = {{"Réinitialiser", "Reset"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
    };

    /**
     * @struct Pool
     * @brief Provides translated strings for pool parameters.
     */
    struct Pool {
        static const char* ph(Language lang) {
            static constexpr const char* t[][2] = {{"pH", "pH"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
        static const char* redox(Language lang) {
            static constexpr const char* t[][2] = {{"Redox", "Redox"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
        static const char* temperature(Language lang) {
            static constexpr const char* t[][2] = {{"Temperature", "Temperature"}};
            return t[0][static_cast<uint8_t>(lang) % 2];
        }
    };

private:
    Language currentLanguage = Language::FRENCH;
};



