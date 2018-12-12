project(cpp_utils)

set(CPPUTILS_SOURCES
    src/stl_utils.cpp
    src/byte.cpp
    )
set(CPPUTILS_INCLUDES
    include/cpp_utils/byte.hpp
    include/cpp_utils/stl_utils.hpp
    )

add_library(${PROJECT_NAME} STATIC EXCLUDE_FROM_ALL ${CPPUTILS_SOURCES} ${CPPUTILS_INCLUDES})
add_library(cpp_utils::cpp_utils ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC include)

if (BUILD_WITH_TESTS)
    add_subdirectory(test)
endif()