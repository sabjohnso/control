configure_file( config.hpp.in config.hpp )

install( FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  abstraction_environment.hpp
  applicative.hpp
  apply_to.hpp
  call_with.hpp
  coapplicative.hpp
  comonad.hpp
  control.hpp
  functor.hpp
  import.hpp
  monad.hpp
  pure.hpp
  DESTINATION ${CONTROL_INSTALL_INCLUDE_DIR} )

