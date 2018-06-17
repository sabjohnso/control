//
// ... Control header files
//
#include <control/apply_to.hpp>

//
// ... Testing header files
//
#include <control_testing/test_macros.hpp>

/** Test  the apply_to function */
struct Apply_to_test
{
  Apply_to_test() : accum( 0 ) {
    using namespace Control::Core;
    constexpr auto sqr = []( auto x ){ return x*x; };
    constexpr auto twc = []( auto x ){ return x+x; };

    CONTROL_STATIC_TEST( apply_to( 2, sqr ) == 4 );
    CONTROL_STATIC_TEST( apply_to( 3, twc ) == 6 );
    CONTROL_STATIC_TEST( apply_to( apply_to( 5, twc ), sqr ) == 100 );

    CONTROL_STATIC_TEST( pipe( 5, sqr, twc ) == 50 );
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Apply_to_test



int
main( int, char** )
{
  int accum = 0;
  accum += Apply_to_test();
  return accum;
}
