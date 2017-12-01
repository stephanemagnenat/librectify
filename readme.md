This is a C++14 plugin doing rectification for Augmented Creativity apps.

# Dependencies

This library depends on OpenCV 3.2 or later.

# How to compile

## Windows

You need Visual Studio 2017 (with C++ support installed)) and CMake.

There is a mismatch between the version of VC in the pre-built OpenCV libraries and the current version of Visual Studio.
So, first recompile Open CV with Visual Studio 2017.
Compile it static (`BUILD_SHARED_LIBS=OFF`).
Then compile this library, you will need to edit the "Runtime Library" in the "Code Generation Option" of the project to `Multi-threaded (/MT)` instead of the default `Multi-threaded DLL (/MD)` to avoid linking errors with OpenCV.

## Android on Windows

You need Android SDK and NDK, CMake, OpenCV for Android (pre-built package or source, see below).

In the Android SDK component installer (standalone or within Android Studio), install CMake support and the NDK.

### Compiling

In CMake, choose `Ninja` as generator, and set custom toolchain to the location of `android.toolchain.cmake` within the NDK (typically `SDK_LOCATION/ndk-bundle/build/cmake/android.toolchain.cmake`). *Do not choose the one of the SDK*.
Select the `Ninja` binary from the SDK CMake installation (typically in `SDK_LOCATION/cmake/VERSION/bin`).
Set `OpenCV_DIR` to the location of `OpenCVConfig.cmake` in the OpenCV Android kit (typically `OpenCV-android-sdk\sdk\native\jni`).
Configure and generate, and in a command line in the build directory, call the ninja provided by the CMake from the SDK.

### Recompiling OpenCV

The OpenCV kit is linked with a very old version of libstdc++, so if you wish to use modern C++ you need to recompile it with the `c++_static` STL.

Download the sources of OpenCV 3.x, unzip and create a `build_android` directory.
In CMake, choose `Ninja` as generator, and set custom toolchain to the location of `android.toolchain.cmake` within the NDK (typically `SDK_LOCATION/ndk-bundle/build/cmake/android.toolchain.cmake`). *Do not choose the one of the SDK*.
Select the `Ninja` binary from the SDK CMake installation (typically in `SDK_LOCATION/cmake/VERSION/bin`).
Set the variable `ANDROID_STL` to `c++_static`.
Configure and generate, and in a command line in the build directory, call the ninja provided by the CMake from the SDK.

Then, compile `librectify` as above, but also set the variable `ANDROID_STL` to `c++_static`, otherwise you'll have linking problems.