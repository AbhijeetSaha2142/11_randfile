#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {

    int file = open("/dev/random", O_RDONLY);
    if (file == -1) {
        printf("errno: %d, error: %s\n", errno, strerror(errno));
        return 0;
    }

    printf("Generating random numbers:\n");
    int randnums[10]; 
    int i;
    for (i = 0; i < 10; i++) {
        int n = read(file, &randnums[i], sizeof(randnums[i]));
        if (n == -1){ // could run out in the middle, though unlikely
            printf("errno: %d\terror: %s\n", errno, strerror(errno));
            return 0; 
        }
        printf("\trandom %d: %d\n", i, randnums[i]);
    }
    printf("\n");
    
    printf("Writing numbers to file...\n\n");
    int randout = open("randout.out", O_CREAT | O_WRONLY, 0644);
    if (randout == -1){
        printf("errno: %d\terror: %s\n", errno, strerror(errno));
        return 0;
    }

    int k = write(randout, randnums, sizeof(randnums));
    if (k == -1){
        printf("errno: %d, error: %s\n", errno, strerror(errno));
            return 0; 
    }

    printf("Reading numbers from file...\n\n");
    int file2 = open("randout.out", O_RDONLY);
    if (file2 == -1) {
        printf("errno: %d\terror: %s\n", errno, strerror(errno));
        return 0;
    }

    printf("Verification that written values were the same:\n");
    int randnums2[10]; 
    for (i = 0; i < 10; i++) {
        int n = read(file2, &randnums2[i], sizeof(randnums2[i]));
        if (n == -1){
            printf("errno: %d\terror: %s\n", errno, strerror(errno));
            return 0; 
        }
        printf("\trandom %d: %d\n", i, randnums2[i]);
    }

    printf("\n");

    return 0;
}