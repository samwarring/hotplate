if [ -z $1 ]; then
	echo "Usage: $0 [ROOT_DIR]"
	exit 1
fi

# Create cache directory for travis
mkdir -p travis-cache
mkdir -p travis-cache/stamp

install_cmake() {
	CMAKE_VERSION=3.14.4
	CMAKE_TARBALL=cmake-$CMAKE_VERSION-Linux-x86_64.tar.gz
	CMAKE_SRC_DIR=cmake-$CMAKE_VERSION-Linux-x86_64
	CMAKE_URL="https://github.com/Kitware/CMake/releases/download/v$CMAKE_VERSION/$CMAKE_TARBALL"
	STAMP_PREFIX=travis-cache/stamp/cmake-$CMAKE_VERSION

	# Download
	if [ ! -f $STAMP_PREFIX-downloaded.stamp ]; then
		echo "Downloading CMake $CMAKE_VERSION"
		cd travis-cache
		wget "$CMAKE_URL"
		cd ..
		touch $STAMP_PREFIX-downloaded.stamp
	else
		echo "CMake $CMAKE_VERSION already downloaded"
	fi

	# Extract
	if [ ! -f $STAMP_PREFIX-extracted.stamp ]; then
		echo "Extracting CMake $CMAKE_VERSION"
		pv travis-cache/$CMAKE_TARBALL | tar -xzf - -C travis-cache
		touch $STAMP_PREFIX-extracted.stamp
	else
		echo "CMake $CMAKE_VERSION already extracted"
	fi

	# Add this CMake to the path
	export PATH=`pwd`/travis-cache/$CMAKE_SRC_DIR/bin:$PATH
}

install_boost() {
	BOOST_VERSION_U=1_69_0  # U = Underscores
	BOOST_VERSION_D=1.69.0  # D = Dots
	BOOST_TARBALL=boost_$BOOST_VERSION_U.tar.gz
	BOOST_SRC_DIR=boost_$BOOST_VERSION_U
	BOOST_URL="https://dl.bintray.com/boostorg/release/$BOOST_VERSION_D/source/$BOOST_TARBALL"
	STAMP_PREFIX=travis-cache/stamp/boost-$BOOST_VERSION_D

	# Download
	if [ ! -f $STAMP_PREFIX-downloaded.stamp ]; then
		echo "Downloading Boost $BOOST_VERSION_D"
		cd travis-cache
		wget "$BOOST_URL"
		cd ..
		touch $STAMP_PREFIX-downloaded.stamp
	else
		echo "Boost $BOOST_VERSION_D already downloaded"
	fi

	# Extract
	if [ ! -f $STAMP_PREFIX-extracted.stamp ]; then
		echo "Extracting Boost $BOOST_VERSION_D"
		pv travis-cache/$BOOST_TARBALL | tar -xzf - -C travis-cache
		touch $STAMP_PREFIX-extracted.stamp
	else
		echo "Boost $BOOST_VERSION_D already extracted"
	fi

	# Compile and install
	if [ ! -f $STAMP_PREFIX-compiled.stamp ]; then
		echo "Compiling Boost $BOOST_VERSION_D"
		cd travis-cache/$BOOST_SRC_DIR
		./bootstrap.sh --prefix=../install --with-libraries=test,program_options
		./b2 install -d0 -j2 --layout=system --prefix=../install
		cd ../..
		touch $STAMP_PREFIX-compiled.stamp
	else
		echo "Boost $BOOST_VERSION_D already compiled"
	fi

	# Hint for CMake
	export CMAKE_EXTRA_ARGS="-DBOOST_ROOT=`pwd`/travis-cache/install"
}

# Do OS-specific configuration steps
if [ "$TRAVIS_OS_NAME" = "osx" ]; then
	
	echo "Configuring for OSX in Travis-CI"

elif [ "$TRAVIS_OS_NAME" = "linux" ]; then
	
	echo "Configuring for Linux in Travis-CI"

	# We need to install Boost from source, because the image provided by
	# travis (Ubuntu 16.04) only has boost 1.58 (we require 1.59).
	install_boost

	# We need to install CMake from source, because the version provided
	# by travis (3.5) is too old to provide imported targets from FindBoost.
	install_cmake

else
	
	echo "ERROR: Unkown OS for Travis-CI: $TRAVIS_OS_NAME"
	exit 1

fi

echo "Configuring Hotplate with CMake"
cmake $1 -DCMAKE_BUILD_TYPE=$CONFIG\
         -Dhotplate_COMMIT=$TRAVIS_COMMIT\
         -Dhotplate_CI_SERVICE=travis\
         -Dhotplate_CI_BUILD_NUMBER=$TRAVIS_BUILD_NUMBER\
         -DBoost_USE_STATIC_LIBS=ON\
         $CMAKE_EXTRA_ARGS