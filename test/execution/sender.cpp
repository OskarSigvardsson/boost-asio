//
// sender.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Disable autolinking for unit tests.
#if !defined(BOOST_ALL_NO_LIB)
#define BOOST_ALL_NO_LIB 1
#endif // !defined(BOOST_ALL_NO_LIB)

// Test that header file is self-contained.
#include <boost/asio/execution/sender.hpp>

#include "../unit_test.hpp"

namespace exec = boost::asio::execution;

struct not_a_sender
{
};

struct sender_using_base :
  boost::asio::execution::sender_base
{
  sender_using_base()
  {
  }
};

template <typename T>
bool is_unspecialised(T*, ...)
{
  return false;
}

template <typename T>
bool is_unspecialised(T*,
    typename boost::asio::void_type<
      typename exec::sender_traits<
        T>::asio_execution_sender_traits_base_is_unspecialised
    >::type*)
{
  return true;
}

void test_sender_traits()
{
  not_a_sender s1;
  BOOST_ASIO_CHECK(is_unspecialised(&s1, static_cast<void*>(0)));

  sender_using_base s2;
  BOOST_ASIO_CHECK(!is_unspecialised(&s2, static_cast<void*>(0)));
}

void test_is_sender()
{
  BOOST_ASIO_CHECK(!exec::is_sender<not_a_sender>::value);
  BOOST_ASIO_CHECK(exec::is_sender<sender_using_base>::value);
}

BOOST_ASIO_TEST_SUITE
(
  "sender",
  BOOST_ASIO_TEST_CASE(test_sender_traits)
  BOOST_ASIO_TEST_CASE(test_is_sender)
)