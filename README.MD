# PE Parser (C)

A lightweight Portable Executable (PE) parser written in pure C with WinAPI. Built for malware analysis and offensive security research.


## Features

- **DOS Header**            - MZ signature, e_lfanew
- **NT Headers**            - Signature, FileHeader, OptionalHeader
- **Optional Header**       - Magic, EntryPoint, ImageBase, Subsystem, DllCharacteristics
- **Sections**              - Name, VA, VS, Raw, Characteristics(R|W|X flags)
- **Import Table**          - DLLs + imported functions(with ordinal support)
- **Human-readable output** - flag decoding(EXECUTABLE_IMAGE, ASLR, DEP, CFG and etc)
- **x86 / x64**             - auto-detection of architecture


## The goal

Understanding PE format is fundamental for
- Malware analysis (identifying suspicious imports)
- Offensive security (IAT hiding, API hashing, manual mapping)
- Reverse engineering(PE structure, sections, entry points)

This intentionally simple and readable parser without any external dependencies except WinAPI is part of my MalDev learning path

## Build

### Requirements

- Windows 10/11
- MSVC (Visual Studio Build tools 2022)

### Compile

```cmd
cl src\*.c \Fe:pe_parser.exe \Zi \EHsc

## Usage
```pe_parser.exe <path_to_exe>


## Example
pe.parser.exe C:\Windows\System32.notepad.exe

Project Structure

    pe-parser-c/
    ├── src/
    │   ├── pe_parser.h        # Headers, structures, prototypes
    │   ├── utils.c            # RvaToOffset, machine/subsystem decoding
    │   ├── characteristics.c  # FileCharacteristics, DllCharacteristics
    │   ├── sections.c         # Section parsing + R/W/X flags
    │   ├── imports.c          # Import table parsing
    │   └── main.c             # CLI entry point
    ├── .vscode/
    │   └── tasks.json         # Build task
    ├── .gitignore
    └── README.md

## Author
    Taepe13 - Offensive Security engineer.
*   Github: @Taeper13
