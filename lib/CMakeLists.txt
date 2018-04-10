project(cpp_utils_lib)


set(LIB_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cpp_utils/bytes.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cpp_utils/preprocessor.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cpp_utils/range.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cpp_utils/scope.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cpp_utils/stl_utils.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cpp_utils/string.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cpp_utils/vector.hpp
)

add_library(${PROJECT_NAME} INTERFACE)
add_library(cpp_utils::cpp_utils ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_sources(${PROJECT_NAME} INTERFACE ${LIB_HEADERS})
