/* 
    - Intentionally Vulnerable C Program
    - Contains 7 common C Vulnerabilites
    - Vulnerabilities: Buffer Overflow, Out-of-Bound Write/Read, Invalid Array Index, 
    Use-After-Free, Double Free, Null Dereference, Insecure Randomness
    // modified to work with libfuzzer and use its entry point
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

void buffer_overflow(const char *data, size_t dataSize) {
    char buf[8];
    strcpy(buf, data);
    printf("in buffer flow function, buf: %s", buf);
}

// writing to an invalid index of an array
void out_of_bounds_write(const char *data, size_t dataSize) {
    int test[4] = {0, 1, 2, 3};
    test[6] = 5;
}

// reading an invalid index of an array
void out_of_bounds_read(const char *data, size_t dataSize) {
    int test[4] = {0, 1, 2, 3};
    printf("%d", test[dataSize]);
}

void improper_array_index(const char *data, size_t dataSize) {
    int test[4] = {0, 1, 2, 3};
    test[dataSize] = 5;
}

void using_free_memory(const char *data, size_t dataSize) {
    int *alloc_memory;
    
    alloc_memory = (int*)malloc(sizeof(int));
    *alloc_memory = 4;
    free(alloc_memory);
    *alloc_memory = 20;
}

void using_double_free_memory(const char *data, size_t dataSize) {
    int *alloc_memory;
    
    alloc_memory = (int*)malloc(sizeof(int));
    *alloc_memory = 4;
    free(alloc_memory);
    free(alloc_memory);
}

void null_dereference(const char *data, size_t dataSize) {
    int *pointer = NULL;
    printf("this is me dereferencing my pointer: %d", pointer[0]);

}

// Fuzzer entry point for C code
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t len) {
    if (len < 1) return 0;  // Ensure there is some data

    printf("Running vulnerable functions...\n");

    // Call the vulnerable functions with the fuzzed input
    buffer_overflow(data, len);
    out_of_bounds_write(data, len);
    out_of_bounds_read(data, len);
    improper_array_index(data, len);
    using_free_memory(data, len);
    using_double_free_memory(data, len);
    null_dereference(data, len);

    return 0;
}