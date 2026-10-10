#pragma once
#include <stdio.h>
#include <Windows.h>


// utils
const char* GetMachineType(WORD machine);
const char* GetOptionalMagic(WORD magic);
const char* GetSubsystem(WORD subsystem);
DWORD RvaToOffset(PIMAGE_NT_HEADERS pNt, DWORD rva);


// Characteristics

void PrintFileCharacteristics(WORD characteristics);
void PrintDllCharacteristics(WORD characteristics);

// Sections
void PrintSectionFlags(DWORD characteristics);
void PrintSection(PIMAGE_NT_HEADERS pNt);

// Imports
void PrintImports(PBYTE pBuffer, PIMAGE_NT_HEADERS pNt);
