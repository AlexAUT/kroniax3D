function(add_to_target target visibility fileName)
  file(RELATIVE_PATH relPath ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${fileName})
  target_sources(${target} ${visibility}
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/${relPath}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/${relPath}>
  )
endfunction()

