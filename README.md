# multikinect
MultiKinect provides high-level, simulatenous access to multiple Kinect 2 sensors concurrently. Under the hood, it depends on [libfreenect2](https://github.com/OpenKinect/libfreenect2) for actual Kinect library calls.

## Requirements
This is tested on Visual Studio 2015 U3 on Windows 10 1511. Follow instructions to make libfreenect2, and then change Visual Studio project options with the proper lib / inc directories (which depend on your environment).
