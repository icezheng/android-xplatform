cmake_minimum_required(VERSION 3.2)
project(xPlatform)

find_package(boost)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(generated-srcs/cpp)
include_directories(src)

set(SOURCE_FILES
    src/user_profile_service_impl.cc)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_library(FloCommon STATIC ${SOURCE_FILES})