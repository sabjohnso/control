macro( control_add_simple_test  name )
  add_executable( ${name}_test ${name}_test.cpp )
  add_test( ${name} ${name}_test ) 
endmacro( control_add_simple_test  name )

control_add_simple_test( apply_to )
control_add_simple_test( pure )
control_add_simple_test( functor )
control_add_simple_test( applicative )
control_add_simple_test( monad )
control_add_simple_test( coapplicative )
control_add_simple_test( comonad )
control_add_simple_test( abstraction_environment )


