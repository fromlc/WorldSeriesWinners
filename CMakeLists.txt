# CMakeList.txt : CMake project for WorldSeriesWinners, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("WorldSeriesWinners")

# Add source to this project's executable.
add_executable ("WorldSeriesWinners" "source/WorldSeriesWinners.cpp" "source/file_read.cpp")

# TODO: Add tests and install targets if needed.
# install (TARGETS WorldSeriesWinners DESTINATION bin)
