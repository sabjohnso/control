//
// ... Control header files
//
#include <control/control.hpp>


//
// ... External library header files
//
#include <type_utility/type_utility.hpp>
#include <function_utility/function_utility.hpp>


//
// ... Testing header files
//
#include <control_testing/test_macros.hpp>
#include <control_testing/test_tools.hpp>



/** Testing the abstraction environment */
struct Abstraction_environment_test
{
  Abstraction_environment_test() : accum( 0 ) {
    using namespace Control;
    using namespace Control::Testing;
    using TypeUtility::nat;
    using FunctionUtility::curry;

    constexpr auto sqrM =
      [&]( auto mx ){ 
	return trans( []( auto x ){ return x*x; },
		      mx ); };

    CONTROL_STATIC_TEST( 
      call_with( identity_monad, sqrM( pure( 3 ))) ==
      9 );

    CONTROL_TEST( 
      accum,
      call_with( maybe_monad, sqrM( pure(  just( 3 )))) ==
      just( 9 ));


    //
    // Addition
    //
    
    constexpr auto addM =
      []( auto mx, auto my ){ return 
	bind( pure( mx ), [=]( auto x ){ return
        bind( pure( my ), [=]( auto y ){
	   return unit( x + y ); }); }); };
    
    auto mx = just( 3 );
    auto my = just( 4 );
    auto mz = call_with( maybe_monad, addM( mx, my ));

    CONTROL_TEST( accum, mz == just( 7 ));
		 
    
    constexpr auto ix = 3;
    constexpr auto iy = 4;
    constexpr auto iz = call_with( identity_monad, addM( ix, iy ));

    CONTROL_STATIC_TEST( iz == 7 );


    // constexpr auto addW =
    //   []( auto wx, auto wy ){
    // 	return call_with( 
    // 	  ap( curry( make_array, nat<2> ), pure( wx ), pure( wy )),
    // 	  extend(
    // 	    []( auto arg ){ return 
    // 		call_with( std::get<0>( extract( arg )), [=]( auto x ){ return
    // 		call_with( std::get<1>( extract( arg )), [=]( auto y ){ return
    // 		      pure( x+y ); }); }); })); };


    
    auto q = 
      call_with( identity_comonad,
		 ap( pure( curry( make_array, nat<2>)),
		     pure( 1 ),
		     pure( 2 )));

    CONTROL_TEST( accum, q[ 0 ] == 1 );
    CONTROL_TEST( accum, q[ 1 ] == 2 );

    auto r = call_with( identity_comonad, ap_pure( curry( make_array, nat<2>), 1, 2 ));
    CONTROL_TEST( accum, r[ 0 ] == 1 );
    CONTROL_TEST( accum, r[ 1 ] == 2 );
    
      
    
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Abstraction_environment_test


int
main( int, char** )
{
  int accum = 0;
  accum += Abstraction_environment_test();
  return accum;
}
