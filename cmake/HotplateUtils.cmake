# Usage: add_test_path(TEST <test> TARGETS <target>...)
#
# Adds each <target>'s output directory to the PATH environment variable
# when running <test>.
function(add_test_path)

    # Parse function arguments
    cmake_parse_arguments(ADD_TEST_PATH "" TEST TARGETS ${ARGV})

    # Build the new PATH list
    set(TEMP_PATH)
    foreach(TGT IN LISTS ADD_TEST_PATH_TARGETS)
        list(APPEND TEMP_PATH "$<TARGET_FILE_DIR:${TGT}>")
    endforeach()
    list(APPEND TEMP_PATH "$ENV{PATH}")

    # Use correct path separator (';' on Windows, ':' on UNIX)
    if(UNIX)
        string(REPLACE ";" ":" TEMP_PATH "${TEMP_PATH}")
    else()
        string(REPLACE ";" "\;" TEMP_PATH "${TEMP_PATH}")
    endif()

    # Set the test property
    set_tests_properties(
        ${ADD_TEST_PATH_TEST}
        PROPERTIES ENVIRONMENT "PATH=${TEMP_PATH}"
    )

endfunction()
