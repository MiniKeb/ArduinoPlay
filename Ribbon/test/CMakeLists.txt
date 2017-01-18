cmake_minimum_required(VERSION 2.6)
 
file(GLOB tests "*.cpp")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

foreach(test_filename ${tests})
	get_filename_component(test ${test_filename} NAME_WE)
 
	add_executable(${test} ${test_filename})
	target_link_libraries(${test} ribbon) 
endforeach()