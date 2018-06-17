

//
// ... Testing header files
//
#include <control_testing/test_macros.hpp>
#include <control_testing/test_tools.hpp>



/** Test the functor type */
struct Functor_test
{
  static constexpr auto sqr = []( auto x ){ return x*x; };
  Functor_test() : accum( 0 ) {
    using Control::Testing::identity_functor;
    CONTROL_STATIC_TEST( identity_functor.trans( sqr, 3 ) == 9 );
  }
  operator int() const { return accum; }
  
private:
  void
  identity_test(){
    using Control::Testing::identity_functor;
    CONTROL_STATIC_TEST( identity_functor.trans( sqr, 3 ) == 9 );
    CONTROL_TEST( accum, identity_functor.trans( sqr, 3 ) == 9 );

    auto x = 3;
    auto y = identity_functor.trans( sqr, x );

    CONTROL_TEST( accum, y == 9 );
    
      
      
  }

  void
  maybe_test(){
    using namespace Control::Testing;

    CONTROL_STATIC_TEST( maybe_functor.trans( sqr, just( 3 )) == just( 9 ));
    CONTROL_STATIC_TEST( maybe_functor.trans( sqr, nothing<int>() ) == nothing<int>());

    CONTROL_TEST( accum,  maybe_functor.trans( sqr, just( 3 )) == just( 9 ));
    CONTROL_TEST( accum, maybe_functor.trans( sqr, nothing<int>() ) == nothing<int>());

    const auto x = just( 3 );
    auto y = maybe_functor.trans( sqr, x );
    CONTROL_TEST( accum, y == just( 9 ));
    
  }
  
  int accum;
}; // end of struct Functor_test

int
main( int, char** )
{
  int accum = 0;
  accum += Functor_test();
  return accum;
}
