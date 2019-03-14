cmake_minimum_required(VERSION 3.0)
project(hotplate)

# Static library
add_library(hotplate_static STATIC 
	src/hotplate_static/hotplate.cpp
	src/hotplate_static/include/hotplate/hotplate.h)
target_include_directories(hotplate_static
	PUBLIC src/hotplate_static/include)
target_compile_features(hotplate_static
	PUBLIC cxx_strong_enums
	       cxx_noexcept)

# Executable app
add_executable(hotplate_app
	src/hotplate_app/main.cpp)
target_link_libraries(hotplate_app
	PRIVATE hotplate_static)
