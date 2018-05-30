#include "kx/container/stack.hpp"

#include <catch.hpp>

TEST_CASE ("stack_ff", "[kx]")
{
    kx::stack_fixed_rt<int> s (10);

    REQUIRE (s.size () == 0);
    REQUIRE (s.capacity () == 10);

    s.push (1);

    REQUIRE (s.size () == 1);
    REQUIRE (s.top () == 1);

    auto r = kx::begin (s);

    REQUIRE (r.get () == 1);
    REQUIRE (!r.at_end ());

    r.advance ();

    REQUIRE (r.at_end ());
}
