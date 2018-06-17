//
// ... Testing header files
//
#include <control_testing/test_macros.hpp>
#include <control_testing/test_tools.hpp>




/** Test the Monad class */
struct Monad_test
{
  static constexpr auto sqr = []( auto x ){ return x*x; };

  
  Monad_test() : accum( 0 ) {
    identity_test();
    maybe_test();
  }
  operator int() const { return accum; }
private:
  void
  identity_test(){
    using namespace Control::Testing;
    CONTROL_STATIC_TEST( identity_monad.bind( 3, sqr ) == 9 );
    CONTROL_STATIC_TEST( identity_monad.join( 9 ) == 9 );

    CONTROL_TEST( accum, identity_monad.bind( 3, sqr ) == 9 );
    CONTROL_TEST( accum, identity_monad.join( 9 ) == 9 );

  }


  void
  maybe_test(){
    using namespace Control::Testing;
    CONTROL_STATIC_TEST(
      maybe_monad.bind( maybe_monad.unit( 3 ), []( auto x ){ return maybe_monad.unit( sqr( x )); })
      == just( 9 ));
    


    CONTROL_TEST( accum,  maybe_monad.join( just( just( 3 ))) == just( 3 ));



  }
  int accum;
}; // end of struct Monad_test

int
main( int, char** )
{
  int accum = 0;
  accum += Monad_test();
  return accum;
}
