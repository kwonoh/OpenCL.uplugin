// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "OpenCLPluginPrivatePCH.h"

class OpenCLPlugin : public IOpenCLPlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( OpenCLPlugin, OpenCL )
DEFINE_LOG_CATEGORY(LogOpenCL);

void OpenCLPlugin::StartupModule()
{
	UE_LOG(LogOpenCL, Log, TEXT("OpenCL Info:"));

	cl_uint i, j;
	char* value;
	size_t valueSize;
	cl_uint platformCount;
	cl_platform_id* platforms;
	cl_uint deviceCount;
	cl_device_id* devices;
	cl_uint maxComputeUnits;

	// get all platforms
	clGetPlatformIDs(0, NULL, &platformCount);
	platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * platformCount);
	clGetPlatformIDs(platformCount, platforms, NULL);

	for (i = 0; i < platformCount; i++) {
		clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 0, NULL, &valueSize);
		value = (char*)malloc(valueSize);
		clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, valueSize, value, NULL);
		UE_LOG(LogOpenCL, Log, TEXT("Platform: %s"), ANSI_TO_TCHAR(value));
		free(value);

		// get all devices
		clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceCount);
		devices = (cl_device_id*)malloc(sizeof(cl_device_id) * deviceCount);
		clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, deviceCount, devices, NULL);

		// for each device print critical attributes
		for (j = 0; j < deviceCount; j++) {

			// print device name
			clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &valueSize);
			value = (char*)malloc(valueSize);
			clGetDeviceInfo(devices[j], CL_DEVICE_NAME, valueSize, value, NULL);
			UE_LOG(LogOpenCL, Log, TEXT("  Device: %s"), ANSI_TO_TCHAR(value));
			free(value);

			// print hardware device version
			clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, 0, NULL, &valueSize);
			value = (char*)malloc(valueSize);
			clGetDeviceInfo(devices[j], CL_DEVICE_VERSION, valueSize, value, NULL);
			UE_LOG(LogOpenCL, Log, TEXT("    Hardware version: %s"), ANSI_TO_TCHAR(value));
			free(value);

			// print software driver version
			clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, 0, NULL, &valueSize);
			value = (char*)malloc(valueSize);
			clGetDeviceInfo(devices[j], CL_DRIVER_VERSION, valueSize, value, NULL);
			UE_LOG(LogOpenCL, Log, TEXT("    Software version: %s"), ANSI_TO_TCHAR(value));
			free(value);

			// print c version supported by compiler for device
			clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, 0, NULL, &valueSize);
			value = (char*)malloc(valueSize);
			clGetDeviceInfo(devices[j], CL_DEVICE_OPENCL_C_VERSION, valueSize, value, NULL);
			UE_LOG(LogOpenCL, Log, TEXT("    OpenCL C version: %s"), ANSI_TO_TCHAR(value));
			free(value);

			// print parallel compute units
			clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS,
							sizeof(maxComputeUnits), &maxComputeUnits, NULL);
			UE_LOG(LogOpenCL, Log, TEXT("    Parallel compute units: %d"), maxComputeUnits);
		}

		free(devices);

	}

	free(platforms);
}

void OpenCLPlugin::ShutdownModule() {}
