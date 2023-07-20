cmake_minimum_required(VERSION 3.7)

# set the project name
project(pi86 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_executable(pi86
	#	cga.cpp
	drives.cpp
	pi86.cpp
	timer.cpp
	vga.cpp
	x86.cpp
)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads)
target_link_libraries(pi86 Threads::Threads)

include(FindPkgConfig)

pkg_check_modules(LIBSDL2 sdl2)
target_link_libraries(pi86 ${LIBSDL2_LIBRARIES})
target_include_directories(pi86 PUBLIC ${LIBSDL2_INCLUDE_DIRS})
target_compile_options(pi86 PUBLIC ${LIBSDL2_CFLAGS_OTHER})

target_link_libraries(pi86 -lwiringPi)
