project(cpp_utils_utests)

set(UTEST_SOURCES
    main.cpp
    preprocessor.cpp
    scope.cpp
    string.cpp
)

add_executable(${PROJECT_NAME} ${UTEST_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE cpp_utils::cpp_utils)
add_test(NAME ${PROJECT_NAME} COMMAND ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME})

