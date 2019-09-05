#! /bin/bash
set -ex

if [ "$TRAVIS_BRANCH" = "master" ] && [ "$TRAVIS_OS_NAME" = "linux" ] && [ "$CONFIG" = "RelWithDebInfo" ]; then
    doxygen docs/Doxyfile
fi
