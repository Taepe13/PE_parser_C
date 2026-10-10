#include "pe-parser.h"
const char* GetMachineType(WORD machine) {
    switch (machine) {
        case 0x014C: return "x86 (i386)";
        case 0x8664: return "x64 (AMD64)";
        case 0x01C0: return "ARM";
        case 0xAA64: return "ARM64";
        case 0x0200: return "IA64 (Itanium)";
        default:     return "Unknown";
    }
}
const char* GetOptionalMagic(WORD magic) {
    switch (magic) {
        case 0x010B: return "PE32 (x86)";
        case 0x020B: return "PE32+ (x64)";
        case 0x0107: return "ROM";
        default:     return "Unknown";
    }
}

const char* GetSubsystem(WORD subsystem) {
    switch (subsystem) {
        case 0:  return "Unknown";
        case 1:  return "Native";
        case 2:  return "Windows GUI";
        case 3:  return "Windows Console";
        case 7:  return "POSIX Console";
        case 9:  return "Windows CE GUI";
        case 10: return "EFI Application";
        case 14: return "Xbox";
        case 16: return "Windows Boot";
        default: return "Unknown";
    }
}
DWORD RvaToOffset(PIMAGE_NT_HEADERS pNt, DWORD rva)
{
    PIMAGE_SECTION_HEADER pSec = IMAGE_FIRST_SECTION(pNt);

    for(int i = 0; i < pNt->FileHeader.NumberOfSections; i++)
    {
        if (rva >= pSec[i].VirtualAddress && rva < pSec[i].VirtualAddress + pSec[i].Misc.VirtualSize) {
            return pSec[i].PointerToRawData + (rva - pSec[i].VirtualAddress);
        }

    }
    return rva;
}