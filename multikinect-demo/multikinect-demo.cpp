// multikinect-demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "multikinect.h"
#include <iostream>
#include "viewer.h"
#include "multikinect-demo.h"
int main(int argc, char *argv[])
{
	MultiKinect multikinect;
	int numDevices = multikinect.GetNumDevices();

	multikinect.Open();
	multikinect.Start();

	Viewer viewer;
	viewer.initialize();

	if (multikinect.WaitForNextFrames())
	{

	}
	system("pause");
    return 0;
}

