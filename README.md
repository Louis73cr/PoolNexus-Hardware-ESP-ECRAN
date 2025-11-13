# PoolNexus Hardware Screen 480x320 (C3248W535C)

[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](https://louis73cr.github.io/PoolNexus-Hardware-ESP-ECRAN/html/)
[![PlatformIO](https://img.shields.io/badge/PlatformIO-ESP32--S3-orange.svg)](https://platformio.org/)
[![Framework](https://img.shields.io/badge/Framework-Arduino-00979D.svg)](https://www.arduino.cc/)


## 📖 Documentation

La documentation complète du code est générée avec **Doxygen** et disponible en ligne :

🔗 **[Documentation Doxygen](https://louis73cr.github.io/PoolNexus-Hardware-ESP-ECRAN/html/)**

## 🚀 À propos

Projet de contrôle d'écran tactile 480x320 pour PoolNexus basé sur ESP32-S3.

## 🛠️ Hardware

- **Board**: ESP32-S3-DevKitC-1
- **Screen**: C3248W535C (480x320)
- **MCU**: ESP32-S3 @ 240MHz
- **Memory**: PSRAM OPI

## 📦 Dépendances

- GFX Library for Arduino (1.6.0)

## 🔧 Compilation

Ce projet utilise PlatformIO. Pour compiler :

```bash
platformio run
```

Pour uploader sur la carte :

```bash
platformio run --target upload
```

---

**PoolNexus** - Système de contrôle intelligent pour piscine
