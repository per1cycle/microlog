add_executable(info InfoTest.cc)
target_link_libraries(info Log)
add_executable(example example.cc)
target_link_libraries(example Log)