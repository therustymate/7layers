#pragma once

#include "7layers.h"

int initialize_environment_blocks(PPEB* peb, PTEB* teb);
void cleanup_pe_context(PE_CONTEXT** head);
int initialize_pe_context(PE_CONTEXT** head);