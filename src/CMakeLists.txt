add_executable(humantraffic "main.cpp" ${SOURCES})
target_link_libraries(
    humantraffic
    logger
    tinyxml
    ${OpenCV_LIBS}
    ${POCO_FOUNDATION}
    pthread
)
