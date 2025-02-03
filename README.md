# ⚽ Balls Visualization (C++ & SFML 3.0.0)

A simple graphical project to visualize bouncing balls using **C++** and **SFML 3.0.0**. This project demonstrates basic 2D graphics rendering, animation, and event handling in SFML.

---

## 🚀 Features
- Smooth visualization of multiple bouncing balls
- Real-time event handling for interactions
- Cross-platform compatibility

---

## 🛠️ Setup and Installation

### **Prerequisites**
- Visual Studio 2022 or any IDE
- SFML 3.0.0 ([Download here](https://www.sfml-dev.org/download.php))

### **Steps to Set Up**
1. Clone this repository:
   ```bash
  git@github.com:iamM0hamed/Balls-Game.git
   
2. **Open the Project in Visual Studio**
   - Launch **Visual Studio 2022**.
   - Select **File > Open > Project/Solution** and navigate to your project directory.
   - Open the `BallsVisualization.sln` file (or create a new solution if prompted).

3. **Link the SFML 3.0.0 Library**
   To properly configure SFML, you'll need to link its headers and libraries.

   - **Include Directory:**
     Go to **Project > Properties** > **Configuration Properties > C/C++ > General** and add the following path to **Additional Include Directories**:
     ```plaintext
     C:\path\to\SFML-3.0.0\include
     ```

   - **Library Directory:**
     Go to **Project > Properties** > **Configuration Properties > Linker > General** and add the following path to **Additional Library Directories**:
     ```plaintext
     C:\path\to\SFML-3.0.0\lib
     ```

   - **Link SFML Libraries:**
     Go to **Project > Properties** > **Configuration Properties > Linker > Input** and add these libraries under **Additional Dependencies**:
     ```plaintext
     sfml-graphics.lib
     sfml-window.lib
     sfml-system.lib
     ```

   - If you are using **Debug mode**, link the debug versions of the libraries:
     ```plaintext
     sfml-graphics-d.lib
     sfml-window-d.lib
     sfml-system-d.lib
     ```

4. **Copy the SFML DLL Files**
   - Copy the `.dll` files from the `bin` directory of SFML (e.g., `sfml-graphics.dll`, `sfml-window.dll`, `sfml-system.dll`) to the output directory where your executable will be located (e.g., the `Debug` or `Release` folder).

5. **Build and Run the Project**
   - Build the project by selecting **Build > Build Solution** or pressing `Ctrl + Shift + B`.
   - To run the project, press `Ctrl + F5` or select **Debug > Start Without Debugging**.
     
6.**Do not forget to change the ISO to C++17 or heigher**
