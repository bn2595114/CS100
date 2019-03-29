
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_STANDARD 11)
SET(Boost_USE_STATIC_LUBS OFF)
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME OFF)
FIND_PACKAGE(BOOST 1.45.0 COMPONENTS)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(progname ${Boost_LIBRARIES})
endif()

ADD_EXECUTABLE(rshell
    main.cpp
    shell.cpp
    and.cpp
    or.cpp
    semi.cpp
    end.cpp
)
