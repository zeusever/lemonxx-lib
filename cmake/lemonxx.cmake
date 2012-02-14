lemon_option(
  LEMON_MPL_MAX_ARGS
  DEFAULT 8
  VALUES 8 16 32 64
  DESCRIPTION "the mpl library max template args"
  )

function(lemonxx_ctg_files OUTPUT)
  lemon_scan_files(FILES "Source Files" ${CMAKE_CURRENT_SOURCE_DIR} PATTERNS  *.ctg)

  set(COMPILER ${PROJECT_SOURCE_DIR}/sources/lemonxx/cmake/compiler.lua)

  foreach(FILE ${FILES})
    file(RELATIVE_PATH PATH ${PROJECT_SOURCE_DIR}/sources/lemonxx/ ${FILE})
    set(PATH ${PROJECT_BINARY_DIR}/build/sources/lemonxx/${PATH})
    string(REPLACE ".ctg" "" PATH ${PATH})
    get_filename_component(NAME ${PATH} NAME)
    string(REPLACE "${NAME}" "" DIR ${PATH})
    if(NOT EXISTS ${DIR})
      file(MAKE_DIRECTORY ${DIR})
    endif()
    lemon_file_source_group("Include Files" ${PROJECT_BINARY_DIR}/build/sources/lemonxx ${PATH})
    
    add_custom_command(
      OUTPUT ${PATH}
      COMMAND ${LEMON_LUA} ${COMPILER} ${FILE} ${PATH} ${LEMON_MPL_MAX_ARGS}
      DEPENDS ${FILE} ${COMPILER}
      COMMENT "run ctg info compiler ...")
    list(APPEND CTG_FILES ${PATH} ${FILE})
  endforeach()

  set(${OUTPUT} ${CTG_FILES} PARENT_SCOPE)

endfunction()