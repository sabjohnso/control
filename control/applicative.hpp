#ifndef APPLICATIVE_HPP_INCLUDED_1167743357581789206
#define APPLICATIVE_HPP_INCLUDED_1167743357581789206 1

//
// ... Control header files
//
#include <control/import.hpp>
#include <control/functor.hpp>



namespace Control
{
  namespace Core
  {

    template< typename Trans, typename App, typename Unit >
    class Applicative : public Functor<Trans>
    {
    public:
      using base = Functor<Trans>;
      
      using transform_type = typename base::transform_type;
      using application_type = App;
      using unit_type = Unit;

      constexpr
      Applicative(){}

      template< typename T, typename A, typename U >
      constexpr
      Applicative( T&& t, A&& a, U&& u )
	: base( forward<T>( t ))
	, app_impl( forward<A>( a ))
	, unit_impl( forward<U>( u ))
      {}

      template< typename A, typename U >
      constexpr
      Applicative( base&& f, A&& a, U&& u )
	: base( move( f ))
	, app_impl( forward<A>( a ))
	, unit_impl( forward<U>( u ))
      {}


      template<  typename A, typename U >
      constexpr
      Applicative( const base& f, A&& a, U&& u )
	: base( f )
	, app_impl( forward<A>( a ))
	, unit_impl( forward<U>( u ))
      {}

      template< typename F, typename T >
      constexpr auto
      app( F&& f, T&& t ) const & {
	return app_impl( forward<F>( f ), forward<T>( t ));
      }

      template< typename T >
      constexpr auto
      unit( T&& x ) const & {
	return unit_impl( forward<T>( x ));
      }
      
    private:
      
      application_type app_impl;
      unit_type unit_impl;
      
    }; // end of class Applicative


    template< typename Trans, typename App, typename Unit >
    constexpr auto
    applicative( Trans&& trans, App&& app, Unit&& unit ){
      return Applicative<
	decay_t<Trans>,
	decay_t<App>,
	decay_t<Unit>>(
	  forward<Trans>( trans ),
	  forward<App>( app ),
	  forward<Unit>( unit ));
    }

    template< typename Trans, typename App, typename Unit >
    constexpr auto
    applicative( Functor<Trans>&& f, App&& app, Unit&& unit ){
      return Applicative<Trans,decay_t<App>,decay_t<Unit>>(
	move( f ),
	forward<App>( app ),
	forward<Unit>( unit ));
    }


    template< typename Trans, typename App, typename Unit >
    constexpr auto
    applicative( const Functor<Trans>& f, App&& app, Unit&& unit ){
      return Applicative<Trans,decay_t<App>,decay_t<Unit>>(
	move( f ),
	forward<App>( app ),
	forward<Unit>( unit ));
    }



    
    
  } // end of namespace Core;
} // end of namespace Control

#endif // !defined APPLICATIVE_HPP_INCLUDED_1167743357581789206
