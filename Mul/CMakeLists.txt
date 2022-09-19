project(Mmul)

# set (CMAKE_C_COMPILER "/home/mumu/SomeSoft/intel/oneapi/compiler/2022.1.0/linux/bin/intel64/icc")
# set (CMAKE_CXX_COMPILER "/home/mumu/SomeSoft/intel/oneapi/compiler/2022.1.0/linux/bin/intel64/icpc")
set (CMAKE_C_COMPILER "icc")
set (CMAKE_CXX_COMPILER "icpc")

set(EXECUTABLE_OUTPUT_PATH ./run)

# SET(INC_DIR /usr/local/include)
# SET(LINK_DIR /usr/local/lib)

SET(INC_DIR ./lib)
SET(LINK_DIR ./lib)

include_directories(${INC_DIR})
link_directories(${LINK_DIR})
# link_libraries(glog)

set(CMAKE_CXX_FLAGS "-align -qopt-prefetch=3 -qopt-prefetch-distance=16,0")

add_executable(run-baseline bulk.cpp algo-baseline.cpp)
add_executable(run-blocked bulk.cpp algo-blocked.cpp)
target_link_libraries(run-baseline glog)
target_link_libraries(run-blocked glog)