#ifndef ABSTRACTION_ENVIRONMENT_HPP_INCLUDED_1298063703706886964
#define ABSTRACTION_ENVIRONMENT_HPP_INCLUDED_1298063703706886964 1


//
// ... Control header files
//
#include <control/import.hpp>
#include <control/call_with.hpp>
#include <control/pure.hpp>



namespace Control
{
  namespace Core
  {



    constexpr
    class Trans : public Static_curried<Trans,Nat<3>> {
    public:
      template< typename F, typename T, typename M >
      static constexpr auto
      call( F&& f, T&& mx, M&& m ){
    	return m.trans(
    	  forward<F>( f ),
    	  forward<T>( mx )( m ));
      }
    } trans{}; // end of class Trans



    constexpr
    class App : public Static_curried<App,Nat<3>> {
    public:
      template< typename F, typename T, typename M >
      static constexpr auto
      call( F&& mf, T&& mx, M&& m ){
    	return m.app(
    	  forward<F>( mf )( m ),
    	  forward<T>( mx )( m ));
      }
    } app{}; // end of class App


    constexpr
    class Ap : public Static_callable<Ap>{
    public:
      template< typename F, typename T >
      static constexpr auto
      call( F&& mf, T&& mx ){ return app( forward<F>( mf ), forward<T>( mx )); }

      template< typename F, typename T, typename U, typename ... Vs >
      static constexpr auto
      call( F&& mf, T&& mx, U&& my, Vs&& ... mzs ){
	return call( call( forward<F>( mf ), forward<T>( mx )),
		     forward<U>( my ), forward<Vs>( mzs ) ... );
      }
	
    } ap{};


    constexpr 
    class Ap_pure : public Static_callable<Ap_pure>{
    public:
      template< typename ... Ts >
      static constexpr auto
      call( Ts&& ... xs ){
	return ap( pure( forward<Ts>( xs )) ... );
      }
    } ap_pure{};




    
    constexpr
    class Unit : public Static_curried<Unit,Nat<2>> { 
    public:
      template< typename T, typename M >
      static constexpr auto
      call( T&& x, M&& m ){
    	return m.unit( forward<T>( x ));
      }
    } unit{}; // end of class Unit


    /**
     * @brief Monadic binding
     *
     */
    constexpr
    class Bind : public Static_curried<Bind,Nat<3>>{
    public:
      template< typename T, typename F, typename M >
      static constexpr auto
      call( T&& mx, F&& f, M&& m ){
    	return m.bind( forward<T>( mx )( m ),
    		       compose( call_with( m ), 
    				forward<F>( f )));

      }
    } bind{}; // end of class Bind



    
    constexpr
    class Join : public Static_curried<Join,Nat<2>>{
    public:
      template< typename T, typename M >
      static constexpr auto
      call( T&& mmx, M&& m ){	
    	return  m.join( apply_to( trans( apply_to( m ), mmx )), m );	  
      }
    } join{}; // end of class Join




    constexpr
    class Observe : public Static_curried<Observe,Nat<2>> {
    public:
      template< typename T, typename W >
      static constexpr auto
      call( T&& wx, W&& w ){
    	return w.obs( forward<T>( wx )( w ));
      }
    } obs{}; // end of class Extract


      

    constexpr
    class Extend : public Static_curried<Extend,Nat<3>> {
    public:
      template< typename T, typename F, typename W >
      static constexpr auto
      call( F&& f,  T&& wx, W&& w ){
    	return w.extend( f, forward<T>( wx )( w ));
      }
    } extend{}; // end of class Extend




    constexpr
    class Duplicate : public Static_curried<Duplicate,Nat<2>> {
    public:
      template< typename T, typename W >
      static constexpr auto
      call( T&& wx, W&& w ){
    	return w.duplicate( forward<T>( wx )( w ));
      }
    } duplicate{}; // end of class duplicate
    
    
  } // end of namespace Core
} // end of namespace Control

#endif // !defined ABSTRACTION_ENVIRONMENT_HPP_INCLUDED_1298063703706886964
