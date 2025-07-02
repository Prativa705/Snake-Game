
```markdown
# 🐍 Snake Game using SFML (C++)

A classic Snake game implemented in modern **C++** using the **SFML library**, featuring smooth gameplay, sound effects, increasing difficulty, and a retro-inspired UI.

---

## 🎮 Game Features

- ✅ Real-time snake movement with grid alignment
- 🍎 Random food placement with collision detection
- ⏱️ Increasing speed with every 3 points scored
- 💥 Game over on wall or self-collision
- 🔁 Restart game on `Enter` key after game over
- 🎧 Sound effects for eating and game over events
- 🎨 Clean visuals with score and high score display

---

## 📁 Project Structure

```

/SnakeGame/
├── source.cpp         # Main game logic
├── eat.wav            # Sound played when food is eaten
├── gameover.wav       # Sound played on collision/game over
├── arial.ttf          # Font used for score and text
├── screenshot.png     # Optional screenshot for README
└── README.md          # Project description and usage

````

---

## 🛠 Prerequisites

- C++17 or later
- [SFML 2.5+](https://www.sfml-dev.org/download.php)

Install SFML on Ubuntu:
```bash
sudo apt install libsfml-dev
````

---

## ⚙️ Build Instructions

### 🔹 On Linux/macOS:

```bash
g++ source.cpp -o SnakeGame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./SnakeGame
```

### 🔹 On Windows:

Ensure SFML is properly installed and linked.

Example using MinGW:

```bash
g++ source.cpp -o SnakeGame -IC:\SFML\include -LC:\SFML\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

---

## 🎮 Controls

| Key                | Action              |
| ------------------ | ------------------- |
| W / Up Arrow       | Move Up             |
| S / Down Arrow     | Move Down           |
| A / Left Arrow     | Move Left           |
| D / Right Arrow    | Move Right          |
| Enter              | Restart after death |
| Esc / Close Button | Quit the Game       |

---

## 📸 Screenshot

*(You can add a real screenshot of your game)*

![Snake Game Screenshot](screenshot.png)

---

## 🔊 Assets

Ensure the following files are in the executable's directory:

* `eat.wav` – Played when food is eaten
* `gameover.wav` – Played when snake dies
* `arial.ttf` – Font for all on-screen text

---

## 🚀 Future Ideas

* Add wall wrap mode (optional difficulty)
* Store high score persistently using a file
* Add pause functionality
* Replace colored blocks with sprite textures

---

## 🧑‍💻 Author

Developed  as a simple C++ game development project using [SFML](https://www.sfml-dev.org/).

---

## 📝 License

This project is open-source and free to use for learning or extension. Attribution is appreciated but not required.

````

---


