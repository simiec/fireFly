cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(fireFly)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

set(BOX2D_INCLUDE_DIR "~/Downloads/Box2D_v2.3.0/Box2D/")
set(BOX2D_LIBRARY "/home/ugurcan/Downloads/Box2D_v2.3.0/Box2D/Build/Box2D/libBox2D.a")

# Add the include directories for the compiler
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${BOX2D_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the executable
add_executable(fireFly main.cpp ${SOURCES})


# Link the headers
target_include_directories(fireFly PRIVATE ${CMAKE_SOURCE_DIR}/include/impl)

target_link_libraries(fireFly sfml-graphics sfml-audio sfml-window sfml-system ${BOX2D_LIBRARY})
