cmake_minimum_required(VERSION 2.6)
project(Ribbon)

include(CTest)
enable_testing()

add_subdirectory(test)

set(PROJECT_INCLUDE_DIR "include")
include_directories("${PROJECT_INCLUDE_DIR}")


set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")


file(GLOB_RECURSE ribbon_files
       "src/*.cpp"
       "src/*.h")

add_library("ribbon" ${ribbon_files})

add_test("main_test" ${EXECUTABLE_OUTPUT_PATH}/foobar)