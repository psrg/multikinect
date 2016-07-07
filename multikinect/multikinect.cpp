// multikinect.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "multikinect.h"

using namespace libfreenect2;
using namespace std;

MultiKinect::MultiKinect()
{
	freenect2 = new Freenect2();
	setGlobalLogger(createConsoleLogger(Logger::Info));
	numDevices = freenect2->enumerateDevices();

	deviceList = new Freenect2Device*[numDevices];
	listenerList = new SyncMultiFrameListener*[numDevices];
	frameMapList = new FrameMap[numDevices];
	frameSetList = new FrameSet[numDevices];
}

void MultiKinect::Open()
{
	if (isOpen)
		return;
	// walk through the devices and add them
	for (int i = 0; i < numDevices; i++)
	{
		Freenect2Device *dev = freenect2->openDevice(i);
		SyncMultiFrameListener *listener = new SyncMultiFrameListener(Frame::Ir | Frame::Depth | Frame::Color);

		dev->setColorFrameListener(listener);
		dev->setIrAndDepthFrameListener(listener);

		deviceList[i] = dev;
		listenerList[i] = listener;
	}
	isOpen = true;
} 

void MultiKinect::Start()
{
	if (isStarted)
		return;

	Open(); // make sure the devices are open before we start

	for (int i = 0; i < numDevices; i++)
	{
		deviceList[i]->start();
	}
	isStarted = true;
}

bool MultiKinect::WaitForNextFrames()
{
	Start(); // if we're not already started, do so now.
	for (int i = 0; i < numDevices; i++)
	{
		if (!(listenerList[i]->waitForNewFrame(frameMapList[i]), 1000))
			return false;
	}

	return true;
}

int MultiKinect::GetNumDevices()
{
	return numDevices;
}

FrameSet * MultiKinect::GetFrames()
{
	for (int i = 0; i < numDevices; i++)
	{
		frameSetList[i].Depth = frameMapList[i][libfreenect2::Frame::Depth];
		frameSetList[i].Ir = frameMapList[i][libfreenect2::Frame::Ir];
		frameSetList[i].Rgb = frameMapList[i][libfreenect2::Frame::Color];
	}
	return frameSetList;
}

void MultiKinect::ReleaseFrames()
{
	for (int i = 0; i < numDevices; i++)
	{
		listenerList[i]->release(frameMapList[i]);
	}
}

void MultiKinect::Stop()
{
	if (!isStarted)
		return;

	for (int i = 0; i < numDevices; i++)
	{
		deviceList[i]->stop();
	}

	isStarted = false;
}

void MultiKinect::Close()
{
	Stop();

	for (int i = 0; i < numDevices; i++)
	{
		deviceList[i]->close();
	}

	isOpen = false;
}

bool MultiKinect::IsStarted()
{
	return isStarted;
}

bool MultiKinect::IsOpen()
{
	return isOpen;
}
