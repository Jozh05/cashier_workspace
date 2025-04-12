cmake_minimum_required(VERSION 3.25)
project(workplace LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PATH_TO_INCLUDE_DIRECTORIES ~/vcpkg/installed/x64-linux-dynamic/include)
set(PATH_TO_LINK_DIRECTORIES ~/vcpkg/installed/x64-linux-dynamic/lib)

include_directories(${PATH_TO_INCLUDE_DIRECTORIES})
link_directories(${PATH_TO_LINK_DIRECTORIES})

add_executable(workplace main.cpp ./src/Catalog.cpp ./src/Item.cpp 
./src/Check.cpp ./src/App.cpp ./src/Sellers.cpp ./src/WorkShift.cpp ./src/Config.cpp ./src/Interface.cpp)

target_link_libraries(workplace PRIVATE jsoncpp)