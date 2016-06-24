// multikinect-demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "multikinect.h"
#include <iostream>
#include "viewer.h"
int main()
{
	Viewer viewer;
	viewer.initialize();


	MultiKinect multikinect;
	
	int numDevices = multikinect.GetNumDevices();
	
	multikinect.Open();
	multikinect.Start();


	if (multikinect.WaitForNextFrames())
	{

	}
	system("pause");
    return 0;
}

