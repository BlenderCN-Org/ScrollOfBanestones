set(SOURCE
    main.cpp
    Application.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES} glm)