#include <pe-parser.h>
void PrintImports(PBYTE pBuffer, PIMAGE_NT_HEADERS pNt)
{
    DWORD importRva = pNt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
    if (importRva == 0)
    {
        printf("\n--Import ---------------------------\n");
        printf("    none\n");
        return;
    }

    PIMAGE_IMPORT_DESCRIPTOR pImport = (PIMAGE_IMPORT_DESCRIPTOR)(pBuffer + RvaToOffset(pNt, importRva));

    printf("\n--Import ---------------------------\n");
    
    while (pImport->Name != 0)
    {
        char* dllName = (char*)(pBuffer + RvaToOffset(pNt, pImport->Name));
        printf("    %s\n", dllName);

        PIMAGE_THUNK_DATA64 pThunk = (PIMAGE_THUNK_DATA64)
        (
            pBuffer + RvaToOffset(pNt, pImport->OriginalFirstThunk)
        );

        while(pThunk->u1.AddressOfData != 0)
        {
            if(pThunk->u1.Ordinal & 0x8000000000000000)
            {
                printf("        Ordinal: 0x%0411X\n", pThunk->u1.Ordinal & 0xFFFF);

            }
            else
            {
                PIMAGE_IMPORT_BY_NAME pName = (PIMAGE_IMPORT_BY_NAME)
                (
                    pBuffer + RvaToOffset(pNt, (DWORD)pThunk->u1.AddressOfData)
                );
                printf("        %s\n", pName->Name);
            }
            pThunk++;

        }
        printf("\n");
        pImport++;
    }
}