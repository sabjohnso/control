configure_file( config.hpp.in config.hpp )

install( FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  abstract_environment.hpp
  control.hpp
  DESTINATION ${CONTROL_INSTALL_INCLUDE_DIR} )

