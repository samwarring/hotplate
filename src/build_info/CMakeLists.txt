# Write build version information to a header file, and create
# an interface target for it to be used by other targets.

configure_file(
    build_info.h.in
    include/hotplate/build_info.h
)

add_library(
    build_info INTERFACE
)

target_include_directories(
    build_info
    INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/include
)