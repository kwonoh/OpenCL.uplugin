OpenCL Plugin for Unreal Engine 4
=============
This plugin helps you to link OpenCL with your UE projects.
It is easy to link with OpenCL on OS X because it's already installed as a global framework.
But on windows it is not trivial. If you want to add/replace for other version or platform, you can replace the header files from [the Khronos OpenCL Registry](https://www.khronos.org/registry/cl/) and add/replace the OpenCL.lib files in [ThirdParty/OpenCL/Lib](https://github.com/kwonoh/OpenCL-UE4Plugin/tree/master/OpenCL/ThirdParty/OpenCL/Lib) from OpenCL SDKs of the SDK providers (Intel/ATI/NVIDIA).
The OpenCL.lib files helps you to link with OpenCL.dll which installed on system with the drivers.
(It is not recommended to link with OpenCL.dll directly.)

Supported Platform
----------------------

OS X, Windows on Intel CPU/GPU, NVIDIA GPU.
I've tested on OS X 10.10.1 (Intel Ivy Bridge, GT 650M, GTX 980) and Windows 8.1.
All suggestions for other platforms are welcome.

Known Issues
----------------------
* On windows, It's failed to run editor on Debug mode. (Development mode works well)


Installation
----------------------

### Windows

1. Install NVIDIA Graphics Driver and [Intel OpenCL runtime](https://software.intel.com/en-us/articles/opencl-drivers).
2. Copy "OpenCL" folder to "Plugins" folder under your project directory.
3. Add "OpenCLPlugin" under "PublicDependencyModuleNames" in your *.Build.cs file to include header files from your project.

### OS X

1. Copy "OpenCL" folder to "Plugins" folder under your project directory.
2. Add "OpenCLPlugin" under "PublicDependencyModuleNames" in your *.Build.cs file to include header files from your project.

Screenshots
----------------------

### Windows
![Log Screenshots on Windows](https://raw.githubusercontent.com/kwonoh/OpenCL-UE4Plugin/gh-pages/images/opencl-ue4plugin-log-win.png)

### OS X
![Log Screenshots on OS X](https://raw.githubusercontent.com/kwonoh/OpenCL-UE4Plugin/gh-pages/images/opencl-ue4plugin-log-osx.png)

Legal info
----------------------

Unreal® is a trademark or registered trademark of Epic Games, Inc. in the United States of America and elsewhere. Unreal® Engine, Copyright 1998 – 2014, Epic Games, Inc. All rights reserved.

Plugin is completely free and available under [MIT open-source license](LICENSE).
