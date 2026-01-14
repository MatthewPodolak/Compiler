#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stdlib.h>

#define MAX_PTRS 4096

typedef struct {
    void *ptrs[MAX_PTRS];
    int count;
} MemoryTracker;

extern MemoryTracker g_mem_tracker;

void mem_init(void);
void *mem_alloc(size_t size);
char *mem_strdup(const char *s);
void mem_cleanup(void);

void cleanup_variable_table(void);
void cleanup_array_table(void);
void cleanup_temp_table(void);
void cleanup_print_table(void);
void cleanup_private_vars_table(void);
void cleanup_high_statement_table(void);
void cleanup_for_statement_table(void);
void cleanup_flow_table(void);

void cleanup_all(void);

#endif