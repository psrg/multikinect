// multikinect-demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "multikinect.h"
#include <iostream>
#include <conio.h>
#include "viewer.h"
#include "multikinect-demo.h"
int main(int argc, char *argv[])
{
	MultiKinect multikinect;

	multikinect.Open();
	multikinect.Start();

	Viewer viewer;
	viewer.initialize();

	while (!kbhit())
	{
		if (multikinect.WaitForNextFrames())
		{
			viewer.addFrame("depth1", multikinect.GetFrames()[0][libfreenect2::Frame::Depth]);
			viewer.addFrame("depth2", multikinect.GetFrames()[1][libfreenect2::Frame::Depth]);
			viewer.addFrame("RGB1", multikinect.GetFrames()[0][libfreenect2::Frame::Color]);
			viewer.addFrame("RGB2", multikinect.GetFrames()[1][libfreenect2::Frame::Color]);
			viewer.render();
			multikinect.ReleaseFrames();
		}
	}

	multikinect.Stop();
	multikinect.Close();

    return 0;
}

