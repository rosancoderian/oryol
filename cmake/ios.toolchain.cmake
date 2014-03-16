#-------------------------------------------------------------------------------
#	ios.toolchain.cmake
#	Oryol cmake toolchain file for cross-compiling to iOS from OSX.
#	(C) 2013 A.Weissflog
#-------------------------------------------------------------------------------

message("Target Platform: iOS")

set(ORYOL_PLATFORM IOS)
set(ORYOL_PLATFORM_NAME "ios")
set(ORYOL_IOS 1)
set(ORYOL_OSX 1)
set(ORYOL_POSIX 1)
set(ORYOL_OPENGL 1)
set(ORYOL_OPENGLES2 1)
set(ORYOL_PLATFORM_DEFINES " -DORYOL_IOS=1 -DORYOL_OSX=1 -DORYOL_POSIX=1)

# disable compiler detection
include(CMakeForceCompiler)
CMAKE_FORCE_C_COMPILER(gcc GNU)
CMAKE_FORCE_CXX_COMPILER(g++ GNU)

# Do a no-op access on the CMAKE_TOOLCHAIN_FILE variable so that CMake will not issue a warning on it being unused.
if (CMAKE_TOOLCHAIN_FILE)
endif()

# define configuration types
set(CMAKE_CONFIGURATION_TYPES Debug Release)

# compiler flags
set(CMAKE_CXX_FLAGS "${ORYOL_PLATFORM_DEFINES} -fno-exceptions -fstrict-aliasing -Wno-multichar -Wall -Wextra -Wno-unused-parameter -Wno-unknown-pragmas -Wno-ignored-qualifiers -Wno-long-long -Wno-overloaded-virtual -Wno-unused-volatile-lvalue -Wno-deprecated-writable-strings")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -msse3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -D_DEBUG_ -D_DEBUG -DORYOL_DEBUG=1 -ggdb")

set(CMAKE_C_FLAGS "${ORYOL_PLATFORM_DEFINES} -fstrict-aliasing -Wno-multichar -Wall -Wextra -Wno-unused-parameter -Wno-unknown-pragmas -Wno-ignored-qualifiers -Wno-long-long -Wno-overloaded-virtual -Wno-unused-volatile-lvalue  -Wno-deprecated-writable-strings")
set(CMAKE_C_FLAGS_RELEASE "-O3 -msse3 -DNDEBUG")
set(CMAKE_C_FLAGS_DEBUG "-O0 -D_DEBUG_ -D_DEBUG -g -DORYOL_DEBUG=1")

set(CMAKE_EXE_LINKER_FLAGS "-ObjC -dead_strip -lstdc++ -lpthread")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "")

# update cache variables for cmake gui
set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "Config Type" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "Generic C++ Compiler Flags" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "C++ Debug Compiler Flags" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "C++ Release Compiler Flags" FORCE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "Generic C Compiler Flags" FORCE)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}" CACHE STRING "C Debug Compiler Flags" FORCE)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "C Release Compiler Flags" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}" CACHE STRING "Generic Linker Flags" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING "Debug Linker Flags" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" CACHE STRING "Release Linker Flags" FORCE)

# set the build type to use
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Compile Type" FORCE)
endif()
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release)

