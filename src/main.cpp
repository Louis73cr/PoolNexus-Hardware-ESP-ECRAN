/**
 * @file main.cpp
 * @brief Application principale pour ESP32-S3 avec écran tactile C3248W535C
 * 
 * Cette application implémente un système de navigation multi-pages pour
 * l'écran tactile QSPI 480x320 avec contrôleur AXS15231B.
 * 
 * Architecture:
 * - Pattern State Machine pour la navigation entre pages
 * - PageManager gère automatiquement l'affichage et les interactions
 * - Chaque page hérite de la classe abstraite Page
 * - Interface tactile I2C pour la navigation
 * 
 * Pages disponibles:
 * - HomePage: Page d'accueil avec informations système
 * - MenuPage: Menu de navigation principal
 * - SettingsPage: Configuration de l'application
 * - StatusPage: Statut système en temps réel
 * 
 * Matériel:
 * - MCU: ESP32-S3 (Dual-core Xtensa LX7, 240MHz)
 * - Écran: C3248W535C_I_Y (480x320, QSPI, RGB565)
 * - Touch: Contrôleur I2C @ 0x3B
 * - RAM: 8MB PSRAM intégrée
 * 
 * @author PoolNexus Hardware Team
 * @version 1.0
 * @date 2025
 */

#include <Arduino.h>
#include "screen/Display.h"
#include "screen/TouchScreen.h"
#include "page/utils/PageManager.h"
#include "page/HomePage.h"
#include "page/MenuPage.h"
#include "page/SettingsPage.h"
#include "page/StatusPage.h"

// ========== DÉFINITION DES IDs DE PAGES ==========

/** @brief Identifiant de la page d'accueil */
#define PAGE_HOME      0
/** @brief Identifiant de la page de menu */
#define PAGE_MENU      1
/** @brief Identifiant de la page de paramètres */
#define PAGE_SETTINGS  2
/** @brief Identifiant de la page de statut */
#define PAGE_STATUS    3
/** @brief Nombre total de pages dans l'application */
#define NUM_PAGES      4

// ========== INSTANCES DES CLASSES ==========

/** @brief Objet de gestion de l'écran LCD QSPI */
Display screen;

/** @brief Objet de gestion de l'écran tactile I2C */
TouchScreen touch;

/** @brief Gestionnaire de pages (State Machine) */
PageManager pageManager(&screen, &touch, NUM_PAGES);

// ========== Instances des pages ==========

/** @brief Instance de la page d'accueil */
HomePage homePage(&screen, &touch);

/** @brief Instance de la page de menu */
MenuPage menuPage(&screen, &touch);

/** @brief Instance de la page de paramètres */
SettingsPage settingsPage(&screen, &touch);

/** @brief Instance de la page de statut système */
StatusPage statusPage(&screen, &touch);

/**
 * @brief Fonction d'initialisation exécutée une seule fois au démarrage
 * 
 * Séquence d'initialisation:
 * 1. Démarrage de la communication série USB (115200 bauds)
 * 2. Initialisation de l'écran QSPI et configuration en mode paysage
 * 3. Initialisation du contrôleur tactile I2C
 * 4. Enregistrement de toutes les pages dans le PageManager
 * 5. Activation de la page d'accueil (HomePage)
 * 
 * En cas d'échec d'initialisation de l'écran ou du tactile,
 * le programme entre dans une boucle infinie avec messages d'erreur.
 * 
 * @note Cette fonction est appelée automatiquement par le framework Arduino
 */
void setup() {
  // ========== Initialisation du port série ==========
  Serial.begin(115200);
  
  // Attente connexion USB (maximum 3 secondes)
  // Permet de capturer les premiers messages sur le moniteur série
  unsigned long start = millis();
  while (!Serial && (millis() - start) < 3000) {
    delay(10);
  }
  
  Serial.println("\n=== ESP32-S3 C3248W535C - Système de Pages ===");
  Serial.printf("RAM libre: %d bytes\n", ESP.getFreeHeap());
  Serial.printf("PSRAM libre: %d bytes\n", ESP.getPsramSize());
  
  // ========== [1/3] Initialisation de l'écran ==========
  Serial.println("\n[1/3] Initialisation de l'écran...");
  if (!screen.begin()) {
    Serial.println("ERREUR: Échec initialisation écran!");
    while(1) delay(1000); // Boucle infinie en cas d'erreur
  }
  Serial.println("✓ Écran initialisé");
  
  // Configuration en mode paysage (480x320)
  screen.setRotation(1);
  Serial.printf("✓ Mode paysage: %dx%d\n", screen.getWidth(), screen.getHeight());
  
  // ========== [2/3] Initialisation du tactile ==========
  Serial.println("\n[2/3] Initialisation du tactile...");
  if (!touch.begin()) {
    Serial.println("ERREUR: Échec initialisation tactile!");
    while(1) delay(1000);
  }
  touch.setRotation(1); // Même rotation que l'écran
  Serial.println("✓ Tactile initialisé");
  
  // ========== [3/3] Enregistrement des pages ==========
  Serial.println("\n[3/3] Initialisation du gestionnaire de pages...");
  pageManager.registerPage(PAGE_HOME, &homePage);
  pageManager.registerPage(PAGE_MENU, &menuPage);
  pageManager.registerPage(PAGE_SETTINGS, &settingsPage);
  pageManager.registerPage(PAGE_STATUS, &statusPage);
  
  // Démarre sur la page d'accueil
  pageManager.setCurrentPage(PAGE_HOME);
  Serial.println("✓ Gestionnaire de pages initialisé");
  
  Serial.println("\n=== Initialisation terminée ===");
  Serial.println("Système de navigation activé!\n");
}

/**
 * @brief Boucle principale exécutée en continu après setup()
 * 
 * Le PageManager gère automatiquement:
 * - Mise à jour de la page active (update())
 * - Détection des touches (handleTouch())
 * - Affichage si nécessaire (draw())
 * - Navigation entre pages
 * 
 * Un délai de 10ms est ajouté pour:
 * - Réduire la charge CPU
 * - Éviter les lectures tactiles trop fréquentes
 * - Permettre au watchdog de se rafraîchir
 * 
 * @note Cette fonction est appelée en boucle infinie par le framework Arduino
 */
void loop() {
  // Le PageManager gère tout: affichage, tactile, navigation
  pageManager.update();
  
  // Délai pour ne pas surcharger le processeur
  delay(10);
}
