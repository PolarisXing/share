aux_source_directory(. SRC_SOURCE)


# add_definitions(-DUNICODE -D_UNICODE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -municode")
add_compile_definitions(UNICODE)
add_compile_definitions(_UNICODE)
add_compile_definitions(_AMD64_)

add_executable(${PROJECT_NAME} ${SRC_SOURCE})

# add_link_options(-municode)
