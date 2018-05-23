cmake_minimum_required(VERSION 2.8)

project(SystemE)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

include_directories("${PROJECT_SOURCE_DIR}/include")
file(GLOB SOURCES "src/*.cpp")

add_executable(systemE ${SOURCES})

find_package(Threads REQUIRED)
find_package(SFML 2 REQUIRED network audio graphics window system)
find_package(Readline REQUIRED)
find_package(Lua REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
    target_compile_options(systemE PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(systemE "${CMAKE_THREAD_LIBS_INIT}")
endif()

if(SFML_FOUND)
    # include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(systemE -lsfml-graphics -lsfml-window -lsfml-system)
endif()

if(LUA_FOUND)
    target_link_libraries(systemE -llua)
    if(LUA_VERSION_MINOR EQUAL "3")
        target_compile_options(systemE PUBLIC "-D_LUA_5_3")
    elseif(LUA_VERSION_MINOR EQUAL "2")
        target_compile_options(systemE PUBLIC "-D_LUA_5_2")
    elseif(LUA_VERSION_MINOR EQUAL "1")
        target_compile_options(systemE PUBLIC "-D_LUA_5_1")
    endif()
endif()

if(READLINE_FOUND)
    target_link_libraries(systemE -lreadline)
endif()

target_compile_options(systemE PUBLIC "-I include/nlohmann")

