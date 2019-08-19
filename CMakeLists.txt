project(naive_parser)

add_definitions(-std=c++11)
include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
add_executable(naive_parser ${SRC_LIST})
