include(cmake/lemonxx.cmake)

lemon_c_cxx_files(SRC)

lemonxx_ctg_files(CTGS)

lemon_library_project(lemonxx ${SRC} ${CTGS})

target_link_libraries(lemonxx lemon-sys lemon-memory lemon-io lemon-play lemon-lua)