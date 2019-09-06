add_executable(
    hotplate_app
    main.cpp
)

target_link_libraries(
    hotplate_app
    PRIVATE hotplate_lib
            Boost::program_options
            build_info
)

add_test(
    NAME hotplate_app
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/hotplate_app
)

if(BUILD_SHARED_LIBS)

    add_test_path(TEST hotplate_app TARGETS hotplate_lib)

endif()
