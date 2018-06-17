//
// ... Control header files
//
#include <control/pure.hpp>


//
// ... Testing header files
//
#include <control_testing/test_macros.hpp>
#include <control_testing/test_tools.hpp>




/** Test the pure class  */
struct Pure_test
{

  Pure_test() : accum( 0 ) {
    using namespace Control::Core;
    

  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Pure_test


int
main( int, char** )
{
  int accum = 0;
  accum += Pure_test();
  return accum;
}
