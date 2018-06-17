#ifndef COMONAD_HPP_INCLUDED_1490294297080849190
#define COMONAD_HPP_INCLUDED_1490294297080849190 1

//
// ... Control header files
//
#include <control/import.hpp>
#include <control/coapplicative.hpp>


namespace Control
{
  namespace Core
  {

    template< typename Trans, typename App, typename Observe, typename Extend, typename Duplicate >
    class Comonad : public CoApplicative<Trans,App,Observe>{
    public:
      using base = CoApplicative<Trans,App,Observe>;
      using transform_type = typename base::transform_type;
      using application_type = typename base::application_type;
      using observation_type = typename base::observation_type;
      using extension_type = Extend;
      using duplication_type = Duplicate;

      constexpr
      Comonad(){}

      template< typename T, typename A, typename O, typename E, typename D >
      constexpr
      Comonad( T&& t, A&& a, O&& o, E&& e, D&& d )
	: base( forward<T>( t ), forward<A>( a ), forward<O>( o ))
	, extend_impl( forward<E>( e ))
	, duplicate_impl( forward<D>( d ))
      {}

      template< typename E, typename D >
      constexpr
      Comonad( base&& b,  E&& e, D&& d )
	: base( move( b ))
	, extend_impl( forward<E>( e ))
	, duplicate_impl( forward<D>( d ))
      {}

      template< typename E, typename D >
      constexpr
      Comonad( const base& b,  E&& e, D&& d )
	: base( b )
	, extend_impl( forward<E>( e ))
	, duplicate_impl( forward<D>( d ))
      {}


      

      template< typename ... Ts >
      constexpr auto
      extend( Ts&& ... xs ) const & {
	return extend_impl( forward<Ts>( xs ) ... );
      }

      template< typename ... Ts >
      constexpr auto
      duplicate( Ts&& ... xs ) const & {
	return duplicate_impl( forward<Ts>( xs ) ... );
      }


    private:

      extension_type extend_impl;
      duplication_type duplicate_impl;
	
    }; // end of class Comonad



    template< typename T, typename A, typename O, typename E, typename D >
    constexpr auto
    comonad( T&& t, A&& a, O&& o, E&& e, D&& d ){
      return Comonad<decay_t<T>, decay_t<A>, decay_t<O>, decay_t<E>, decay_t<D>>(
	forward<T>( t ),
	forward<A>( a ),
	forward<O>( o ),
	forward<E>( e ),
	forward<D>( d ));
    }

    template< typename T, typename A, typename O, typename E, typename D >
    constexpr auto
    comonad( CoApplicative<T,A,O>&& base, E&& e, D&& d ){
      return Comonad<T,A,O,decay_t<E>,decay_t<D>>(
	move( base ),
	forward<E>( e ),
	forward<D>( d ));
    }


    
    template< typename T, typename A, typename O, typename E, typename D >
    constexpr auto
    comonad( const CoApplicative<T,A,O>& base, E&& e, D&& d ){
      return Comonad<T,A,O,decay_t<E>,decay_t<D>>(
	base,
	forward<E>( e ),
	forward<D>( d ));
    }


    
    
  } // end of namespace Core
} // end of namespace Control

#endif // !defined COMONAD_HPP_INCLUDED_1490294297080849190
