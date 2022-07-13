#!/bin/sh

BUILD_DIR="Build"

DO_CLEAN="false"
DO_TEST="false"
RELEASE=""

if [ "$#" -lt 1 ]; then
    echo 
    echo "Usage $0 [clean][debug|release][test]"
    echo 
    exit 1
fi

while [ -n "$1" ]; do 
    case "$1" in
       clean)
          DO_CLEAN="true"
          ;;
       debug)
          RELEASE="Debug"
          ;;
       release)
          RELEASE="Release"
          echo "Releas is not supported"          
          exit 1
          ;;
       test)
          DO_TEST="true"
          ;;
       *)
          echo 
          echo "Option $1 not recognized."
          echo 
          exit 1
          ;;
     esac
     shift
done      

if [ "$DO_CLEAN" = "true" ]; then
    echo "Cleaning build directory..."
    if [ -d "$BUILD_DIR" ]; then
      cd "$BUILD_DIR"
      if [ -f "install_manifest.txt" ]; then
         xargs rm < install_manifest.txt
      fi   
      make clean
      cd ..
    fi  
      rm -rf "$BUILD_DIR"  
fi      

if [ -n "$RELEASE" ]; then
      mkdir -p "$BUILD_DIR"
      cd "$BUILD_DIR"
      cmake .. -DCMAKE_INSTALL_PREFIX=.. -DCMAKE_BUILD_TYPE=$RELEASE -DBLD_DIR=$BUILD_DIR
      make -j $NPROC
      make install
fi      

if [ "$DO_TEST" = "true" ]; then
  echo "Running Tests..."
  cd ..
  python tests/tests.py -b $BUILD_DIR
fi
