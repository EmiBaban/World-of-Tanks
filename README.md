# 🕹️ World of Tanks – 3D Graphics Project

## 📌 Description
A **3D tank simulation game** inspired by *World of Tanks*, developed as part of the **Computer Graphics Course**.

The project leverages a custom graphics framework (engine + utilities) provided by the course instructors.  
**My primary contributions are in [`src/lab_m1/Tema2`](src/lab_m1/Tema2):** here I implemented the core game logic, real-time rendering, user controls, and interactive mechanics.

---

## 🛠️ Tech Stack
- **C++**
- **OpenGL**
- **EGC Framework** (educational engine based on GLFW, GLM, stb, Assimp)
- **CMake** & **Visual Studio**

---

## ✨ Features
- 🚜 **Custom-built tank model** using 3D primitive shapes  
- 🎮 **Player controls**:  
  - Movement with **WASD**  
  - Independent **turret rotation**  
  - Projectile **shooting & lifetime management**  
- 💥 **Collisions & interactions**:  
  - Projectile ↔ enemy tanks  
  - Tank ↔ tank  
  - Tank ↔ buildings  
- 🤖 **Enemy AI**:  
  - Movement on predefined or random trajectories  
  - Attack behavior against the player  
- 🏢 **3D environment** with obstacles and destructible objects  
- ❤️ **Health & damage system with visual feedback**:  
  - Tank deformation in **vertex shader** based on HP  
  - Dynamic **color change** in **fragment shader**  
- 🕹️ **Gameplay loop** with active enemies, damage, and win/lose conditions  

---

## 📷 Screenshots

![MyWorlOfTanks](https://github.com/user-attachments/assets/07d238fb-7d07-447a-b74a-d4a4b377715b)

---

## 🚀 How to Run
1. **Install prerequisites:**  
   - Latest C++ compiler (Visual Studio recommended)  
   - Graphics drivers supporting OpenGL 3.3+
2. **Clone the repository**
3. **Build using CMake:**  
   - `mkdir build && cd build`  
   - `cmake ..`  
   - `cmake --build .`
4. **Run the executable:**  
   - Windows: `.\bin\Debug\GFXFramework.exe`  
   - Linux/macOS: `./bin/Debug/GFXFramework`

---

## 🏗️ Project Structure
- `src/lab_m1/Tema2` – **Main game implementation**
- `src/framework` – Core engine code (provided)
- `docs` – Documentation and usage instructions
