
file(GLOB TESTS "t_*.cpp")

add_executable(test1 "testMain.cpp" ${SOURCES} ${TESTS})

target_link_libraries(
    test1
    googletest
    pthread
    logger
    tinyxml
    ${OpenCV_LIBS}
)
