add_library(
    hotplate_lib
    hotplate.cpp
)

target_include_directories(
    hotplate_lib
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
           $<INSTALL_INTERFACE:include>
)

target_compile_features(
    hotplate_lib
    PUBLIC cxx_strong_enums
           cxx_noexcept
)
