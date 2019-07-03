cmake_minimum_required(VERSION 3.7.2)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17) # C++17...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

#
# Set our project name
#
project(parseRGB_test)

#
# Source files
#
set(parseRGB_test_src
    test.cpp
)

#
# find libraries and include
#

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/iutest/cmake)
message(STATUS "${CMAKE_MODULE_PATH}")
set(iutest_DIR ${CMAKE_SOURCE_DIR}/iutest/cmake)
set(IUTEST_ROOT_DIR ${CMAKE_SOURCE_DIR}/iutest)
find_package(iutest)
include_directories(${IUTEST_INCLUDE_DIR})

#
# Update compiler waring flags
#
if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-long-long -pedantic")
endif()

#
# Compile
#
add_executable(parseRGB_test ${parseRGB_test_src})

#
# Link
#
target_link_libraries(parseRGB_test parseRGB)
if(WIN32)
    target_link_libraries(parseRGB_test ws2_32)
endif()

add_custom_target(run_test
    COMMAND parseRGB_test
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    DEPENDS parseRGB_test
    COMMENT "Execute produced executable."
)