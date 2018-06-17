#ifndef APPLY_TO_HPP_INCLUDED_2021666057527398346
#define APPLY_TO_HPP_INCLUDED_2021666057527398346 1

//
// ... Control header files
//
#include <control/import.hpp>


namespace Control
{
  namespace Core
  {


    /**
     * @brief Apply the second argument to the first
     */
    constexpr
    class Apply_to : public Static_curried<Apply_to,Nat<2>> {
    public:
      template< typename T, typename F >
      static constexpr auto
      call( T&& x, F&& f ){
	return forward<F>( f )( forward<T>( x ));
      }
      
    } apply_to{};





    template< typename T, typename F >
    constexpr auto
    pipe( T&& x, F&& f ){
      return Apply_to::call( forward<T>( x ), forward<F>( f ));
    }

    template< typename T, typename F, typename G, typename ... Hs >
    constexpr auto
    pipe( T&& x, F&& f, G&& g, Hs&& ... hs ){
      return pipe( pipe( forward<T>( x ), forward<F>( f )),
		   forward<G>( g ), forward<Hs>( hs ) ... );
    }

    
  } // end of namespace Core
} // end of namespace Control
#endif // !defined APPLY_TO_HPP_INCLUDED_2021666057527398346
