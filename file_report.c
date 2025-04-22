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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide input for fuzzing.\n");
        return 0;
    }

    const char *input = argv[1];  // Using char here instead of unsigned char
    size_t len = strlen(input);
    if (len < 1) {
        printf("Input is too short to fuzz.\n");
        return 0;
    }

    // Use the first byte of input to select a vulnerability
    unsigned char selector = input[0] % 7;

    printf("Running vulnerable functions...\n");

    // Trigger vulnerabilities based on the selected vulnerability
    switch (selector) {
    case 0:
        printf("Triggering buffer_overflow()\n");
        buffer_overflow();
        break;
    case 1:
        printf("Triggering out_of_bounds_write()\n");
        out_of_bounds_write();
        break;
    case 2:
        printf("Triggering out_of_bounds_read()\n");
        out_of_bounds_read();
        break;
    case 3:
        printf("Triggering improper_array_index()\n");
        improper_array_index(7);
        break;
    case 4:
        printf("Triggering use-after-free\n");
        using_free_memory();
        break;
    case 5:
        printf("Triggering double-free\n");
        using_double_free_memory();
        break;
    case 6:
        printf("Triggering null_dereference\n");
        null_dereference();
        break;
}

    return 0;
}
