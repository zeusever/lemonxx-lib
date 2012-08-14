lemon_option(
  LEMON_MPL_MAX_ARGS
  DEFAULT 8
  VALUES 8 16 32 64
  DESCRIPTION "the mpl library max template args"
  )

function(lemonxx_ctg_files OUTPUT)
  lemon_parse_arguments(
    lemon_c_cxx_files
    FILES 
    LEMON_OPTION_ARGS BOOTSTRAP
    LEMON_ONE_VALUE_KEY DIR
    LEMON_INPUT_ARGS ${ARGN})

  lemon_scan_files(FILES "Source Files\\${FILES_DIR}" ${PROJECT_SOURCE_DIR}/sources/lemonxx/ PATTERNS  *.ctg)

  set(COMPILER ${PROJECT_SOURCE_DIR}/sources/lemonxx/cmake/compiler.lua)

  foreach(FILE ${FILES})
    file(RELATIVE_PATH PATH ${PROJECT_SOURCE_DIR}/sources/lemonxx/ ${FILE})
    if(FILES_BOOTSTRAP)
      set(PATH ${PROJECT_BINARY_DIR}/build/sources/lemonxx/${PATH})
    else()
      set(PATH ${PROJECT_BINARY_DIR}/bootstrap/sources/lemonxx/${PATH})
    endif()
    string(REPLACE ".ctg" "" PATH ${PATH})
    get_filename_component(NAME ${PATH} NAME)
    string(REPLACE "${NAME}" "" DIR ${PATH})
    if(NOT EXISTS ${DIR})
      file(MAKE_DIRECTORY ${DIR})
    endif()
    lemon_file_source_group("Include Files\\${FILES_DIR}" ${PROJECT_BINARY_DIR}/build/sources/lemonxx ${PATH})
    
    add_custom_command(
      OUTPUT ${PATH}
      COMMAND ${LEMON_LUA} ${COMPILER} ${FILE} ${PATH} ${LEMON_MPL_MAX_ARGS}
      DEPENDS ${FILE} ${COMPILER}
      COMMENT "run ctg info compiler ...")
    list(APPEND CTG_FILES ${PATH} ${FILE})
  endforeach()

  set(${OUTPUT} ${CTG_FILES} PARENT_SCOPE)

endfunction()