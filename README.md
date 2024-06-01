NeoRec EEG Data Acquisition

This project is a C++ console application designed to interact with the NEOREC 16 device, a mobile EEG data acquisition system. The application allows you to configure the device, read EEG data, and simulate these data if the device is not available.

Project Structure

- NeoRec.h: Contains declarations of the `NeoRec` class and necessary functions to interact with the device DLL.
- NeoRec.cpp: Contains definitions of the functions of the `NeoRec` class.
- main.cpp**: Contains the main logic of the application, including initializing the `NeoRec` class, data acquisition, and console display.
- /bin/: Folder containing the necessary DLLs to interact with the device.
- /lib/: Folder containing example project files and headers provided by the manufacturer.

Usage

Compilation

1. Open Visual Studio.
2. Create a new console application project.
3. Add the `NeoRec.h`, `NeoRec.cpp`, and `main.cpp` files to the project.
4. Copy the DLLs (`nb2mcs_x64.dll` and `nb2mcs_x86.dll`) to the project's output folder (e.g., `Debug` or `Release`).

Execution

The application can run in two modes: simulation and real mode. By default, the simulation mode is enabled to allow development without the physical device.


Expected Output
In simulation mode, the output should show random EEG data in the console:

Reading EEG data...
38 30 1 77 96 55 96 9 54 46 82 21 14 14 1 30
92 49 52 1 62 94 13 89 67 39 96 31 84 18 87 51
...

In real mode, the output will display the EEG data captured by the NEOREC 16 device.

Contributions
Contributions are welcome. If you have suggestions, bugs, or improvements, feel free to open an issue or submit a pull request.
