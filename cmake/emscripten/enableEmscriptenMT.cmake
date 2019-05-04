function(enableEmscriptenMT target)
  if(CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    add_definitions(-s USE_PTHREADS=1)
    target_link_libraries(${target} PUBLIC "-s USE_PTHREADS=1")
    target_link_libraries(${target} PUBLIC "-s PTHREAD_POOL_SIZE=1")
    target_link_libraries(${target} PUBLIC "-s PTHREAD_HINT_NUM_CORES=8")
  endif()

endfunction()
