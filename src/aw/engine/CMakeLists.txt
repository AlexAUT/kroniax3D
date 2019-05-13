add_subdirectory(stateMachine)
add_subdirectory(window)

add_to_target(awEngine PRIVATE config.cpp)
add_to_target(awEngine PRIVATE engine.cpp)
