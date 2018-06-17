#ifndef CONTROL_HPP_INCLUDED_1314212473278589848
#define CONTROL_HPP_INCLUDED_1314212473278589848 1

//
// ... Control header files
//
#include <control/functor.hpp>
#include <control/applicative.hpp>
#include <control/monad.hpp>
#include <control/coapplicative.hpp>
#include <control/comonad.hpp>


#include <control/abstraction_environment.hpp>
#include <control/pure.hpp>
#include <control/call_with.hpp>



namespace Control
{

  using Core::functor;
  using Core::applicative;
  using Core::monad;

  using Core::coapplicative;
  using Core::comonad;

  
  using Core::Functor;
  using Core::Applicative;
  using Core::Monad;
  
  using Core::CoApplicative;
  using Core::Comonad;

  using Core::pure;

  using Core::trans;
  using Core::app;
  using Core::unit;
  using Core::bind;
  using Core::join;
  using Core::obs;
  using Core::extend;
  using Core::duplicate;

  using Core::ap;
  using Core::ap_pure;
  using Core::call_with;
  
  
} // end of namespace Control

#endif // !defined CONTROL_HPP_INCLUDED_1314212473278589848
