#----------------------------------------------------------------------------
# Set The Name of Main.cc
set(Name "CrystalEyeTool")

# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(${Name})
#----------------------------------------------------------------------------
find_package(ROOT REQUIRED)

# Locate sources and headers for this project
include(${ROOT_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include ${ROOT_INCLUDE_DIR})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_library(${Name} SHARED ${sources} ${headers}) # dylib
#add_library(${Name} MODULE ${sources} ${headers})  #solib 
target_link_libraries(${Name} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#install(TARGETS ${Name} DESTINATION bin)


