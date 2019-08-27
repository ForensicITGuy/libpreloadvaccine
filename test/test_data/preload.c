#include <stdio.h>

static void init(int argc, char **argv, char **envp) {
    printf("Preload Successful!\n");
}

__attribute__((section(".init_array"), used)) static typeof(init) *init_p = init;