CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_STANDARD 11)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(progname ${Boost_LIBRARIES})
endif()

ADD_EXECUTABLE(rshell

    src/main.cpp
    src/and.cpp
    src/or.cpp
    src/semi.cpp
    src/shell.cpp
    src/end.cpp
    src/parentheses.cpp
    src/piping.cpp

)

ADD_SUBDIRECTORY(googletest)

Add_EXECUTABLE(test
    tests/connectorTests.cpp
    src/and.cpp
    src/or.cpp
    src/semi.cpp
    src/shell.cpp
    src/end.cpp
    src/parentheses.cpp
    src/piping.cpp
)



TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
