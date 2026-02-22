#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <conio.h>

using namespace std;

HWND hwnd;
DWORD pID;
HANDLE hProcess;
uintptr_t gameModule;

float stamina = 100;

uintptr_t GetModuleBaseAddress(const char* modName) {
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pID);

    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);

        if (Module32First(hSnap, &modEntry)) {
            do {
                if (!_stricmp(modEntry.szModule, modName)) {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }

    CloseHandle(hSnap);
    return modBaseAddr;
}

uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets) {
    uintptr_t addr = ptr;

    for (unsigned int i = 0; i < offsets.size(); ++i) {
        ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
        addr += offsets[i];
    }

    return addr;
}

void InfinityStamina() {
    gameModule = (uintptr_t)GetModuleBaseAddress("UnityPlayer.dll");
    uintptr_t staminaAddr = gameModule + 0x1F31A18;

    std::vector<unsigned int> staminaOffset = { 0x90, 0x68, 0x8, 0x4F0, 0x78, 0x350 };
    uintptr_t staminaBaseAddr = FindDMAAddy(hProcess, staminaAddr, staminaOffset);

    WriteProcessMemory(hProcess, (LPVOID)staminaBaseAddr, &stamina, sizeof(stamina), 0);
}

int main() {
    setlocale(LC_ALL, "Russian");

    SetConsoleTitle("Infinity Stamina (Gnomium | by elyrin)");

    hwnd = FindWindow(0, "Gnomium");

    if (hwnd == NULL) {
        cout << "[-] | Игра не запущена!" << endl;
        system("pause");
        return 0;
    }

    GetWindowThreadProcessId(hwnd, &pID);
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pID);

    cout << "[+] | Игра запущена! Если ты до сих пор в меню - заходи в игру чтобы подгрузить стамину!" << endl;
    cout << "[+] | Поменял значение стамины на " << stamina << " единиц!" << endl;

    while (true) {
        InfinityStamina();
    }
}