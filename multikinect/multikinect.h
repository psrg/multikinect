#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MULTIKINECT_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MULTIKINECT_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MULTIKINECT_EXPORTS
#define MULTIKINECT_API __declspec(dllexport)
#else
#define MULTIKINECT_API __declspec(dllimport)
#endif

#include "stdafx.h"

using namespace std;
using namespace libfreenect2;

// This class is exported from the multikinect.dll
class MULTIKINECT_API MultiKinect {
public:
	MultiKinect(void);
	void Open();
	void Start();
	bool WaitForNextFrames();
	int GetNumDevices();
	FrameMap** GetFrames();
};

class MULTIKINECT_API FrameSet {
public:
	Frame* Rgb;
	Frame* Depth;
	Frame* Ir;
};