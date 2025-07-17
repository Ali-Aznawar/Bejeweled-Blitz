# 💎 Bejeweled Blitz – C++ & SFML

A fast-paced, match-3 puzzle game inspired by the classic **Bejeweled Blitz**, developed using **C++** and **SFML (Simple and Fast Multimedia Library)**.

---

## 🚀 Features

- 🔢 **Classic Match-3 Mechanics** – Swap adjacent gems to match 3 or more of the same kind.
- ⏱️ **Timed Blitz Mode** – Score as high as you can before the clock runs out!
- 💥 **Chain Reactions** – Matching gems can cause cascading combos.
- 🎮 **Smooth Animations** – Made possible by SFML's sprite rendering and timing.
- 🔊 **Sound Effects** – Optional: integrated with SFML Audio for match/combo feedback.

---

## 🛠️ Built With

- **C++17**
- **[SFML](https://www.sfml-dev.org/)** (Graphics, Window, System, and optionally Audio)
- Optional: **CMake** for cross-platform build management

---

## 🧰 Requirements

- C++ compiler supporting C++17 (GCC, Clang, MSVC)
- SFML 2.5+
- CMake (optional)

---

## 🧱 How to Build

### 🔹 On Linux/macOS

```bash
git clone https://github.com/your-username/bejeweled-blitz-cpp.git
cd bejeweled-blitz-cpp

# If using CMake
mkdir build && cd build
cmake ..
make

# Or if manually compiling
g++ -std=c++17 -I/path/to/SFML/include -L/path/to/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -o bejeweled main.cpp

