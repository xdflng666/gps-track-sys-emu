#!/bin/sh

BASEDIR=`pwd`

echo $BASEDIR
mkdir out
cd ./out
cmake ..
make -j8
ctest
make ExperimentalCoverage
lcov --directory . -c -o cov.info
lcov --extract cov.info '$BASEDIR/*' -o filtered_cov.info
lcov --remove filtered_cov.info '$BASEDIR/src/HTTPRequest.hpp' -o final.info
genhtml final.info -o out
cp ./out/index.html ../test_coverage.html
firefox ../test_coverage.html
