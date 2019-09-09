cmake_minimum_required(VERSION 3.2)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(editor VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(editor VERSION 0.0.1)
endif()

find_package(Threads REQUIRED)
find_package(GTest   REQUIRED)
find_package(Boost   REQUIRED)

add_executable(editor       sources/main.cpp)
add_executable(editor_gtest tests/editor_gtest.cpp)

set_target_properties(editor PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(editor_gtest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/sources
)

target_link_libraries(editor_gtest
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

if (MSVC)
    target_compile_options(editor PRIVATE
        /W4 -O3
    )
    target_compile_options(editor_gtest PRIVATE
        /W4 -O3
    )
else ()
    target_compile_options(editor PRIVATE
        -Wall -Wextra -pedantic -Werror -O3
    )
    target_compile_options(editor_gtest PRIVATE
        -Wall -Wextra -pedantic -Werror -O3
    )
endif()

install(TARGETS editor RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT alexpoligon@mail.ru)

include(CPack)

enable_testing()

add_test(editor_gtest editor_gtest)

add_custom_command(
    TARGET editor_gtest
    POST_BUILD 
    COMMAND ./editor_gtest
    COMMENT "Run test..."
)

find_package(Doxygen)
set(DOXYGEN_IN  ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxyfile.in)
set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/doxyfile)
configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

add_custom_target( doc_doxygen
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generate documentation..."
)
