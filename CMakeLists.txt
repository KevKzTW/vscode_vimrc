cmake_minimum_required(VERSION 2.8)

add_executable(read_vimrc src/main.c)
target_link_libraries(read_vimrc json-c)
