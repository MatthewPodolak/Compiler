#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_manager.h"

MemoryTracker g_mem_tracker = { .count = 0 };

void mem_init(void) {
    g_mem_tracker.count = 0;
    for (int i = 0; i < MAX_PTRS; i++) {
        g_mem_tracker.ptrs[i] = NULL;
    }
}

void *mem_alloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr != NULL && g_mem_tracker.count < MAX_PTRS) {
        g_mem_tracker.ptrs[g_mem_tracker.count++] = ptr;
    }
    return ptr;
}

char *mem_strdup(const char *s) {
    if (s == NULL) return NULL;
    
    char *dup = strdup(s);
    if (dup != NULL && g_mem_tracker.count < MAX_PTRS) {
        g_mem_tracker.ptrs[g_mem_tracker.count++] = dup;
    }
    return dup;
}

void mem_cleanup(void) {
    for (int i = 0; i < g_mem_tracker.count; i++) {
        if (g_mem_tracker.ptrs[i] != NULL) {
            free(g_mem_tracker.ptrs[i]);
            g_mem_tracker.ptrs[i] = NULL;
        }
    }
    g_mem_tracker.count = 0;
}

void cleanup_all(void) {
    cleanup_flow_table();
    cleanup_variable_table();
    cleanup_array_table();
    cleanup_temp_table();
    cleanup_print_table();
    cleanup_private_vars_table();
    cleanup_high_statement_table();
    cleanup_for_statement_table();
    
    mem_cleanup();
}