cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(bulk VERSION ${PROJECT_VESRION})

configure_file(include/version.h.in include/version.h)

add_executable(bulk src/main.cpp)
add_executable(bulk_test tests/BulkTest.cpp)

set_target_properties(bulk  PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

target_include_directories(bulk
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(bulk_test PRIVATE ${GTEST_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(bulk_test ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} Threads::Threads)

if(MSVC)
	target_compile_options(bulk PRIVATE /MT)
	target_compile_options(bulk_test PRIVATE /MT)
endif()

install(TARGETS bulk RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT artem-glibkin@yandex.ru)

include(CPack)
enable_testing()

gtest_add_tests(TARGET bulk_test
				TEST_LIST SimpleTest BracketsTest EnclosedBracketsTest
)