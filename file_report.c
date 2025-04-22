/* 
    - Intentionally Vulnerable C Program
    - Contains 7 common C Vulnerabilites
    - Vulnerabilities: Buffer Overflow, Out-of-Bound Write/Read, Invalid Array Index, 
    Use-After-Free, Double Free, Null Dereference, Insecure Randomness
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void buffer_overflow() {
    char buf[8];
    strcpy(buf, "hello isn't it fantastic I can write all of this");
    printf("in buffer flow function, buf: %s", buf);
}

// writing to an invalid index of an array
void out_of_bounds_write() {
    int test[4] = {0, 1, 2, 3};
    test[6] = 5;
}

// reading an invalid index of an array
void out_of_bounds_read() {
    int test[4] = {0, 1, 2, 3};
    printf("%d", test[6]);
}

void improper_array_index(int index) {
    int test[4] = {0, 1, 2, 3};
    test[index] = 5;
}

void using_free_memory() {
    int *alloc_memory;
    
    alloc_memory = (int*)malloc(sizeof(int));
    *alloc_memory = 4;
    free(alloc_memory);
    *alloc_memory = 20;
}

void using_double_free_memory() {
    int *alloc_memory;
    
    alloc_memory = (int*)malloc(sizeof(int));
    *alloc_memory = 4;
    free(alloc_memory);
    free(alloc_memory);
}

void null_dereference() {
    int *pointer = NULL;
    printf("this is me dereferencing my pointer: %d", pointer[0]);

}

int main() {
    printf("Running vulnerable functions...\n");

    buffer_overflow();
    out_of_bounds_write();
    out_of_bounds_read();
    improper_array_index(7);
    using_free_memory();
    using_double_free_memory();
    null_dereference();

    return 0;
}