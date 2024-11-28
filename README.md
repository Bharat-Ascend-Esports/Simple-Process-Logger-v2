# Simple-Process-Logger-v2 🔒

Welcome to the **Simple Process Logger v2**! Written in C for optimal performance and low-level system access, this version is a significant upgrade over [Simple Process Logger v1](https://github.com/Bharat-Ascend-Esports/Simple-Process-Logger). With features like secure HTTPS communication, detailed error handling, and JSON payload integration, it offers robust and secure process monitoring. For those with simpler needs, v1 remains available as a lightweight alternative.

---

## Prerequisites 🛠️

- **Required DLLs**: Ensure the following DLLs are available in the same directory as the executable if you encounter missing dependency errors:
  - `libgcc_s_seh-1.dll`
  - `libjson-c-5.dll`
  - `libwinpthread-1.dll`

- **Programming Language**: C.

- **Operating System**: Windows 10 or 11.
- **Compiler**: GCC (MinGW) or MSVC.
- **Libraries**:
  - `wininet`
  - `psapi`
  - `json-c`

---

## Installation 📦

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/yourusername/process-logger.git
   cd process-logger
   ```

2. **Build the Application**: Compile the source code using GCC:

   ```bash
   gcc -o process_logger.exe process_logger.c -lwininet -ljson-c -I"C:/msys64/mingw64/include" -L"C:/msys64/mingw64/lib" -mconsole
   ```

---

## Usage 🖥️

1. Run the executable:

   ```bash
   process_logger.exe
   ```

2. Enter your **Steam ID** and **Match ID** when prompted:

   ```
   Enter your Steam ID: 123456789
   Enter your Match ID: match123
   ```

3. Let the application run to monitor and send logs every 30 seconds.

---

## Configuration 🗃️

- **Server URL**: Update the `SERVER_URL` macro in the source code to point to your server.
- **Authorization Token**: Replace the `AUTH_TOKEN` macro with your server's authorization token.

---

## Example Output 📋

```bash
888'Y88                               888   Y8b Y8b Y888P           d8            888                    
888 ,'Y 888,8,  ,"Y88b 8888 8888  e88 888    Y8b Y8b Y8P   ,"Y88b  d88    e88'888 888 ee   ,e e,  888,8,
888C8   888 "  "8" 888 8888 8888 d888 888     Y8b Y8b Y   "8" 888 d88888 d888  '8 888 88b d88 88b 888 " 
888 "   888    ,ee 888 Y888 888P Y888 888      Y8b Y8b    ,ee 888  888   Y888   , 888 888 888   , 888   
888     888    "88 888  "88 88"   "88 888       Y8P Y     "88 888  888    "88,e8' 888 888  "YeeP" 888   

            Created by Bharat Ascend Esports - Empowering Gaming and Innovation

Enter your Steam ID: 123456789
Enter your Match ID: match123
[INFO] Logger started
[INFO] Gathering process list...
[INFO] Sending logs to server...
[INFO] JSON request sent successfully.
[INFO] Server response: {"message":"Log received and updated successfully.","status":"success"}
```

---

## Troubleshooting 🛠️

- **403 Forbidden**: Ensure the `AUTH_TOKEN` matches the server's token.
- **Failed to Enumerate Processes**: Ensure the application has sufficient permissions to read processes.
- **HTTP/HTTPS Errors**: Verify that the `SERVER_URL` is reachable and uses a valid SSL certificate.

---

## Contributing 🤝

We welcome contributions! To get started:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch-name`).
3. Commit your changes (`git commit -m 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch-name`).
5. Open a Pull Request.

---

## License 🔒

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Disclaimer ⚠️

This application is intended for educational purposes only. Ensure compliance with all relevant laws and policies when using this tool.

---

Happy logging! 🚀

