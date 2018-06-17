#ifndef COAPPLICATIVE_HPP_INCLUDED_1679817197531679725
#define COAPPLICATIVE_HPP_INCLUDED_1679817197531679725 1

//
// ... Control header files
//
#include <control/import.hpp>
#include <control/functor.hpp>



namespace Control
{
  namespace Core
  {

    template< typename Trans, typename App, typename Observe >
    class CoApplicative : public Functor<Trans>
    {
    public:
      using base =  Functor<Trans>;
      using transform_type = typename base::transform_type;
      using application_type = App;
      using observation_type = Observe;

      constexpr CoApplicative(){}

      template< typename T, typename A, typename O >
      constexpr
      CoApplicative( T&& t, A&& a, O&& o )
	: base( forward<T>( t ), forward<A>( a ))
	, app_impl( forward<A>( a ))
	, obs_impl( forward<O>( o ))
      {}

      template< typename A, typename O >
      constexpr
      CoApplicative( const base& f, A&& a, O&& o )
	: base( f )
	, app_impl( forward<A>( a ))
	, obs_impl( forward<O>( o ))
      {}

      template< typename A, typename O >
      constexpr
      CoApplicative( base&& f, A&& a, O&& o )
	: base( move( f ))
	, app_impl( forward<A>( a ))
	, obs_impl( forward<O>( o ))
      {}
      

      template< typename ... Ts >
      constexpr auto
      app( Ts&& ... xs ) const & { return app_impl( forward<Ts>( xs ) ... ); }
     

      template< typename ... Ts >
      constexpr auto
      obs( Ts&& ... xs ) const & { return obs_impl( forward<Ts>( xs ) ... ); }


    private:

      application_type app_impl;
      observation_type obs_impl;
      
	
    }; // end of class CoApplicative

    template< typename Trans, typename App, typename Observe >
    constexpr auto
    coapplicative( Trans&& trans, App&& a, Observe&& o ){
      return CoApplicative<decay_t<Trans>,decay_t<App>, decay_t<Observe>>(
	forward<Trans>( trans ),
	forward<App>( a ),
	forward<Observe>( o ));
    }


    template< typename Trans, typename App, typename Observe >
    constexpr auto
    coapplicative( Functor<Trans>&& f, App&& a, Observe&& o ){
      return CoApplicative<Trans,decay_t<App>, decay_t<Observe>>(
	move( f ),
	forward<App>( a ),
	forward<Observe>( o ));
    }

    template< typename Trans, typename App, typename Observe >
    constexpr auto
    coapplicative( const Functor<Trans>& f, App&& a, Observe&& o ){
      return CoApplicative<Trans,decay_t<App>, decay_t<Observe>>(
	f,
	forward<App>( a ),
	forward<Observe>( o ));
    }
    
  } // end of namespace Core
} // end of namespace Control

#endif // !defined COAPPLICATIVE_HPP_INCLUDED_1679817197531679725
