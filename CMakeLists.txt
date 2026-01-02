cmake_minimum_required(VERSION 3.16)
project(ACMCode)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3")

file(GLOB_RECURSE files
        CONFIGURE_DEPENDS
        *.cpp
)

foreach(file ${files})
    file(RELATIVE_PATH rel "${CMAKE_CURRENT_SOURCE_DIR}" "${file}")
    string(REPLACE "/" "-" exe "${rel}")
    string(REGEX REPLACE "\\.cpp$" "" exe "${exe}")
    add_executable(${exe} ${file})
endforeach()
