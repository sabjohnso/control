//
// ... Testing header files
//
#include <control_testing/test_macros.hpp>
#include <control_testing/test_tools.hpp>

//
// ... Type Utility header files
//
#include <type_utility/type_utility.hpp>


using namespace Control::Testing;

constexpr auto sqr = []( auto x ){ return x*x; };



/** Test the comonad type */
struct Comonad_test
{

  Comonad_test() : accum( 0 ) {
    identity_test();
    array_test();
  }
  operator int() const { return accum; }
private:

  void
  identity_test(){
    
    CONTROL_STATIC_TEST( identity_comonad.extend( sqr, 3 ) == 9 );
    CONTROL_STATIC_TEST( identity_comonad.duplicate( 3 ) == 3 );

    CONTROL_TEST( accum,  identity_comonad.extend( sqr, 3 ) == 9 );
    CONTROL_TEST( accum,  identity_comonad.duplicate( 3 ) == 3 );
  }

  void
  array_test(){
    constexpr auto xs = make_array( 1, 2 );
    constexpr auto ys = array_rotate( xs );
    
    CONTROL_STATIC_TEST( ys[ 0 ] == 2 );
    CONTROL_STATIC_TEST( ys[ 1 ] == 1 );
    

    constexpr auto as = array_comonad.duplicate( xs );

    CONTROL_STATIC_TEST( as[ 0 ][ 0 ] == 1 );
    CONTROL_STATIC_TEST( as[ 0 ][ 1 ] == 2 );
    CONTROL_STATIC_TEST( as[ 1 ][ 0 ] == 2 );
    CONTROL_STATIC_TEST( as[ 1 ][ 1 ] == 1 );

    constexpr auto bs = array_comonad.extend(
      []( auto arg ){ return array_comonad.obs( arg ); },
      xs );

    CONTROL_STATIC_TEST( bs[ 0 ] == xs[ 0 ]);
    CONTROL_STATIC_TEST( bs[ 1 ] == xs[ 1 ]);
    
  }
  
  int accum;
}; // end of struct Comonad_test


int
main( int, char** )
{
  int accum = 0;
  accum += Comonad_test();
  return accum;
}
