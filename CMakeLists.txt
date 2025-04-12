cmake_minimum_required(VERSION 3.25)
project(workplace)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PATH_TO_LIBS ~/vcpkg/installed/x64-linux-dynamic)

include_directories(${PATH_TO_LIBS}/include)
link_directories(${PATH_TO_LIBS}/lib)

add_executable(workplace main.cpp ./src/Catalog.cpp ./src/Item.cpp 
./src/Check.cpp ./src/App.cpp ./src/Sellers.cpp ./src/WorkShift.cpp ./src/Config.cpp)

target_link_libraries(workplace PRIVATE jsoncpp)