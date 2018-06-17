#ifndef MONAD_HPP_INCLUDED_51007001452796916
#define MONAD_HPP_INCLUDED_51007001452796916 1
//
// ... Control header files
//
#include <control/import.hpp>
#include <control/applicative.hpp>

namespace Control
{
  namespace Core
  {


    template< typename Trans, typename App, typename Unit, typename Bind, typename Join >
    class Monad : public Applicative<Trans,App,Unit>
    {
    public:

      using base = Applicative<Trans,App,Unit>;
      using transform_type = typename base::transform_type;
      using application_type = typename base::transform_type;
      using unit_type = typename base::unit_type;
      using bind_type = Bind;
      using join_type = Join;

      constexpr
      Monad(){}

      template< typename T, typename A, typename U, typename B, typename J >
      constexpr
      Monad( T&& t, A&& a, U&& u, B&& b, J&& j )
	: base( forward<T>( t ), forward<A>( a ), forward<U>( u ))
	, bind_impl( forward<B>( b ))
	, join_impl( forward<J>( j ))
      {}


      template< typename B, typename J >
      constexpr
      Monad( base&& appl, B&& b, J&& j )
	: base( move( appl ))
	, bind_impl( forward<B>( b ))
	, join_impl( forward<J>( j ))
      {}

      template< typename B, typename J >
      constexpr
      Monad( const base& appl, B&& b, J&& j )
	: base( appl )
	, bind_impl( forward<B>( b ))
	, join_impl( forward<J>( j ))
      {}


      

      template< typename ... Ts >
      constexpr auto
      bind( Ts&& ... xs ) const & { return bind_impl( forward<Ts>( xs ) ... ); }

      template< typename ... Ts >
      constexpr auto
      join( Ts&& ... xs ) const & { return join_impl( forward<Ts>( xs ) ... ); }
	

    private:
      
      bind_type bind_impl;
      join_type join_impl;
      
    }; // end of class Monad



    template< typename T, typename A, typename U, typename B, typename J >
    constexpr auto
    monad( T&& t, A&& a, U&& u, B&& b, J&& j ){
      using dT = decay_t<T>;
      using dA = decay_t<A>;
      using dU = decay_t<U>;
      using dB = decay_t<B>;
      using dJ = decay_t<J>;
      return Monad<dT,dA,dU,dB,dJ>(
	forward<T>( t ),
	forward<A>( a ),
	forward<U>( u ),
	forward<B>( b ),
	forward<J>( j ));
    }



    template< typename T, typename A, typename U, typename B, typename J >
    constexpr auto
    monad( Applicative<T,A,U>&& appl, B&& b, J&& j ){
      using dB = decay_t<B>;
      using dJ = decay_t<J>;
      return Monad<T,A,U,dB,dJ>(
	move( appl ),
	forward<B>( b ),
	forward<J>( j ));
    }

    template< typename T, typename A, typename U, typename B, typename J >
    constexpr auto
    monad( const Applicative<T,A,U>& appl, B&& b, J&& j ){
      using dB = decay_t<B>;
      using dJ = decay_t<J>;
      return Monad<T,A,U,dB,dJ>(
	appl,
	forward<B>( b ),
	forward<J>( j ));
    }
    


    
  } // end of namespace Core
} // end of namespace Control
#endif // !defined MONAD_HPP_INCLUDED_51007001452796916
