# This is the cmake file. It describes how to build our app
# The documentation for how to build these can be found here:
# http://www.cmake.org/cmake/help/cmake-2-8-docs.html

# CMake likes us to put this here in case someone tries to read this file with an older version of cmake
cmake_minimum_required(VERSION 2.8) # http://www.cmake.org/cmake/help/cmake-2-8-docs.html#command:cmake_minimum_required

# Sets the name of the project. Additionally this sets the variables <projectName>_BINARY_DIR and <projectName>_SOURCE_DIR to the respective values.
project ("ElladanHelper") # http://www.cmake.org/cmake/help/cmake-2-8-docs.html#command:project

file(GLOB_RECURSE source "src/*.cpp")
file(GLOB_RECURSE header "src/*.h")

#set(CMAKE_CXX_FLAGS "-std=c++14 -Wshadow-compatible-local -fsanitize=address -fuse-ld=gold")
#set(CMAKE_CXX_FLAGS "-std=c++14 -Wshadow-compatible-local") #-fsanitize=address -fuse-ld=gold")
set(CMAKE_CXX_FLAGS "-std=c++14 -Wshadow") #-fsanitize=address -fuse-ld=gold")
SET_SOURCE_FILES_PROPERTIES( ${source} ${header} PROPERTIES LANGUAGE CXX )
add_library(ElladanHelper STATIC ${source} )

# Export header
install(DIRECTORY src/ DESTINATION include/elladan
        FILES_MATCHING PATTERN "*.h")
install(TARGETS ElladanHelper ARCHIVE DESTINATION lib)

message(status "cmake version " ${CMAKE_C_COMPILER_VERSION})


enable_testing()

add_executable(randomTest test/RandomTest.cpp)
target_link_libraries(randomTest ElladanHelper)
add_test(randomTest randomTest)

add_executable(uuidTest test/UUIDTest.cpp)
target_link_libraries(uuidTest ElladanHelper)
add_test(uuidTest uuidTest)

add_executable(setTest test/SetTest.cpp)
target_link_libraries(setTest ElladanHelper)
add_test(setTest setTest)

add_executable(stringifyTest test/StringifyTest.cpp)
target_link_libraries(stringifyTest ElladanHelper)
add_test(stringifyTest stringifyTest)

add_executable(folderTest test/FolderManipTest.cpp)
target_link_libraries(folderTest ElladanHelper)
add_test(folderTest folderTest)

add_executable(bitTest test/BitTest.cpp)
target_link_libraries(bitTest ElladanHelper)
add_test(bitTest bitTest)

add_executable(vmapTest test/VMapTest.cpp)
target_link_libraries(vmapTest ElladanHelper)
add_test(vmapTest vmapTest)
