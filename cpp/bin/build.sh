#!/bin/bash
# ------------------------
# 编译工程
# bin/build.sh
# ------------------------

BASE_DIR=`pwd`
BUILD_DIR="./build"
BUILD_TYPE="Release"

cd ${BUILD_DIR}
rm -rf *
touch .keep

cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
make

cd ${BASE_DIR}
echo "Done."
