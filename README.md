# 🏰 Internal Wesnot Hack by KeesOG 🎮

## 📝 Overview
Welcome to the Wesnoth Hack repository! This project features a dynamic link library (DLL) hack for the game **Battle for Wesnoth**, engineered to boost your gold value by injecting a custom codecave directly into the game's process. 🪄

## ✨ Features
- **💰 Dynamic Gold Modification:** Automatically set your gold to **420** by opening the terrain description in-game.
- **🛎️ Injection Notification:** Receive a message box notification upon successful DLL injection.
- **🧩 Inline Assembly:** Utilizes inline assembly for efficient and seamless integration into the game.

## ⚙️ Technical Details

### 🧠 Memory Address Resolution
1. **🗺️ Player Base Address Identification:**
   - The player's data base address is a constant pointer at `0x017EED18`, serving as the launch point for accessing player-specific memory data.

2. **🔗 Navigating Pointer Chains:**
   - From `player_base`, compute `game_base` by dereferencing `player_base` and adding `0xA90`.
   - Locate the player's gold value address by further dereferencing `game_base` and adding `0x4`.

### 🛠️ Codecave Implementation
1. **📌 Memory Hook:**
   - The DLL hooks into a specific location in the game's code at `0x00CCAF8A`. This hook redirects the game's execution flow to a codecave where custom code is executed.

2. **🧮 Address Calculation:**
   - Calculate the player base, game base, and gold addresses in memory using the pointer chains.

3. **🏅 Gold Modification:**
   - Within the codecave, set the player's gold amount to **420** whenever the terrain description is opened in-game.

4. **🔄 Execution Redirection:**
   - Restore the game's original instructions and redirect execution back to the game's original flow at address `0x00CCAF90`.

### 🔐 Memory Management and Protection
1. **🛡️ Memory Protection:**
   - Change the memory protection of the hook location to allow code execution modification using `VirtualProtect`.

2. **🔧 Hook Installation:**
   - Write a jump instruction at the hook location to redirect execution to the codecave. This involves:
     - ✍️ Writing the JMP opcode (`0xE9`).
     - 📏 Calculating and writing the relative address for the jump.
     - 🔄 Adding a NOP instruction (`0x90`) to align the code.

3. **🧵 Thread Injection and Monitoring:**
   - Upon DLL load, the DLL creates a new thread to monitor and manage the in-game actions. This thread ensures the hack remains active and responsive.

4. **🛡️ Memory Safety:**
   - Ensure memory integrity by restoring the original protection settings after modifying the hook location. This prevents other processes from inadvertently writing to or corrupting the game memory.

## 🚀 Installation
1. **🔧 Compile the DLL:**
   - Use a C++ compiler to compile the source code into a DLL file.
2. **🔗 Inject the DLL:**
   - Utilize a DLL injector to inject the compiled DLL into the Battle for Wesnoth process.
3. **✨ Activate the Hack:**
   - Open the terrain description in-game to set your gold to **420**.

## ⚠️ Disclaimer
Use this hack at your own risk. Modifying game memory can lead to unpredictable behavior and may violate the game's terms of service. Always back up your game data before using hacks or modifications.

## 📜 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
