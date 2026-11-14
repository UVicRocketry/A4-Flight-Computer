cmake_minimum_required(VERSION 3.20)

project(A4FlightComputerTests LANGUAGES C CXX)

include(FetchContent)
include(CTest)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest CONFIG QUIET)

if (NOT GTest_FOUND)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    FetchContent_MakeAvailable(googletest)
endif()

add_executable(flight_fsm_test
    Unit/flight_fsm_test.cpp
    ../App/Services/flight_fsm.c
)

target_include_directories(flight_fsm_test
    PRIVATE
        ../App/Services
)

target_link_libraries(flight_fsm_test
    PRIVATE
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(flight_fsm_test)