set(INCLUDE_DIR include)
set(SRC_DIR src)



file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${INCLUDE_DIR}/*.h)


add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SRC_FILES} src/Ball.cpp ${INCLUDE_FILES} src/BallController.cpp )
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})


target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)
target_link_libraries(${PROJECT_NAME} PRIVATE Core)


add_custom_command(
    TARGET Labyrinth POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/shaders
            ${CMAKE_CURRENT_BINARY_DIR}/shaders
)


