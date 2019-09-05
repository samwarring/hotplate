add_executable(
    hotplate_boost_test
    main.cpp
    hotplate_boost_test.cpp
    substance_boost_test.cpp
    build_info_boost_test.cpp
)

target_link_libraries(
    hotplate_boost_test
    PRIVATE build_info
            hotplate_lib
            Boost::unit_test_framework
)

if(NOT ${Boost_USE_STATIC_LIBS})

    target_compile_definitions(
        hotplate_boost_test
        PRIVATE BOOST_TEST_DYN_LINK=1
    )

endif()

add_test(
    NAME hotplate_boost_test
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/hotplate_boost_test
)
