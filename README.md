# Game Memory Manipulation with DLL Injection

**Author: KeesOG**

## 🎮 Overview
This project involves creating a stathack for the game Wesnoth 1.14.9, which displays the second player's gold value by injecting a DLL. We will explore memory pointers, establish a code cave, and modify memory protections to intercept the game's string printing function and display custom values.

---

## Key Components

### 🔑 Memory Pointers
Memory pointers act as coordinates in the game's memory, helping us locate specific data. In this project, we use pointers like `player_base`, `game_base`, and `enemy_gold` to find the second player's gold value.

### 🕳 Code Cave
A code cave is a reserved space in the game's memory where we can insert our custom assembly instructions without disrupting normal game operations.

### 🔒 Memory Protection
We will temporarily modify memory protection settings to allow writing to normally protected memory areas, enabling us to insert and execute custom code.

---

## 📜 Detailed Process

### 🛠 DLL Injection

- **Initialization:** The DLL sets up the environment upon injection by modifying memory protection settings, allowing us to write custom instructions.

### 🔌 Hooking the Assembly Call

- **Inserting the Jump:** A jump instruction is inserted at a critical point in the game’s code to redirect execution to our custom code cave.
- **Why Assembly?:** Assembly language allows direct interaction with the CPU's registers and instructions, providing precise control over the game's behavior.

### 🏴‍☠️ Retrieving Enemy Gold

- **Pointer Navigation:** We navigate through memory pointers to locate the second player's gold value, similar to following breadcrumbs.

### ✍️ Modifying the String

- **Conversion:** Convert the gold value into a string format.
- **Inserting the String:** Update the game's memory to display the gold value by manipulating the CPU's registers and memory addresses within the code cave.

### 🧩 Understanding the Registers

- **Pushad and Popad:** These instructions save and restore general-purpose registers, ensuring our changes do not interfere with the game's normal operations.
- **Registers in Action:** By moving the converted gold value into specific registers, we can update the game's display string. For example, using the `eax` register to point to the string location and `bl` to hold each byte of the gold value.

### 🔄 Restoring Original Functionality

- **Calling the Original Function:** After modifying the string, the original function is called to maintain normal game operation.
- **Returning to Normal:** Finally, we jump back to the original return address, allowing the game to continue as usual.

---

## 🚀 Usage

1. **Compile the DLL:** Set up your development environment and compile the provided C++ code into a DLL.
2. **Inject the DLL:** Use a DLL injector tool to inject your compiled DLL into the game’s process.
3. **Observe the Magic:** Once injected, watch as the second player's gold value is displayed in-game.

---

## ⚠️ Disclaimer
This code is for educational purposes only. Using it in online games without authorization can violate terms of service and lead to consequences. Always use this knowledge responsibly and ethically.

---

## 📄 License
MIT License
