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
	char* Value;
	size_t ValueSize;
	cl_uint NumPlatforms;
	cl_platform_id* Platforms;
	cl_uint NumDevices;
	cl_device_id* Devices;
	cl_uint MaxComputeUnits;

	clGetPlatformIDs(0, NULL, &NumPlatforms);
	Platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * NumPlatforms);
	clGetPlatformIDs(NumPlatforms, Platforms, NULL);

	for (i = 0; i < NumPlatforms; i++) {
		clGetPlatformInfo(Platforms[i], CL_PLATFORM_NAME, 0, NULL, &ValueSize);
		Value = (char*)malloc(ValueSize);
		clGetPlatformInfo(Platforms[i], CL_PLATFORM_NAME, ValueSize, Value, NULL);
		UE_LOG(LogOpenCL, Log, TEXT("Platform: %s"), ANSI_TO_TCHAR(Value));
		free(Value);

		// get all Devices
		clGetDeviceIDs(Platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &NumDevices);
		Devices = (cl_device_id*)malloc(sizeof(cl_device_id) * NumDevices);
		clGetDeviceIDs(Platforms[i], CL_DEVICE_TYPE_ALL, NumDevices, Devices, NULL);

		for (j = 0; j < NumDevices; j++) {
			clGetDeviceInfo(Devices[j], CL_DEVICE_NAME, 0, NULL, &ValueSize);
			Value = (char*)malloc(ValueSize);
			clGetDeviceInfo(Devices[j], CL_DEVICE_NAME, ValueSize, Value, NULL);
			UE_LOG(LogOpenCL, Log, TEXT("  Device: %s"), ANSI_TO_TCHAR(Value));
			free(Value);

			clGetDeviceInfo(Devices[j], CL_DEVICE_VERSION, 0, NULL, &ValueSize);
			Value = (char*)malloc(ValueSize);
			clGetDeviceInfo(Devices[j], CL_DEVICE_VERSION, ValueSize, Value, NULL);
			UE_LOG(LogOpenCL, Log, TEXT("    Hardware version: %s"), ANSI_TO_TCHAR(Value));
			free(Value);

			clGetDeviceInfo(Devices[j], CL_DRIVER_VERSION, 0, NULL, &ValueSize);
			Value = (char*)malloc(ValueSize);
			clGetDeviceInfo(Devices[j], CL_DRIVER_VERSION, ValueSize, Value, NULL);
			UE_LOG(LogOpenCL, Log, TEXT("    Software version: %s"), ANSI_TO_TCHAR(Value));
			free(Value);

			clGetDeviceInfo(Devices[j], CL_DEVICE_OPENCL_C_VERSION, 0, NULL, &ValueSize);
			Value = (char*)malloc(ValueSize);
			clGetDeviceInfo(Devices[j], CL_DEVICE_OPENCL_C_VERSION, ValueSize, Value, NULL);
			UE_LOG(LogOpenCL, Log, TEXT("    OpenCL C version: %s"), ANSI_TO_TCHAR(Value));
			free(Value);

			clGetDeviceInfo(Devices[j], CL_DEVICE_MAX_COMPUTE_UNITS,
							sizeof(MaxComputeUnits), &MaxComputeUnits, NULL);
			UE_LOG(LogOpenCL, Log, TEXT("    Parallel compute units: %d"), MaxComputeUnits);
		}

		free(Devices);

	}

	free(Platforms);
}

void OpenCLPlugin::ShutdownModule() {}
