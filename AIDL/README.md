# AIDL with AOSP

Let's first take a journey through the structure and how we can use the `aidl-cpp` tool:  

### Initial Steps  
First, we manually create three components:  
- AIDL file  
- HAL drivers  
- Service drivers  

Now, let's assume we want to generate a Java application that calls the `setGpio` method to turn on an LED. We'll break down the functionality into smaller parts:  

1. **Driver Layer for Hardware**  
   - First, we need to generate the driver layer for hardware by configuring the device tree. This involves creating `.cpp` and `.h` files along with an `Android.bp` blueprint file as a shared library to generate the DTB (Device Tree Blob) under `/vendor/bin`.  
   - For example, after flashing, when I open the ADB shell and echo a value to the DTB, the LED should turn on.  

2. **Creating the HAL Layer**  
   - Next, we'll wrap these files (`gpioHAL.h` and `gpioHAL.cpp`) into a HAL (Hardware Abstraction Layer) for reusability. These files should be placed in a new directory, such as `gpio/hal`.  
   - Then, we'll create another folder called `test`, which contains a file like `test.cpp` to call methods from the HAL layer. In this file, we should include `gpioHAL.h` and also generate an `Android.bp` file in this directory.  

   **Note:**  
   - If we generate two separate folders (e.g., one for the HAL layer), we must create the `Android.bp` file in the `hal` directory as a `cc_binary_shared{}` to make it a shared library.  
   - However, if all the files are in the same directory, we only need one `Android.bp` file for a local build.

3. **Running the Application**  
   - To execute the program, we need to flash a vanilla RPi image onto the Raspberry Pi. After flashing, we can locate the executable file under `/system/bin`.  
   - If we specify `vendor = true` in the configuration, the executable will be found under `/vendor/bin` instead.  

   **Note:**  
   - If we include this in an RC file (e.g., `test.rc`) with the command `on boot system/bin/test` (on a boot trigger), it will start automatically after booting.  
   - This setup works fine on Android 14 and 15 without policy enforcement if only logging is required. However, for direct hardware access, we need user and group permissions (as root) so the filesystem runs with those permissions. Alternatively, we can use AC policies.  

---

### Upgrading to Java Integration  

Next, we want to upgrade the system to use Java by calling `set` and `get` methods via the Java runtime environment. This means introducing a service layer as the mediator between the Java code and the HAL layer.  

1. **Service Layer**  
   - We'll create a folder, such as `gpio_service`, containing:  
     - `gpioService.cpp`  
     - `gpioService.h`  
     - `gpioService.rc`  

2. **Key Configurations**  
   - In `gpioService.rc`, include:  
     - The class (`hal`).  
     - User and group permissions (as root).  
     - Use `oneshot` to ensure that if the service encounters an error and terminates, Android won't automatically restart it. Alternatively, you can use the `on boot` trigger.  

---

![Alt Text](/images/01.png)

for this part: Configuration Explained

### I2C Settings

- **`dtparam=i2c_arm=on`:** Activates the I2C interface on the ARM processor, enabling communication via SCL (clock) and SDA (data) lines.  
- **`dtparam=i2c_arm_baudrate=400000`:** Sets the I2C bus speed to 400 kHz for fast communication.  
- **`dtoverlay=ads1115`:** Loads the device tree overlay for the ADS1115 ADC, enabling kernel recognition and management of the hardware.

### ADC Settings

- **`dtparam=cha_enable`:** Activates Channel A of the ADS1115 ADC for analog signal reading.  
- **`dtparam=chb_enable`:** Activates Channel B.  
- **`dtparam=chc_enable`:** Activates Channel C.  
- **`dtparam=chd_enable`:** Activates Channel D.  

What Happens Next?

After setting these parameters:

    I2C Communication: The system can perform I2C read (i2c_read) and write (i2c_write) operations to communicate with devices on the I2C bus. For example, this could include configuring the ADS1115 or reading the digital output of its analog inputs.

    ADC Functionality: With all four channels (A, B, C, D) enabled, the system can use the ADS1115 to:
        Convert analog signals (e.g., sensor readings) into digital values.
        Access those digital values via the I2C interface.

These configurations are essential for applications requiring precise analog measurements (e.g., temperature sensors, light sensors, or potentiometers) and allow the Raspberry Pi (or other host device) to interact seamlessly with analog hardware through the ADS1115 ADC.


now under the rpi4 folder lets create our package -> (hal/gpio)
we inspire that from light pakage

![Alt Text](/images/02.png)

as the main.cpp file is the service function
light.cpp, light.h is the interface implementation
xml file is the descriptor file of aidl that system need
rc file 
like that:

![Alt Text](/images/03.png)

and the last file is bp file put here he didn't put the aidl file or its related files 
these remaining files is at vendor/overlays/aidl 

sh```
aosp/
├── build/
├── device/
├── system/
├── vendor/
│   ├── google/
│   ├── qualcomm/
│   ├── mediatek/
│   └── <other vendors>/
```

now let's put our hal files at lib folder and i will put on it gpiohal.h, gpiohal.cpp
and at the same gpio folder we will put 2 folders (manifest,sepolicy)custom folders
that for educational purpose put policy should be at the parent directory
so let's start with gpio/lib dir:
![Alt Text](/images/04.png)
![Alt Text](/images/05.png)
here is the going to the file stream to write and so on

{if we have the intention to use it at external module and going to put it at a separate file and includeing it at another service so i should to add at the same folder blueprint file and then extern it as blueprint file and naming it at bp file then should include it their  (at where i need)}
for this part again:
If you intend to use a specific functionality, like a GPIO HAL (Hardware Abstraction Layer), in an external module and need to organize it as a separate file for reusability, here’s how you can achieve it. Below is a breakdown of the process:
1. Organize the External Module

To make the GPIO HAL reusable, it should be separated into its own library. This involves creating header files (e.g., gpiohal.h) and source files (e.g., gpiohal.cpp) and placing them in a structured directory.
Directory Example:

sh```
aosp/
├── hal/
│   ├── gpio/
│   │   ├── lib/                # Contains reusable GPIO HAL files
│   │   │   ├── gpiohal.h       # Header file with function declarations
│   │   │   ├── gpiohal.cpp     # Source file with function implementations
│   │   ├── manifest/           # Contains HAL manifest for this module
│   │   ├── sepolicy/           # Security policy configurations
```

2. Create a Blueprint File for the Library

Blueprint files (Android.bp) are essential for defining how to build the module within AOSP. For the gpiohal library, create a blueprint file in the same folder (hal/gpio/lib/).
Example Android.bp for gpiohal

sh```
cc_library {
    name: "libgpiohal",
    srcs: [
        "gpiohal.cpp",
    ],
    shared_libs: [
        "libc",           // Standard C library
        "libbase",        // Android's base library for utilities
    ],
    export_include_dirs: ["."], // Export this library's header files for other modules
}

    name: The name of the library, here libgpiohal.
    srcs: Specifies the source files (e.g., gpiohal.cpp) to compile.
    shared_libs: Lists shared libraries that the module depends on.
    export_include_dirs: Makes the header files available for other modules.
```
3. Include the External Module in Another Service

To use the gpiohal library in another service:

    Include the header file (gpiohal.h) in your service’s source file.
    Modify the service's blueprint file (Android.bp) to include libgpiohal as a dependency.

Example:

Imagine a service called gpiocontrol located in hal/gpio/service/.
Service File Structure

sh```

hal/gpio/service/
├── main.cpp           # Service logic
├── Android.bp         # Blueprint file for the service
```
Modify Android.bp for gpiocontrol

sh```
cc_binary {
    name: "gpiocontrol",
    srcs: [
        "main.cpp",
    ],
    shared_libs: [
        "libc",
        "libbase",
        "libgpiohal",  // Add the external gpiohal library
    ],
    init_rc: ["gpiocontrol.rc"],  // Service init file
}
```

Include gpiohal.h in main.cpp

sh```
#include "gpiohal.h"

int main() {
    // Example usage of GPIO HAL
    GPIOHAL gpio;
    gpio.initialize();
    gpio.setPin(4, 1); // Set GPIO pin 4 to HIGH
    return 0;
}
```

4. Externalize the Library

If the gpiohal library is to be shared across multiple services, ensure it is:

    Defined as a standalone library (libgpiohal as per the example).
    Properly exported via export_include_dirs in its Android.bp.
    Declared as a dependency (shared_libs) in any module requiring it.

5. Optional: Blueprint for External Modules

If you plan to use the library as an external module, include it in the parent directory of your project or in the central vendor/ or external/ directory.

For example:

sh```
vendor/myvendor/external_gpio/
├── Android.bp         # External library blueprint
├── gpiohal.h
├── gpiohal.cpp
```

Blueprint for external usage:

sh```
cc_library {
    name: "libgpiohal_external",
    srcs: [
        "gpiohal.cpp",
    ],
    export_include_dirs: ["."],
}
```

To include this external module in another service:

    Ensure libgpiohal_external is added to shared_libs.
    Include the header files as needed.

6. Notes on SEPolicy and Manifest

    SEPolicy: Add appropriate security policies in the sepolicy folder, ensuring that the gpiohal service and its users have access permissions.
    Manifest: Define the HAL details in a manifest file if this is a shared HAL. Example manifest (manifest.xml):

sh```
    <hal format="aidl">
        <name>android.hardware.gpio</name>
        <version>1.0</version>
        <interface>
            <name>IGPIO</name>
            <instance>default</instance>
        </interface>
    </hal>
```
By following these steps, you can structure and use the GPIO HAL as a reusable external module effectively.
let's now the main fuction for interface 
i could merge the main and implementation

![Alt Text](/images/07.png)

untill now this is the hierarchy

![Alt Text](/images/06.png)

these are the 2 methods should be implemented inside the service
and take in considration package is: `package com.luxoft.gpio;` so folders should be com/luxoft/gpio (reverse name)
at the bp file : let's put our package as name: com.luxoft.gpio, vendor_available : true to be located at vendor partation or at older releases the service would be found under /ODM , srcs: "interfaces/**/*.aidl" to access .aidl files should go through this hierarchy

`local_include_dir: "interfaces",`
and this isn't so important
is typically used in an Android.bp file to specify a single local directory containing aidl files (.h) that are needed for compiling the current module.


Unlike local_include_dirs, which allows specifying multiple directories in a list, local_include_dir is used to define just one directory. The specified directory is relative to the location of the Android.bp file.

aidl allows import as i could create at the gpio dir else (types.aidl)

so for this file after generating it after import types at IGpioService file how the sys will find it through local_include_dir: "interfaces",

i have else backend that i addto it or untill now i actually care about cpp only

sh```
backend: {
        java: {
            enabled: true,
            platform_apis: true,
        },
        cpp: {
            enabled: true,
        },
        ndk: {
            enabled: true,
        },
    }
```
to sepecifiy after build i will use this interface for what
==================> export at shared library for export my locations is for after build i want it to be eanble to people to search on it
or  using feature visiblity and apply this feature for other people

ok to rearrange or work flow this is our new hierarchy:

![Alext](/images/08.png)


now let's build at 3 steps: so at first we need to generate to it it's first version which should have its hash using (freeze) and then update pakages to makesure that every thing is ok finally i should generate from aidl file its cpp,h files 
```sh
source build/envsetup.sh
lunch aosp_rpi4_car-ap2a-userdebug or eng
//Want FASTER LOCAL BUILDS? Use -eng instead of -userdebug (however for performance benchmarking continue to use userdebug)
make bootimage systemimage vendorimage -j$(nproc)
```
1) `make com.nada.gpio-freeze-api`
each freeze generate a new with a new hash
i just update the hierarchy with my name: 

```sh
package com.nada.gpio;

interface IGpioService {
	boolean setGpioState(int pin, boolean value);
	boolean getGpioState(int pin);
}
```
![Alt Text](/images/10.png)

![Alt Text](/images/11.png)

this part appear at our bp files:
```sh
    versions_with_info: [
        {
            version: "1",
            imports: [],
        },
    ],
```
`frozen: true,` this line may throw error so we will handle that later

![Alt Text](/images/12.png)

![Alt Text](/images/13.png)
![Alt Text](/images/14.png)

here is our hash generated and its a frozen version:

![Alt Text](/images/15.png)

2) `make com.nada.gpio-update-api` to generate current folder from last version on our package

![Alt Text](/images/6.png)
![Alt Text](/images/17.png)

3) let's now use our aidl tool `aidl-cpp -h` `-h` to now how to use

![Alt Text](/images/18.png)
![Alt Text](/images/19.png)

it take generally INPUT HEADER_DIR OUTPUT: so input aidl path (take it by right click on IGpioService and copy path) and space then copy it again without file name(to specify where it should put the generated header files) and again paste the path without aidl file name (to specify where should put the generated .cpp files) for notice this syntax isn't right the terminal will describe that:
for my case it looks like: 
```sh
aidl-cpp /media/iti/468469bc-700b-47e2-ad57-0efb9731e806/android-14.0.0_r67/device/brcm/rpi4/haltest/gpio/interfaces/com/nada/gpio/IGpioService.aidl /media/iti/468469bc-700b-47e2-ad57-0efb9731e806/android-14.0.0_r67/device/brcm/rpi4/haltest/gpio/interfaces/com/nada/gpio/ /media/iti/468469bc-700b-47e2-ad57-0efb9731e806/android-14.0.0_r67/device/brcm/rpi4/haltest/gpio/interfaces/com/nada/gpio/
```
![Alt Text](/images/20.png)

so here it announced me to add `/com/nada/gpio/IGpioService.cpp` to the output file
here we go

![Alt Text](/images/21.png)



=============>
to make our build system to know that's is my compatability file

then should add
# DEVICE_FRAMEWORK_COMPATIBILITY_MATRIX_FILE += device/brcm/rpi4/haltest/manifests/framework_compatibility_matrix
