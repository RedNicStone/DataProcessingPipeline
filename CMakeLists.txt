cmake_minimum_required(VERSION 3.20)
project(DataProcessingPipeline)

set(CMAKE_CXX_STANDARD 17)

find_package(GNUPLOT)

find_package(Boost 1.40.0 COMPONENTS filesystem system iostreams REQUIRED)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib/gnuplot-iostream")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/rapidcsv)

file(GLOB SRCS *.cpp)
add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} rapidcsv)
