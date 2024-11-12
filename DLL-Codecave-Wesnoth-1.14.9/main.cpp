/*
 * ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 * ┃                                                                              ┃
 * ┃                               🎮 CODE OVERVIEW 🎮                            ┃
 * ┃                                                                              ┃
 * ┃ Author: KeesOG                                                               ┃
 * ┃                                                                              ┃
 * ┃ This C++ code demonstrates a method to hook into a game's memory and         ┃
 * ┃ manipulate certain values. The code primarily injects a DLL into a game,     ┃
 * ┃ reads a specific in-game value (enemy gold), and modifies a section of the   ┃
 * ┃ game code to display this value.                                             ┃
 * ┃                                                                              ┃
 * ┃                           ,MMM8&&&.                                          ┃
 * ┃                      _...MMMMM88&&&&..._                                     ┃
 * ┃                   .::'''MMMMM88&&&&&&'''::.                                  ┃
 * ┃                  ::     MMMMM88&&&&&&     ::                                 ┃
 * ┃                  '::....MMMMM88&&&&&&....::'                                 ┃
 * ┃                     `''''MMMMM88&&&&''''`                                    ┃
 * ┃                           'MMM8&&&'                                          ┃
 * ┃                                                                              ┃
 * ┃ Key Components:                                                              ┃
 * ┃ - Memory pointers to important locations within the game                    ┃
 * ┃ - A code cave to execute custom assembly instructions                        ┃
 * ┃ - Mechanisms for modifying memory protections and inserting hooks            ┃
 * ┃                                                                              ┃
 * ┃ Detailed Process:                                                            ┃
 * ┃ 1. Hooking the Assembly Call: The code hooks into the assembly call          ┃
 * ┃    function responsible for printing strings in the game, such as those      ┃
 * ┃    displayed in the terrain description box.                                 ┃
 * ┃ 2. Retrieving Enemy Gold: The enemy gold value is fetched using a pointer    ┃
 * ┃    chain that navigates through specific memory addresses.                   ┃
 * ┃ 3. Editing the String: Before the string is printed, the first three bytes   ┃
 * ┃    of the string are modified to display the enemy gold value. This is done  ┃
 * ┃    by converting the gold value to a string and inserting it into the        ┃
 * ┃    memory location where the string is stored.                               ┃
 * ┃ 4. Restoring Original Functionality: After modifying the string, the         ┃
 * ┃    original function is called, and the program execution returns to its     ┃
 * ┃    normal flow.                                                              ┃
 * ┃                                                                              ┃
 * ┃ This method is commonly used in game hacking to alter game behavior for      ┃
 * ┃ testing or other purposes, allowing dynamic modification of in-game values.  ┃
 * ┃                                                                              ┃
 * ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 */

#include <windows.h>
#include <stdio.h>

 // Pointers to various memory locations in the game
DWORD* player_base;
DWORD* game_base;
DWORD* enemy_gold;
DWORD old_protect; // Old protection setting for memory page

// Location to hook the game code
unsigned char* hook_location = (unsigned char*)0x005ED129;

// Buffer to store enemy gold value as a string
char gold_byte_array[4] = { 0 };

// Addresses for the original function call and return address
DWORD original_call_address = 0x005E9630;
DWORD ret_address = 0x005ED12E;

// Assembly code to create a code cave
__declspec(naked) void codecave() {
    __asm {
        pushad  // Save all general-purpose registers
    }

    // Read the enemy gold value using pointer chain
    player_base = (DWORD*)0x17EED18;
    game_base = (DWORD*)(*player_base + 0xA90);
    enemy_gold = (DWORD*)(*game_base + (0x274));

    // Convert the enemy gold value to a string
    sprintf_s(gold_byte_array, 4, "%d", *enemy_gold);

    __asm {
        popad  // Restore all general-purpose registers
        pushad  // Save all general-purpose registers again

        // Modify the string in memory to display enemy gold
        mov eax, dword ptr ds : [edx]
        mov bl, gold_byte_array[0]
        mov byte ptr ds : [eax] , bl
        mov bl, gold_byte_array[1]
        mov byte ptr ds : [eax + 1] , bl
        mov bl, gold_byte_array[2]
        mov byte ptr ds : [eax + 2] , bl

        popad  // Restore all general-purpose registers

        // Call the original function
        call original_call_address

        // Jump back to the original code
        jmp ret_address
    }
}

// Entry point for the DLL
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        // Notify that the DLL has been injected
        MessageBox(NULL, L"DLL injected into game!", L"mHACKeroni by KeesOG", MB_OK | MB_ICONINFORMATION);

        // Change the protection of the memory page to allow writing
        VirtualProtect((void*)hook_location, 6, PAGE_EXECUTE_READWRITE, &old_protect);

        // Insert a jump to our codecave function
        *hook_location = 0xE9;
        *(DWORD*)(hook_location + 1) = (DWORD)&codecave - ((DWORD)hook_location + 5);
    }
    return TRUE;
}
