
# set the project name
set(CMAKE_BUILD_TYPE Debug)
find_package(LibXml2 REQUIRED)

include_directories(${LIBXML2_INCLUDE_DIR} ${TextReader_SOURCE_DIR}/inc)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TextReader_SOURCE_DIR}/bin)
add_library(TextReaderLib STATIC ${TextReader_SOURCE_DIR}/src/Reader.cpp ${TextReader_SOURCE_DIR}/src/ConsoleReader.cpp ${TextReader_SOURCE_DIR}/src/TextFileReader.cpp ${TextReader_SOURCE_DIR}/src/XmlFileReader.cpp)
target_link_libraries(TextReaderLib ${LIBXML2_LIBRARIES})
add_executable(TextReader main.cpp)
target_link_libraries(TextReader TextReaderLib)
target_include_directories (TextReaderLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


