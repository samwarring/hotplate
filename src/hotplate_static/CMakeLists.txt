add_library(
    hotplate_static STATIC
    hotplate.cpp
)

target_include_directories(
    hotplate_static
    PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
           $<INSTALL_INTERFACE:include>
)

target_compile_features(
    hotplate_static
    PUBLIC cxx_strong_enums
           cxx_noexcept
)
