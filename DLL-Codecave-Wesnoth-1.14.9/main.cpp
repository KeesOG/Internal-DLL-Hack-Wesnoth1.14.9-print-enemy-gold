/*
 * ----------------------------------------------------------------------------
 * "Wesnot 1.14.9 Internal DLL hack by KeesOG"
 * ----------------------------------------------------------------------------
 * Description:
 * This dynamic-link library (DLL) demonstrates a simple game hack that modifies
 * the player's gold amount in a game upon injecting the DLL. It alters the game
 * memory to set the gold value to 420 whenever a specific in-game action
 * (opening terrain description) occurs.
 *
 * Features:
 * - Dynamic memory manipulation
 * - Message box notification upon successful injection
 * - Inline assembly for codecave implementation
 *
 * Instructions:
 * - Inject this DLL into the target game process.
 * - Open the terrain description in-game to see the gold value change.
 * ----------------------------------------------------------------------------
         ,MMM8&&&.
    _...MMMMM88&&&&..._
 .::'''MMMMM88&&&&&&'''::.
::     MMMMM88&&&&&&     ::
'::....MMMMM88&&&&&&....::'
   `''''MMMMM88&&&&''''`
         'MMM8&&&'

 */

#include <windows.h> // Include Windows header for WinAPI functions

DWORD* player_base;    // Pointer to player base address
DWORD* game_base;      // Pointer to game base address
DWORD* gold;           // Pointer to gold amount
DWORD old_protect;     // Variable to store old memory protection settings

// Location of the hook in the code to redirect execution to codecave
unsigned char* hook_location = (unsigned char*)0x00CCAF8A;
DWORD ret_adress = 0x00CCAF90; // Return address after executing the codecave

// Naked function for the codecave, no function prolog/epilog
__declspec(naked) void codecave() {
    __asm {
        pushad // Save all general-purpose registers
    }

    player_base = (DWORD*)0x17EED18; // Calculate the player base address
    game_base = (DWORD*)(*player_base + 0xA90); // Calculate the game base address
    gold = (DWORD*)(*game_base + 0x4); // Calculate the gold address
    *gold = 420; // Set gold amount to 420

    __asm {
        popad // Restore all general-purpose registers
        mov eax, dword ptr ds : [ecx] // Original instruction from the hooked location
        lea esi, ds : [esi]           // Original instruction from the hooked location
        jmp ret_adress                // Jump back to the original return address
    }
}

// Entry point for the DLL
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) { // When the DLL is attached to the process
        // Display a message box to indicate successful DLL injection
        MessageBox(NULL, L"DLL injected into game! Open terrain description for 420 gold!", L"mHACKeroni by KeesOG", MB_OK | MB_ICONINFORMATION);

        // Change memory protection to allow code execution modification
        VirtualProtect((void*)hook_location, 6, PAGE_EXECUTE_READWRITE, &old_protect);

        // Write the jump instruction to the hook location to redirect execution to codecave
        *hook_location = 0xE9; // JMP instruction opcode
        *(DWORD*)(hook_location + 1) = (DWORD)&codecave - ((DWORD)hook_location + 5); // Calculate relative address for the jump
        *(hook_location + 5) = 0x90; // NOP instruction (No Operation)
    }
    return TRUE; // Indicate successful initialization
}
