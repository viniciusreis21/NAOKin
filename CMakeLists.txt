cmake_minimum_required(VERSION 2.6.4)
project(naoKin)
find_package(qibuild)



qi_create_bin(naoKin main.cpp src/external/Kofinas/NAOKinematics.cpp src/external/Kofinas/NAOKinematicsJacobian.cpp src/NAOKin.cpp src/Timer.cpp)
qi_use_lib(naoKin OPENCV2_CORE OPENCV2_HIGHGUI ALCOMMON ALPROXIES)

target_link_libraries(naoKin ${OpenCV_LIBS})
include_directories(".")
include_directories( ${OpenCV_INCLUDE_DIRS} )