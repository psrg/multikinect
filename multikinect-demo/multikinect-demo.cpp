#include "stdafx.h"
#include "multikinect.h"
#include <iostream>
#include <conio.h>
#include "viewer.h"
#include "multikinect-demo.h"

int main(int argc, char *argv[])
{
	MultiKinect multikinect;

	Viewer viewer;
	viewer.initialize();

	while (!kbhit())
	{
		if (multikinect.WaitForNextFrames())
		{
			viewer.addFrame("depth1", multikinect.GetFrames()[0].Depth);
			viewer.addFrame("depth2", multikinect.GetFrames()[1].Depth);
			viewer.addFrame("RGB1", multikinect.GetFrames()[0].Rgb);
			viewer.addFrame("RGB2", multikinect.GetFrames()[1].Rgb);
			viewer.render();
		}
		multikinect.ReleaseFrames();

	}

	multikinect.Close();

    return 0;
}

