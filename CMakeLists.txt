include(cmake/lemonxx.cmake)

lemon_c_cxx_files(SRC)

lemonxx_ctg_files(CTGS)

lemon_library_project(lemonxx BOOTSTRAP1 ${SRC} ${CTGS})