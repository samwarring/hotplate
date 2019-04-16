# The following originated from the below stackoverflow answer:
# https://stackoverflow.com/a/11339392

# Name of the target operating system
set(CMAKE_SYSTEM_NAME Linux)

# Which compilers to use for C and C++
set(CMAKE_C_COMPILER gcc -m32)
set(CMAKE_CXX_COMPILER g++ -m32)

# Where to find x86 boost libraries on x64 linux
set(BOOST_LIBRARYDIR /usr/lib/i386-linux-gnu)
