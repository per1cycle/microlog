add_executable(SingleHeaderTest SingleHeaderTest.cc)

target_include_directories(SingleHeaderTest PRIVATE ${CMAKE_SOURCE_DIR}/release)
