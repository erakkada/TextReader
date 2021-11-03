set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})

include_directories(${LIBXML2_INCLUDE_DIR} ${TextReader_SOURCE_DIR}/inc)

add_executable (TextReaderTests_run ${TextReader_SOURCE_DIR}/test/test_cases/test1.cpp)
target_link_libraries (TextReaderTests_run ${Boost_LIBRARIES} TextReaderLib)



