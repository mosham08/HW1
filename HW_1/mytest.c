#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define MAX_FILE_SIZE 4098
#define MAX 1000

struct Disk {
    char data[256];
    // is free bit
    unsigned free: 1;
    // add the file name later
};
struct Disk *disk[MAX];

void loadFileInDisk(const char *fileName) {
    char buffer[MAX_FILE_SIZE];
    printf("%4s: %s\n", "File", fileName);
    FILE *file;
    file = fopen(fileName, "rb");// rb= read binary
    size_t i, j, index;
    if (file != NULL) {
        int ch;
        i = 0;
        while ((ch = fgetc(file)) != EOF) {
            buffer[i++] = ch;
        }
        buffer[i++] = 0x00;
        j = i;
        fclose(file);
    }

    printf("%4s: 11111111111111 %s\n", "File", fileName);
    int size = sizeof(buffer) / sizeof(buffer[0]);
    double value = (double) j / 256.0;
    int blocks = (int) ceil(value);
    printf("Size of the array: %ld  number of blocks: %d\n", j, blocks);

    index = 0; // to 256
    int countBlocks = 0; // to number of blocks
    for (i = 0; i < j; ++i) {
        if (buffer[i] == 0x00) break;
        // make sure that the data cell is free.
        disk[countBlocks]->data[index] = buffer[i];
        disk[countBlocks]->free = 1;
        index++;

        if (index > 256) {
            index = 0;
            countBlocks++;
            printf("Next block %d \n", countBlocks);
        }
    }

    printf("After loading files: %ld\n", index);
    for (int i1 = 0; i1 < blocks; i1++) {
        printDiskBlock(disk[i1]);
    }
}

void initDisk() {
    size_t index;
    for (index = 0; index < MAX; ++index) {
        // allocate mem for the earthquakes structure
        disk[index] = (struct Disk *) malloc(sizeof(struct Disk));
        disk[index]->free = 0;
    }
}

void printDiskBlock(struct Disk *disk) {
    printf("%-40s", disk->data);
    printf("\n%-12u\n", disk->free);
}

int main() {
// code to initialize the disk in memory (blocks or 256 bytes)
    initDisk();

    DIR *folder;
    struct dirent *entry;
    struct stat filestat;

    folder = opendir(".");
    if (folder == NULL) {
        perror("Unable to read directory");
        return (1);
    }

    /* Read directory entries */
    while ((entry = readdir(folder))) {
        stat(entry->d_name, &filestat);
        if (S_ISDIR(filestat.st_mode))
            printf("%4s: %s\t%s\n", "Dir", entry->d_name, ctime(&filestat.st_ctime));
        else {
            printf("%4s: %s\t%s\n", "File", entry->d_name, ctime(&filestat.st_ctime));
            loadFileInDisk(entry->d_name);
            break;
        }

    }
    closedir(folder);
}


//
//void readFile(const char *fileName) {
//    char buffer[MAX_FILE_SIZE];
//    printf("%4s: %s\n", "File", fileName);
//    FILE *file;
//    file = fopen(fileName, "rb");
//    size_t i, j;
//    if (file != NULL) {
//        int ch;
//        i = 0;
//        while ((ch = fgetc(file)) != EOF) {
//            buffer[i++] = ch;
////            if (isprint(ch)) {
////                printf("%c", ch);
////            } else {
////                printf("'%02X'", ch);
////                if (ch == '\n') {
////                    fputs("\n", stdout);
////                }
////            }
//
//        }
//        buffer[i++] = 0x00;
//        j = i;
//        fclose(file);
//    }
//    // print out the buffer
//    for (i = 0; i < j; ++i) {
//        if (isprint(buffer[i])) {
//            printf("%c", buffer[i]);
//        } else {
//            printf("'%02X'", buffer[i]);
//            if (buffer[i] == '\n') {
//                fputs("\n", stdout);
//            }
//        }
//    }
//}
