CXX=clang++
CXXFLAGS="-Wall -Werror -g `llvm-config --cxxflags`"
LDFLAGS="`llvm-config --ldflags` `llvm-config --libs`"
