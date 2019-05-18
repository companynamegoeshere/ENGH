project(ENGH_TEST CXX)
add_executable(
        engh_test
        main.cpp
)

target_link_libraries(engh_test engh_engine)

