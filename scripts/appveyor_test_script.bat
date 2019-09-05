echo ON

@set "PATH=%PATH%;C:\Libraries\boost_1_69_0\lib64-msvc-14.0"

ctest -C %CONFIGURATION% --verbose
