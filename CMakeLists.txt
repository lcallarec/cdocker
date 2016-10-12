cmake_minimum_required(VERSION 3.2)
project(cdocker)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -lcurl ljson" )

set(SOURCE_FILES
        cdocker.c
        cdocker.h
        cdocker_model.h
        cdocker_model.c
)

add_library(cdocker SHARED ${SOURCE_FILES})
target_link_libraries(cdocker curl json)