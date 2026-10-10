#include "pe-parser.h"
void PrintFileCharacteristics(WORD characteristics) {
    
    
    if (characteristics & IMAGE_FILE_RELOCS_STRIPPED)         printf("RELOCS_STRIPPED ");
    if (characteristics & IMAGE_FILE_EXECUTABLE_IMAGE)        printf("EXECUTABLE_IMAGE ");
    if (characteristics & IMAGE_FILE_LINE_NUMS_STRIPPED)      printf("LINE_NUMS_STRIPPED ");
    if (characteristics & IMAGE_FILE_LOCAL_SYMS_STRIPPED)     printf("LOCAL_SYMS_STRIPPED ");
    if (characteristics & IMAGE_FILE_LARGE_ADDRESS_AWARE)     printf("LARGE_ADDRESS_AWARE ");
    if (characteristics & IMAGE_FILE_BYTES_REVERSED_LO)       printf("BYTES_REVERSED_LO ");
    if (characteristics & IMAGE_FILE_32BIT_MACHINE)           printf("32BIT_MACHINE ");
    if (characteristics & IMAGE_FILE_DEBUG_STRIPPED)          printf("DEBUG_STRIPPED ");
    if (characteristics & IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP) printf("REMOVABLE_RUN_FROM_SWAP ");
    if (characteristics & IMAGE_FILE_NET_RUN_FROM_SWAP)       printf("NET_RUN_FROM_SWAP ");
    if (characteristics & IMAGE_FILE_SYSTEM)                  printf("SYSTEM ");
    if (characteristics & IMAGE_FILE_DLL)                     printf("DLL ");
    if (characteristics & IMAGE_FILE_UP_SYSTEM_ONLY)          printf("UP_SYSTEM_ONLY ");
    
}
void PrintDllCharacteristics(WORD characteristics) {
    printf("0x%04X (", characteristics);
    
    if (characteristics & 0x0020) printf("HIGH_ENTROPY_VA ");
    if (characteristics & 0x0040) printf("DYNAMIC_BASE ");
    if (characteristics & 0x0080) printf("FORCE_INTEGRITY ");
    if (characteristics & 0x0100) printf("NX_COMPAT ");
    if (characteristics & 0x0200) printf("NO_ISOLATION ");
    if (characteristics & 0x0400) printf("NO_SEH ");
    if (characteristics & 0x0800) printf("NO_BIND ");
    if (characteristics & 0x1000) printf("APPCONTAINER ");
    if (characteristics & 0x2000) printf("WDM_DRIVER ");
    if (characteristics & 0x4000) printf("GUARD_CF ");
    if (characteristics & 0x8000) printf("TERMINAL_SERVER_AWARE ");
    
    printf(")");
}