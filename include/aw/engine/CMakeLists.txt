add_subdirectory(stateMachine)
add_subdirectory(window)

add_to_target(awEngine PUBLIC config.hpp)
add_to_target(awEngine PUBLIC engine.hpp)
add_to_target(awEngine PUBLIC log.hpp)
