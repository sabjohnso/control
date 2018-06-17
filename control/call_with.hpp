#ifndef CALL_WITH_HPP_INCLUDED_551927074581628370
#define CALL_WITH_HPP_INCLUDED_551927074581628370 1

//
// ... Control header files
//
#include <control/import.hpp>


namespace Control
{
  namespace Core
  {

    
    constexpr
    class Call_with : public Static_curried<Call_with,Nat<2>>{
    public:

      template< typename M, typename F >
      static constexpr auto
      call( M&& m, F&& f ){
	return forward<F>( f )( forward<M>( m ));
      }
      
    } call_with{}; // end of class Call_with
    
  } // end of namespace Core
} // end of namespace Control

#endif // !defined CALL_WITH_HPP_INCLUDED_551927074581628370
