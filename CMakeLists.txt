cmake_minimum_required(VERSION 3.9)

project(rtFiltering)

# Set compile version
set(CMAKE_CXX_STANDARD 11)

add_executable(imgDisplay ./src/imgDisplay.cpp)
add_executable(vidDisplay ./src/util.cpp ./src/filter.cpp ./src/vidDisplay.cpp)

find_package(OpenCV REQUIRED)
target_link_libraries(imgDisplay ${OpenCV_LIBRARIES})
target_link_libraries(vidDisplay ${OpenCV_LIBRARIES})