cmake_minimum_required(VERSION 3.17)
add_definitions(-std=c++11)
set(CXX_FLAGS "-Wall -lpython3.6")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(MCL)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_BUILD_TYPE Debug)

find_package(Python3 COMPONENTS Development NumPy)

message("Python_FOUND:${Python3_FOUND}")
message("Python_VERSION:${Python3_VERSION}")
message("Python_Development_FOUND:${Python3_Development_FOUND}")
message("Python_LIBRARIES:${Python3_LIBRARIES}")
message("Python_NumPy:${Python3_NumPy_FOUND}")

include_directories(${python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS} /usr/local/lib/python3.7/dist-packages/numpy/core/include)
include_directories("${PROJECT_SOURCE_DIR}/include/")

# Find all executables
file(GLOB project_SRCS src/*.cpp) #src/*.h

# Add project executable
add_executable(MCL ${project_SRCS})
target_link_libraries(MCL ${Phyton_LIBRARIES} PUBLIC Python3::NumPy)
target_include_directories(MCL PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})
