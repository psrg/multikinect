// multikinect.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "multikinect.h"

using namespace libfreenect2;
using namespace std;

Freenect2 *freenect2;

SyncMultiFrameListener** listenerList;
Freenect2Device** deviceList;
FrameMap** frameList;

int numDevices;

// This is the constructor of a class that has been exported.
// see multikinect.h for the class definition
MultiKinect::MultiKinect()
{

	freenect2 = new Freenect2();
	setGlobalLogger(createConsoleLogger(Logger::Info));
	numDevices = freenect2->enumerateDevices();
}

void MultiKinect::Open()
{
	deviceList = new Freenect2Device*[numDevices];
	listenerList = new SyncMultiFrameListener*[numDevices];
	frameList = new FrameMap*[numDevices];


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
}

void MultiKinect::Start()
{

}

bool MultiKinect::WaitForNextFrames()
{
	int numFramesReceived = 0;
	while (numFramesReceived < numDevices)
	{
		for (int i = 0; i < numDevices; i++)
		{
			numFramesReceived += listenerList[i]->hasNewFrame();
		}
	}
	
	return true;
}

int MultiKinect::GetNumDevices()
{
	return numDevices;
}

FrameMap ** MultiKinect::GetFrames()
{
	return frameList;
}