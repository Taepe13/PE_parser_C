#include "pe-parser.h"
void PrintSectionFlags(DWORD characteristics) {
    printf("%s%s%s",
        (characteristics & IMAGE_SCN_MEM_READ)    ? "R" : "-",
        (characteristics & IMAGE_SCN_MEM_WRITE)   ? "W" : "-",
        (characteristics & IMAGE_SCN_MEM_EXECUTE) ? "X" : "-");
}
void PrintSections(PIMAGE_NT_HEADERS pNt)
{
    PIMAGE_SECTION_HEADER pSec = IMAGE_FIRST_SECTION(pNt);
    printf("\n   --Sections------------------------\n");
    printf("   # Name       VA          VS          Raw         Char        Flags\n");
    printf("   - ---------- ----------  ----------  ----------  ----------  ---\n");

    for (int i =0; i < pNt->FileHeader.NumberOfSections; i++)
    {
        printf("   %d  %-8s  0x%08X  0x%08X  0x%08X  0x%08X  ", 
        i,                            // %d
        pSec[i].Name,                 // %-8s
        pSec[i].VirtualAddress,       // 0x%08X
        pSec[i].Misc.VirtualSize,     // 0x%08X
        pSec[i].PointerToRawData,     // 0x%08X
        pSec[i].Characteristics);     // 0x%08X
        PrintSectionFlags(pSec[i].Characteristics);
        printf("\n");
    }
    
}