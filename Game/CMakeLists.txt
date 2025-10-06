set(INCLUDE_DIR include)
set(SRC_DIR src)



file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ${INCLUDE_DIR}/*.h)


add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SRC_FILES} ${INCLUDE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})


target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)
target_link_libraries(${PROJECT_NAME} PRIVATE Core)


