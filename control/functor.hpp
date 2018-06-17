#ifndef FUNCTOR_HPP_INCLUDED_1049580325028408916
#define FUNCTOR_HPP_INCLUDED_1049580325028408916 1

//
// ... Control header files
//
#include <control/import.hpp>


namespace Control
{
  namespace Core
  {

    template< typename Trans >
    class Functor
    {
    public:

      using transform_type = Trans;
      
      template< typename ... Ts >
      constexpr
      Functor( Ts&& ... input ) : trans_impl( forward<Ts>( input ) ... ){}
      

      
      template< typename F, typename T >
      constexpr auto
      trans( F&& f, T&& x ) const & { return trans_impl( forward<F>( f ), forward<T>( x )); }

    private:
      constexpr 
      operator transform_type && () && { return move( trans_impl ); }

      constexpr
      operator const transform_type& () && { return trans_impl; }
      
      transform_type trans_impl;

    }; // end of class functor


    template< typename Trans >
    constexpr auto
    functor( Trans&& f ){
      return Functor<decay_t<Trans>>( forward<Trans>( f ));
    }


    
  } // end of namespace Core
} // end of namespace Control

#endif // !defined FUNCTOR_HPP_INCLUDED_1049580325028408916
