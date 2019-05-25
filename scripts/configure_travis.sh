if [ -z $1 ]; then
    echo "Usage: $0 [ROOT_DIR]"
    exit 1
fi

if [ ! -f vcpkg/vcpkg ]; then
    # Vcpkg is not cached. Let's install it :)
    git clone https://github.com/microsoft/vcpkg.git
    cd vcpkg
    ./bootstrap-vcpkg.sh
else
    echo "Vcpkg already installed"
    cd vcpkg
fi

./vcpkg install boost-test boost-program-options
cd ..

export CMAKE=`find vcpkg/downloads/tools -name cmake | grep bin/cmake`
$CMAKE $1 -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake\
          -DCMAKE_BUILD_TYPE=$CONFIG\
          -Dhotplate_VERSION=0.1.0\
          -Dhotplate_COMMIT=$TRAVIS_COMMIT\
          -Dhotplate_CI_SERVICE=travis\
          -Dhotplate_CI_BUILD_NUMBER=$TRAVIS_BUILD_NUMBER\
          -DBoost_USE_STATIC_LIBS=ON
