# Game Memory Manipulation with DLL Injection

**Author: KeesOG**

## 🎮 Overview
Ready to dive into the exhilarating world of game hacking? This project is all about tapping into a game's memory and tweaking in-game values for fun and learning. By injecting a DLL, you can reveal the enemy's gold value right in the game. We'll journey through memory pointers, carve out our secret code cave, and change memory protections. Let’s uncover the magic behind the scenes!

---

## Key Components

### 🔑 Memory Pointers
Think of these as coordinates on a treasure map, leading us to specific spots in the game's memory. We'll use pointers like `player_base`, `game_base`, and `enemy_gold` to locate and change the data we want.

### 🕳 Code Cave
This is our secret hideout in the game’s memory—a safe spot where we can insert our custom code without messing up the game's normal operations.

### 🔒 Memory Protection
The game's memory is usually guarded to block unauthorized changes. We’ll use some clever techniques to temporarily lift these protections, letting us make the modifications we need.

---

## 📜 Detailed Process

### 🛠 DLL Injection

- **Initialization:** When our DLL is injected, it begins by setting up the environment. This includes tweaking the memory protection settings at a specific spot so we can write our instructions there.

### 🔌 Hooking the Assembly Call

- **Inserting the Jump:** At a key point in the game’s code, we insert a jump instruction. This redirects the game’s execution to our custom code cave.
- **Why Assembly?:** Assembly language lets us directly interact with the CPU's registers and instructions, giving us precise control over the game’s behavior.

### 🏴‍☠️ Retrieving Enemy Gold

- **Pointer Navigation:** We follow a series of pointers to find the enemy gold value, like following breadcrumbs through the game's memory.

### ✍️ Modifying the String

- **Conversion:** We convert the enemy gold value into a string format.
- **Inserting the String:** Our custom code updates the game's memory to display this gold value, by directly manipulating the CPU's registers and memory addresses within our code cave.

### 🧩 Understanding the Registers

- **Pushad and Popad:** These instructions save and restore all general-purpose registers, ensuring our changes don’t interfere with the game’s normal operations.
- **Registers in Action:** By moving the converted gold value into specific registers, we can update the game's display string. For example, using the `eax` register to point to the string location and `bl` to hold each byte of the gold value.

### 🔄 Restoring Original Functionality

- **Calling the Original Function:** After tweaking the string, we call the original function to keep the game running smoothly.
- **Returning to Normal:** Finally, we jump back to the original return address, letting the game continue as normal.

---

## 🚀 Usage

1. **Compile the DLL:** Set up your development environment and compile the provided C++ code into a DLL.
2. **Inject the DLL:** Use a DLL injector tool to inject your compiled DLL into the game’s process.
3. **Observe the Magic:** Once injected, watch as the enemy gold value is displayed in-game, right where you wanted it!

---

## ⚠️ Disclaimer
This code is for educational purposes only. Using it in online games without authorization can violate terms of service and lead to consequences. Always use this knowledge responsibly and ethically.

---

## 📄 License
MIT License
