# Infinity Stamina for Gnomium

![Version](https://img.shields.io/badge/version-1.0-blue)
![Platform](https://img.shields.io/badge/platform-Windows-lightgrey)
![Language](https://img.shields.io/badge/language-C%2B%2B-green)

A simple cheat tool for the game Gnomium that sets infinite stamina.

---

## English Version

### About The Project

This is my first experience in creating game cheats. Here I practiced with:
- Windows process management (OpenProcess, Read/WriteProcessMemory)
- Module base address searching via Toolhelp32Snapshot
- DMA (Direct Memory Access) for working with multi-level pointers
- Dynamic address calculation through offset chains

The code might not be optimal, but it works and helped me understand the basics of process memory manipulation.

### How It Works

1. The program finds the "Gnomium" game window
2. Retrieves the process PID and opens it with full access
3. Locates the base address of UnityPlayer.dll module
4. Using an offset chain, calculates the exact memory address where stamina value is stored
5. In an infinite loop, overwrites this value to 100

### Usage

1. Launch the Gnomium game
2. Enter the actual gameplay (not the menu)
3. Run the cheat
4. Stamina will be fixed at 100 units

### Technical Details

| Parameter | Value |
|-----------|-------|
| Base Address | UnityPlayer.dll + 0x1F31A18 |
| Offset Chain | [0x90, 0x68, 0x8, 0x4F0, 0x78, 0x350] |
| Stamina Type | float (4 bytes) |

### Note

This project was created for educational purposes to learn about Windows process memory manipulation.

---

## Русская версия

### О проекте

Это мой первый опыт в создании читов для игр. Здесь я практиковался в:
- Работе с процессами Windows (OpenProcess, Read/WriteProcessMemory)
- Поиске базовых адресов модулей через Toolhelp32Snapshot
- Использовании DMA (Direct Memory Access) для работы с многоуровневыми указателями
- Вычислении динамических адресов через цепочки оффсетов

Код может быть не самым оптимальным, но он работает и помог мне разобраться в основах работы с памятью процессов.

### Как это работает

1. Программа находит окно игры Gnomium
2. Получает PID процесса и открывает его с полным доступом
3. Находит базовый адрес модуля UnityPlayer.dll
4. Используя цепочку оффсетов, вычисляет точный адрес в памяти, где хранится значение стамины
5. В бесконечном цикле перезаписывает это значение на 100

### Использование

1. Запустите игру Gnomium
2. Зайдите непосредственно в игровой процесс (не в меню)
3. Запустите чит
4. Стамина автоматически зафиксируется на 100 единицах

### Технические детали

| Параметр | Значение |
|----------|----------|
| Базовый адрес | UnityPlayer.dll + 0x1F31A18 |
| Цепочка оффсетов | [0x90, 0x68, 0x8, 0x4F0, 0x78, 0x350] |
| Тип данных стамины | float (4 байта) |

### Примечание

Проект создан в образовательных целях для изучения работы с памятью процессов Windows.

---

## Building from Source

```bash
# Compile with any C++ compiler (MSVC, MinGW, etc.)
g++ main.cpp -o InfinityStamina.exe