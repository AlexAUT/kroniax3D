function(enableHTMLOutput)
  if(CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
  endif()
endfunction()

