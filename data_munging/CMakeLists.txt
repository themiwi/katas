configure_file(weather.dat weather.dat COPY_ONLY)

foreach (i RANGE 1 1)
  add_executable(tests_part${i} tests_part${i}.cpp)
  target_link_libraries(tests_part${i} ${GMOCK_BOTH_LIBRARIES})
  add_test(NAME part${i} COMMAND tests_part${i})
endforeach()

add_executable(part1 part1.cpp)

# vim: set et sw=2 :
