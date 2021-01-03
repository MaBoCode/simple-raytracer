cmake_minimum_required(VERSION 3.13)

project(simple_raytracer C)

set(DEBUG_FLAGS "-g;-fsanitize=address")

file(GLOB_RECURSE INCLUDE_FILES "src/*.h")
set(INCLUDE_DIRS "")
FOREACH(file_path ${INCLUDE_FILES})
    get_filename_component(dir_path ${file_path} PATH)
    SET(INCLUDE_DIRS ${INCLUDE_DIRS} ${dir_path})
ENDFOREACH()
LIST(REMOVE_DUPLICATES INCLUDE_DIRS)

include_directories(${INCLUDE_DIRS})

file(GLOB_RECURSE SRC_FILES "src/*.c")

add_executable(raytracer-debug ${SRC_FILES})
target_compile_options(raytracer-debug PUBLIC ${DEBUG_FLAGS})
target_link_options(raytracer-debug PUBLIC ${DEBUG_FLAGS})
target_link_libraries(raytracer-debug m)
add_custom_target(
        debug
        DEPENDS raytracer-debug
)

set_target_properties(raytracer-debug PROPERTIES EXCLUDE_FROM_ALL 1)

add_executable(raytracer ${SRC_FILES})
target_link_libraries(raytracer m)