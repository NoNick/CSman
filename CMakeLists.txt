cmake_minimum_required(VERSION 2.8)
project (CSman)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fopenmp")
#set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fopenmp")

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS program_options) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(CSman draw.cpp draw.h gamecontroller.cpp gamecontroller.h keys.cpp levelmap.cpp levelmap.h main.cpp mapBlock.cpp mapBlock.h pellet.cpp pellet.h player.cpp player.h state.cpp state.h status.cpp status.h texture.cpp texture.h) 
    target_link_libraries(CSman ${Boost_LIBRARIES})
endif()
