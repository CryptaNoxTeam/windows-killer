# Windows Killer

**Windows Killer** is an educational tool designed to overwrite the Master Boot Record (MBR) of all physical drives on both **Windows** and **Unix-like systems** (Linux, macOS, BSD, etc.). The tool erases the first 512 bytes of each physical drive, which is the MBR, making the system unbootable. This is a destructive action and should be used with caution.

---

### ⚠️ **Warning: Educational Purposes Only**
This tool is for **educational** purposes only! The use of this tool on systems that you do not own or have explicit permission to modify is **illegal** and **unethical**. The **developer is not responsible** for any damage caused by using this tool. Misuse of this tool may result in data loss, unbootable systems, and other severe consequences. Use it responsibly and at your own risk.

---

## Features

- **For Windows**: Detects all physical drives (`\\.\PhysicalDrive0`, `\\.\PhysicalDrive1`, etc.) and overwrites their MBR with zeroes.
- **For Unix-like systems (Linux, macOS, BSD)**: Detects all physical drives (`/dev/sda`, `/dev/sdb`, etc.) and overwrites their MBR with zeroes.

---

## File Names

- **`unix.c`**: Contains the code for Unix-like systems (Linux, macOS, BSD).
- **`windows.c`**: Contains the code for Windows systems.

---

## 🚀 How to Use the Tool

### 1. **Compiling and Using the Windows Version (`windows.c`)**

#### Prerequisites:
- You need a **C compiler**. For Windows, the easiest options are:
  - **MinGW** (Minimalist GNU for Windows)
  - **Microsoft Visual Studio** (MSVC)

#### Steps:
1. **Install a C Compiler**:
   - **MinGW**: Download from [MinGW-w64](https://mingw-w64.org/) and follow installation instructions.
   - **MSVC**: Install Microsoft Visual Studio from [Visual Studio](https://visualstudio.microsoft.com/) and include the C++ development workload.

2. **Compile the Program**:
   - Open **Command Prompt** (with Administrator privileges).
   - Navigate to the folder containing `windows.c`.
   - Run the following command to compile using **MinGW**:
     ```bash
     gcc -o windows_killer.exe windows.c
     ```
   - Alternatively, if you are using **MSVC**:
     ```bash
     cl windows.c
     ```

3. **Run the Program**:
   - Open **Command Prompt** as Administrator.
   - Run the compiled program:
     ```bash
     windows_killer.exe
     ```

   The program will overwrite the MBR of all detected physical drives on your system. Be sure to double-check the drives before running this tool.

### 2. **Compiling and Using the Unix Version (`unix.c`)**

#### Prerequisites:
- You need a **C compiler** for Unix-like systems:
  - **GCC** (GNU Compiler Collection)
  - **Clang** (for macOS and BSD)

#### Steps:
1. **Install a C Compiler**:
   - **Linux**: Usually comes with GCC pre-installed. If not, install via the package manager:
     ```bash
     sudo apt install build-essential  # On Debian/Ubuntu
     sudo yum groupinstall 'Development Tools'  # On CentOS/RHEL
     ```
   - **macOS**: You can install **Xcode Command Line Tools**:
     ```bash
     xcode-select --install
     ```

2. **Compile the Program**:
   - Open a **terminal** and navigate to the folder where `unix.c` is saved.
   - Run the following command to compile the program:
     ```bash
     gcc -o unix_killer unix.c
     ```

3. **Run the Program**:
   - **Linux/macOS/BSD**: Run the program with `root` privileges to access the physical drives:
     ```bash
     sudo ./unix_killer
     ```

   The program will overwrite the MBR of all detected physical drives on your system. Again, be very careful with this action.

---

## 🧑‍💻 Code Explanation

The code is **well-commented** and designed for **beginners** to understand. Here's an overview:

### Windows (`windows.c`):
- The code opens each physical drive (starting with `\\.\PhysicalDrive0`, `\\.\PhysicalDrive1`, etc.) and writes 512 zeroes to the MBR of each drive. This is done using the Windows API to interact with raw devices.

### Unix-like Systems (`unix.c`):
- The code scans the `/dev/` directory for devices starting with `sd` (e.g., `/dev/sda`, `/dev/sdb`, etc.), which are typically physical drives on Unix-like systems. It opens each device and writes 512 zeroes to the MBR.

The code is designed to be **easy to read** and **beginner-friendly**. Every function is explained with simple comments to help you understand how it works.

---

## ❗ Important Notes

- **Data Loss**: This tool will erase all partitions and data on the affected drives by overwriting the MBR. Once this is done, the system will be unbootable, and you will need to reinstall the operating system.
- **Use Only on Your Own Machines**: Make sure you are using this tool only on devices you own or have explicit permission to modify.
- **Backup Important Data**: Before using this tool, make sure to back up any important data on the drives you intend to overwrite.

---

## 👨‍💻 Contributing

Feel free to fork the repository and submit a pull request if you have suggestions, improvements, or bug fixes. Please ensure that any contributions comply with ethical standards and are used for **educational** purposes only.

---

## 📜 License

This tool is released under the [MIT License](LICENSE). You are free to use, modify, and distribute it for **educational purposes only**. **Any misuse of this tool** for malicious intent is strictly prohibited.

---

## 🧩 Additional Resources

- **Windows API Documentation**: [Microsoft Docs](https://learn.microsoft.com/en-us/windows/win32/api/)
- **Linux Device Files**: [Linux Documentation](https://www.kernel.org/doc/html/latest/admin-guide/devices.html)

---

**Disclaimer**: This project is for **educational purposes only**. Misuse of this tool can cause significant damage to your system. Always use responsibly and with caution.
