#ifndef TEST_TOOLS_HPP_INCLUDED_1380356379005535683
#define TEST_TOOLS_HPP_INCLUDED_1380356379005535683 1

//
// ... Standard header files
//
#include <utility>
#include <variant>
#include <array>

//
// ... Control header files
//
#include <control/control.hpp>
#include <control/apply_to.hpp>

//
// ... External header files
//
#include <type_utility/type_utility.hpp>
#include <function_utility/function_utility.hpp>



namespace Control
{
  namespace Testing
  {

    class Identity : public FunctionUtility::Static_curried<Identity,Core::Nat<1>>
    {
    public:
      template< typename T >
      static constexpr auto
      call( T&& x ){
	return std::forward<T>( x );
      }
    } identity{};
   

    class Apply : public FunctionUtility::Static_curried<Apply,Core::Nat<2>>
    {
    public:
      template< typename F, typename T >
      static constexpr auto
      call( F&& f, T&& x ){ return std::forward<F>( f )( std::forward<T>( x )); }
    } apply{};


    
    constexpr auto identity_functor = Functor<Apply>();
    constexpr auto identity_applicative = Applicative<Apply,Apply,Identity>();
    constexpr auto identity_monad = Monad<Apply,Apply,Identity,Core::Apply_to,Identity>();
    constexpr auto identity_coapplicative = CoApplicative<Apply,Apply,Identity>();
    constexpr auto identity_comonad =
      Comonad<Apply,Apply,Identity,Apply,Identity>();


    struct Nothing{};
        
    template< typename T >
    using Maybe = std::variant<T,Nothing>;

    template< typename T >
    constexpr auto
    nothing(){ return Maybe<T>(Nothing{}); }


    constexpr
    class Just : public FunctionUtility::Static_curried<Just,Core::Nat<1>> {
    public:
      template< typename T >
      static constexpr auto
      call( const T& x ){
	return Maybe<std::decay_t<T>>( x );
      }
    } just{};

    template< typename T >
    constexpr bool
    issomething( const Maybe<T>& x ){
      return std::holds_alternative<T>( x );
    }

    template< typename T >
    constexpr bool
    isnothing( const Maybe<T>& x ){
      return ! issomething( x );
    }

    template< typename T >
    constexpr bool
    operator ==( const Maybe<T>& x, const Maybe<T>& y ){
      return issomething( x ) && issomething( y )
	? std::get<T>( x ) == std::get<T>( y )
	: (isnothing( x ) && isnothing( y )
	   ? true
	   : false );
    }

    template< typename T >
    constexpr bool
    operator !=( const Maybe<T>& x, const Maybe<T>& y ){
      return !( x == y );
    }



    



    
    constexpr
    class Maybe_trans : public FunctionUtility::Static_curried<Maybe_trans,Core::Nat<2>>{
    public:
      template< typename ... Ts >
      constexpr
      Maybe_trans( Ts&& ...  ){}
      
      template< typename F, typename T, typename U = std::decay_t<std::result_of_t<F(T)>> >
      static constexpr auto
      call( F&& f, const Maybe<T>& x ){
	return issomething( x )
	  ? f( std::get<T>( x ))
	  : nothing<U>();
      }
    } maybe_trans{};


    
    constexpr
    class Maybe_app : public FunctionUtility::Static_callable<Maybe_app> {
    public:
      template< typename F, typename T, typename U = std::decay_t<std::result_of_t<F(T)>> >
      static constexpr auto
      call( const Maybe<F>& f, const Maybe<T>& x ){
	return (issomething( f ) && issomething( x ))
	  ? std::get<F>( f )( std::get<T>( x ))
	  : nothing<U>();
      }      
    } maybe_app{};

    


    
    class Maybe_bind : public FunctionUtility::Static_callable<Maybe_bind> {
    public:
      template< typename T, typename F >
      static constexpr auto
      call( const Maybe<T>& mx, F&& f ){
	return issomething( mx )
	  ? f( std::get<T>( mx ))
	  : Nothing{};
      }
    } maybe_bind{};


    

    class Maybe_join : public FunctionUtility::Static_callable<Maybe_join> {
    public:
      template< typename T >
      static constexpr auto
      call( const Maybe<Maybe<T>>& mmx ){
	return issomething( mmx )
	  ? std::get<Maybe<T>>( mmx )
	  : nothing<T>();
      }
    } maybe_join{};

    


    constexpr auto maybe_functor =
      functor( maybe_trans );

    constexpr auto maybe_applicative =
      applicative(
	maybe_functor,
	maybe_app,
	just );

    constexpr auto maybe_monad =
      monad( maybe_applicative,
	     maybe_bind,
	     maybe_join );
		   

    



    constexpr
    class Make_array : public FunctionUtility::Static_callable<Make_array> {
    public:
      template< typename ... Ts >
      static constexpr auto
      call( Ts&& ... xs ){
	static_assert( std::is_same<std::common_type_t<Ts...>,
		       std::decay_t<std::common_type_t<Ts...>>>::value );
	return std::array<std::common_type_t<Ts...>,TypeUtility::count_types<Ts...>()>({
	    std::forward<Ts>( xs ) ... });
      }
    } make_array{};



    


    constexpr
    class Array_trans : public FunctionUtility::Static_curried<Array_trans,TypeUtility::Nat<2>> {
    public:

      template< typename F, typename T, size_t N >
      static constexpr auto
      call( F&& f, const std::array<T,N>& xs ){
	return aux( TypeUtility::generate_indices<N>(), std::forward<F>( f ), xs );
      }

      
      template< typename F, typename T, size_t N >
      static constexpr auto
      call( F&& f, std::array<T,N>&& xs ){
	return aux( TypeUtility::generate_indices<N>(), std::forward<F>( f ), std::move( xs ));
      }

    private:
      template< size_t ... indices, typename F, typename T >
      static constexpr auto
      aux( std::index_sequence<indices ...>, F&& f, T&& xs ){
	return make_array( f( std::get<indices>( std::forward<T>( xs ))) ... );
      }
    } array_trans{};




    constexpr
    class Array_app : public FunctionUtility::Static_curried<Array_app,TypeUtility::Nat<2>>
    {
    public:
      template< typename F, typename T, size_t N >
      static constexpr auto
      call( const std::array<F,N>& fs, const std::array<T,N>& xs ){
	return aux( TypeUtility::generate_indices<N>(), fs, xs );
      }
    private:
      template< size_t ... indices, typename F, typename T >
      static constexpr auto
      aux( std::index_sequence<indices...>, F&& fs, T&& xs ){
	return make_array(
	  std::get<indices>( std::forward<F>( fs ))(
	    std::get<indices>( std::forward<T>( xs ))) ... );
      }
    }array_app;
    

    constexpr
    class Array_obeserve : public FunctionUtility::Static_curried<Array_obeserve,TypeUtility::Nat<1>> {
    public:
      template< typename T, size_t N >
      static constexpr auto
      call( const std::array<T,N>& xs ){
	return xs[ 0 ];
      }
    } array_obeserve{};






    constexpr
    class Array_rotate : public FunctionUtility::Static_curried<Array_rotate,TypeUtility::Nat<1>> {
    public:
      template< typename T, size_t N >
      static constexpr auto
      call( const std::array<T,N>& xs ){
	return aux( TypeUtility::generate_indices<N>(), xs );
      }
    private:
      template< size_t index,  size_t ... indices, typename T >
      static constexpr auto
      aux( std::index_sequence< index, indices ... >, const T& xs ){
	return make_array( std::get<indices>( xs ) ..., std::get<index>( xs ) );
      }
    } array_rotate{};


    constexpr
    class Array_duplicate
      : public FunctionUtility::Static_curried<Array_duplicate,TypeUtility::Nat<1>>{
    public:
      template< typename T, size_t N >
      static constexpr auto
      call( const std::array<T,N>& xs ){
	return aux( TypeUtility::generate_indices<N>(), xs );
      }

    private:
      template< size_t ... indices, typename T >
      static constexpr auto
      aux( std::index_sequence<indices...>, const T& xs ){
	return make_array( FunctionUtility::powerfunc( array_rotate, TypeUtility::nat<indices>, xs ) ... );
      }
    } array_duplicate{};


    constexpr
    class Array_extend
      : public FunctionUtility::Static_curried<Array_extend,TypeUtility::Nat<2>>{
    public:
      template< typename F, typename T, size_t N >
      static constexpr auto
      call( F&& f, const std::array<T,N>& xs ){
	return array_trans( std::forward<F>( f ),
			    array_duplicate( xs ));
      }
    } array_extend{};



    constexpr auto array_functor =
      functor( array_trans );

    constexpr auto array_coapplicative =
      coapplicative( array_functor,
		     array_app, 
		     array_obeserve);

    constexpr auto array_comonad =
      comonad( array_coapplicative,
	       array_extend,
	       array_duplicate );
	
		     




    
      





    
    
  } // end of namespace Testing
} // end of namespace Control

#endif // !defined TEST_TOOLS_HPP_INCLUDED_1380356379005535683
