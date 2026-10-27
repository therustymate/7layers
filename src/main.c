#include "7layers.h"
#include "context.h"

int main(int argc, char *argv[]) {
    ANTI_DISASM();
    if (argc < 1) {
        printf("Usage: %s [OPTIONS]", argv[0]);
    }

    initialize_environment_blocks(&g_PEB, &g_TEB);
    initialize_pe_context(&g_PE_HEAD);

    

    cleanup_pe_context(&g_PE_HEAD);
    return 0;
}