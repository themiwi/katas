include_directories(${PROJECT_SOURCE_DIR})

foreach (i RANGE 1 3)
  add_executable(chopv${i} tests.cpp)
  set_target_properties(chopv${i} PROPERTIES COMPILE_DEFINITIONS USE_V${i})
  target_link_libraries(chopv${i} ${GMOCK_BOTH_LIBRARIES})
  add_test(NAME chopv${i} COMMAND chopv${i})
endforeach()

# vim: set et sw=2 :
