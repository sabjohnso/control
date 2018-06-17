#ifndef PURE_HPP_INCLUDED_773286975965538782
#define PURE_HPP_INCLUDED_773286975965538782 1

//
// ... Control header files
//
#include <control/import.hpp>


namespace Control
{
  namespace Core
  {

    
    /** 
     * @brief Inject a values already wrapped up in some 
     * abstract context into the abstraction environment
     * monad.
     */
    class Pure : public Static_curried<Pure,Nat<2>>{
    public:
      
      template< typename T, typename M >
      static constexpr auto
      call( T&& x, M&& ){ return forward<T>( x ); }
      
    } pure{}; // end of class Pure



    
  } // end of namespace Core
} // end of namespace Control

#endif // !defined PURE_HPP_INCLUDED_773286975965538782
