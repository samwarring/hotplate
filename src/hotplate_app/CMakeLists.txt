add_executable(
    hotplate_app
    main.cpp
)

target_link_libraries(
    hotplate_app
    PRIVATE hotplate_static
            Boost::program_options
            build_info
)

add_test(
    NAME hotplate_app
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/hotplate_app
)
