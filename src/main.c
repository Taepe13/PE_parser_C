#include "pe-parser.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <path_to_exe>\n", argv[0]);
        return 1;
    }

    HANDLE hFile = CreateFileA(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("CreateFileA failed: \n%d\n", GetLastError());
        return 1;
    }

    DWORD fSize = GetFileSize(hFile, NULL);
    PBYTE pBuffer = (PBYTE)HeapAlloc(GetProcessHeap(), 0, fSize);
    DWORD bytesRead = 0;
    ReadFile(hFile, (LPVOID)pBuffer, fSize, &bytesRead, NULL);
    CloseHandle(hFile);

    PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)pBuffer;
    if (pDos->e_magic != IMAGE_DOS_SIGNATURE)
    {
        printf("Not a valid DOS Header\n");
        return 1;
    }
    printf("  ***************************************************\n\n");
    printf("  |Reading a file|\n  Name:  %s\n\n", argv[1]);
    printf("  ***************************************************\n");
    printf("  --------DOS HEADER--------------------------\n");
    printf("  DOS magic:              0x%X\n", pDos->e_magic);
    printf("  e_lfanew:               0x%X\n\n", pDos->e_lfanew);
    
    PIMAGE_NT_HEADERS pNt = (PIMAGE_NT_HEADERS)(pBuffer + pDos->e_lfanew);
    if(pNt->Signature != IMAGE_NT_SIGNATURE)
    {
        printf("Not a valid Portable Executable");
        return 1;
    }

    printf("  --------NT HEADER--------------------------\n");
    printf("  SIGNATURE:              0x%X  (MZ)\n", pNt->Signature);
    printf("  Machine:                0x%X  (%s)\n", pNt->FileHeader.Machine, GetMachineType(pNt->FileHeader.Machine));
    printf("  SizeOfOptionalHeader:   0x%X\n", pNt->FileHeader.SizeOfOptionalHeader);
    printf("  TimeDateStamp:          0x%X\n", pNt->FileHeader.TimeDateStamp);
    printf("  Characteristics:        0x%X    (", pNt->FileHeader.Characteristics);
    PrintFileCharacteristics(pNt->FileHeader.Characteristics);
    printf(")\n");
    printf("  NumberOfSections:       0x%X\n\n", pNt->FileHeader.NumberOfSections);
 
    printf("  --------OPTIONAL HEADER--------------------\n");
    printf("  Magic:                  0x%X  (%s)\n", pNt->OptionalHeader.Magic, GetOptionalMagic(pNt->OptionalHeader.Magic));
    printf("  AddressOfEntryPoint     0x%X\n", pNt->OptionalHeader.AddressOfEntryPoint);
    printf("  ImageBase:              0x%8X\n", (unsigned int)pNt->OptionalHeader.ImageBase);
    printf("  SizeOfImage:            0x%X\n", pNt->OptionalHeader.SizeOfImage);
    printf("  Subsystem:              0x%X    (%s)\n", pNt->OptionalHeader.Subsystem, GetSubsystem(pNt->OptionalHeader.Subsystem));
    printf("  DllCharacteristics:     ", pNt->OptionalHeader.DllCharacteristics);
    PrintDllCharacteristics(pNt->OptionalHeader.DllCharacteristics);
    printf(")\n");
    PrintSections(pNt);
    PrintImports(pBuffer, pNt);
    HeapFree(GetProcessHeap(), 0, pBuffer);
    return 0;
}
