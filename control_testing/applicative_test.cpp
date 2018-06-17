

//
// ... Testing header files
//
#include <control_testing/test_macros.hpp>
#include <control_testing/test_tools.hpp>


constexpr auto sqr = []( auto x ){ return x*x; };
constexpr auto twc = []( auto x ){ return x*x; };

/** Test the applicative class */
struct Applicative_test
{
  Applicative_test() : accum( 0 ) {
    identity_test();
    maybe_test();
  }

  operator int() const { return accum; }
  
private:

  void
  identity_test(){
    using namespace Control::Testing;
    CONTROL_STATIC_TEST( identity_applicative.app( sqr, 3 ) == 9 );
    CONTROL_TEST( accum, identity_applicative.app( sqr, 3 ) == 9 );

    auto x = 3;
    auto y = identity_applicative.app( sqr, x );
    CONTROL_TEST( accum, y == 9 );
    
    
  }

  void
  maybe_test(){
    using namespace Control::Testing;
    
    CONTROL_STATIC_TEST( 
      maybe_applicative.app( 
	maybe_applicative.unit( sqr ),
	maybe_applicative.unit( 3 )) == just( 9 ));
    
    CONTROL_TEST( accum, maybe_applicative.app( just( sqr ), just( 3 )) == just( 9 ));

    auto just_sqr = just( sqr );
    auto x = just( 3 );
    auto y = maybe_applicative.app( just_sqr, x );

    CONTROL_TEST( accum, y == just( 9 ));
  
  }
  
  int accum;
  
}; // end of struct Applicative_test

int
main( int, char** )
{
  int accum = 0;
  accum += Applicative_test();
  return accum;
}
