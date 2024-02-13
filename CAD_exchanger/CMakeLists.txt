cmake_minimum_required(VERSION 3.5)

project(job_test)

add_executable(test 
    main.cpp
)

set_target_properties(test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

foreach(target ${TARGETS})
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
        CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${target} PRIVATE 
            -g
            -Wall
            -Wextra
            -Werror
            -Wno-unused-parameter
            -pedantic
        )
        target_link_libraries(${target} PUBLIC Threads::Threads)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${target} PRIVATE
            /EHsc
            /W4
            /WX
        )
    endif()
    target_compile_features(${target} PUBLIC cxx_std_17)
endforeach(target IN ${TARGETS})

