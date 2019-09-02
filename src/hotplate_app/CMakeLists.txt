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
