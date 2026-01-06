# VL53L0X Library for Raspberry Pi Pico (Pico SDK)

A high-performance C++ static library for the VL53L0X Time-of-Flight (ToF) distance sensor. This version is a specialized port designed specifically for the **Raspberry Pi Pico (RP2040/RP2350)** using the native **Pico SDK**, providing a lean alternative to Arduino-based drivers.

## 📜 Lineage & Credits
This library is the result of a collaborative open-source chain. By using this fork, you benefit from the work of:
1. **Pololu Corporation**: The original Arduino library structure.
2. **Larry Bank (bitbank2)**: Simplification and port to Linux systems.
3. **Daniel Perron (danjperron)**: Basic integration with the Pico SDK.
4. **Michał Sadecki (sadeckiM), Maksymilian Książka (maxksiazka)**: Ported to the Raspberry Pi Pico SDK, refactored as a static library, and integrated with `hardware_i2c`.

## ⚖️ License
This project is licensed under the **GNU General Public License v3.0 (GPLv3)**. 

Because this fork is derived from code licensed under the GPLv3 by Larry Bank, the license remains "reciprocal." You are free to use and modify this code, but any distributions of the software must also be licensed under the GPLv3. 

**Note:** The underlying STMicroelectronics API constants and low-level communication logic remain subject to their original BSD-style notice (see `LICENSE` file for full details).

---

## 🛠 Integration (Pico SDK & CMake)

This library is intended to be used as a **linked static library** in your Pico project.

### 1. Project Structure
Place this library into your project's library directory:
```text
my_project/
├── lib/
│   └── libVL53L0X_pico/     <-- This library
├── CMakeLists.txt
└── main.c
```
### 2. Top level CMakeLists.txt
Add the following to your top-level `CMakeLists.txt`:
```cmake
add_subdirectory(lib)
target_link_libraries(<EXECUTABLE_NAME> PRIVATE libVL53L0X_pico)
```
