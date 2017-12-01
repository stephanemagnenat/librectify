cmake_minimum_required(VERSION 2.8)

project (librectify)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(OpenCV_SHARED OFF)
find_package(OpenCV REQUIRED COMPONENTS core imgproc)

include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(src)
