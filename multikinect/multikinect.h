#pragma once

#ifdef MULTIKINECT_EXPORTS
#define MULTIKINECT_API __declspec(dllexport)
#else
#define MULTIKINECT_API __declspec(dllimport)
#endif

#include "stdafx.h"

using namespace std;
using namespace libfreenect2;

class MULTIKINECT_API FrameSet {
public:
	Frame* Rgb;
	Frame* Depth;
	Frame* Ir;
};

// This class is exported from the multikinect.dll
class MULTIKINECT_API MultiKinect {
public:
	MultiKinect(void);

	/// <summary>
	/// Opens all devices to prepare for capture.
	/// </summary>
	void Open();

	/// <summary>
	/// Start capturing frame data. Implicitly calls Open() automatically.
	/// </summary>
	void Start();

	/// <summary>
	/// Blocks execution until the next set of frames arrive, or times out. Implicitly Start()s the stream if not already done.
	/// </summary>
	/// <returns>"true" if a set of frames has arrived; "false" if a timeout from any device occurs.</returns>
	bool WaitForNextFrames();

	/// <summary>
	/// Gets the number of devices attached to the computer on initialization.
	/// </summary>
	/// <returns>The number of devices</returns>
	int GetNumDevices();

	/// <summary>
	/// Gets a reference to the frame map
	/// </summary>
	/// <returns></returns>
	FrameSet* GetFrames();

	/// <summary>
	/// Releases frames from memory.
	/// </summary>
	void ReleaseFrames();

	/// <summary>
	/// Stops capturing data.
	/// </summary>
	void Stop();

	/// <summary>
	/// Close devices. This method will automatically stop() devices if not already done.
	/// </summary>
	void Close();

	/// <summary>
	/// Tests whether the streams have started
	/// </summary>
	/// <returns>"true" if started, "false" otherwise</returns>
	bool IsStarted();

	/// <summary>
	/// Tests whether the devices are open.
	/// </summary>
	/// <returns>"true" if the devices are open.</returns>
	bool IsOpen();

private:
	bool isStarted = false;
	bool isOpen = false;
	int numDevices = 0;
	Freenect2 *freenect2;
	SyncMultiFrameListener** listenerList;
	Freenect2Device** deviceList;
	FrameMap* frameMapList;
	FrameSet* frameSetList;
	
};
