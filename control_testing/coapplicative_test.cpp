//
// ... Testing header files
//
#include <control_testing/test_macros.hpp>
#include <control_testing/test_tools.hpp>

using namespace Control::Testing;

constexpr auto sqr = []( auto x ){ return x*x; };


/** Test the CoApplicative class */
struct CoApplicative_test
{
  CoApplicative_test() : accum( 0 ) {
    identity_test();
    array_test();
  }
  operator int() const { return accum; }
private:
  void
  identity_test(){
    CONTROL_STATIC_TEST( identity_coapplicative.app( sqr, 3 ) == 9 );
    CONTROL_STATIC_TEST( identity_coapplicative.obs( 3 ) == 3 );

    CONTROL_TEST( accum, identity_coapplicative.app( sqr, 3 ) == 9 );
    CONTROL_TEST( accum, identity_coapplicative.obs( 3 ) == 3 );
  }

  void
  array_test(){

    constexpr auto xs = make_array( 2, 3 );
    constexpr auto ys = array_coapplicative.trans( sqr, xs );
    CONTROL_STATIC_TEST( ys[ 0 ] == 4 );
    CONTROL_STATIC_TEST( ys[ 1 ] == 9 );

    constexpr auto fs = make_array( sqr, sqr );
    constexpr auto zs = array_coapplicative.app( fs, xs );
    CONTROL_STATIC_TEST( zs[ 0 ] == 4 );
    CONTROL_STATIC_TEST( zs[ 1 ] == 9 );

    CONTROL_STATIC_TEST( array_coapplicative.obs( xs ) == 2 );

      
    
  }
  
  int accum;
}; // end of struct CoApplicative_test

int
main( int, char** )
{
  int accum = 0;
  accum += CoApplicative_test();
  return accum;
}
