//******** copyright © 2025 jishnu periya, jonathon bell. all rights reserved.
//*
//*
//*  version : $header:$
//*
//*
//*  purpose : implements the main entry point to the test runner.
//*
//*
//*  see also: https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
//*            for more on the doctest main entry point.
//*                                                                     0-0
//*                                                                   (| v |)
//**********************************************************************w*w***

#include <set>										     // for std::set
#include <algorithm>								   // for std::set_intersection, std::set_union
#include <vector>									     // for std::vector
#include <doctest/doctest.h>           // for doctest
#include <rapidcheck.h>                

#include "harmony.hpp"								 // for harmony::note
#include "note_set.hpp"                // for harmony::note_set
//****************************************************************************

using namespace harmony;


/**
 * RapidCheck generator for harmony::note
 *
 * Generates random notes in the range [0, 11] representing the 12 pitch
 * classes in an octave.
 */
template<>
struct rc::Arbitrary<harmony::note>
{
  static rc::Gen<harmony::note> arbitrary()
  {
    // Generate random note value between 0 and 11 (12 pitch classes)
    auto g = rc::gen::inRange<std::uint8_t>(0, 12);
    auto h = rc::gen::construct<harmony::note>(g);
    return h;
  }
};

/**
 * RapidCheck generator for harmony::note_set
 *
 * Generates random note_set collections by creating arbitrary vectors
 * of notes and constructing a set from them. RapidCheck will automatically
 * deduplicate notes due to set semantics.
 */
template<>
struct rc::Arbitrary<harmony::note_set>
{
  static rc::Gen<harmony::note_set> arbitrary()
  {
    return rc::gen::map(
      rc::gen::arbitrary<std::vector<harmony::note>>(),
      [](const std::vector<harmony::note>& notes)
      {
        return harmony::note_set(notes.begin(), notes.end());
      }
    );
  }
};

TEST_CASE("note_set: default constructor")
{
    const harmony::note_set ns;
    rc::check("default note_set is always empty",
        [&ns](note n)
        {
            RC_ASSERT(ns.size() == 0);
            RC_ASSERT(ns.contains(n) == false);
        });
}

TEST_CASE("note_set: copy and move")
{
  rc::check("copying note_set results in identical set",
    [](harmony::note_set ns)
    {
      harmony::note_set ns_copy = ns;
      RC_ASSERT(ns_copy.size() == ns.size());
      for (auto n : ns)
      {
        RC_ASSERT(ns.contains(n) == ns_copy.contains(n));
      }
    });
}

TEST_CASE("note_set: insert method")
{
  rc::check("inserting notes behaves like a mathemcatical set",
    [](harmony::note_set ns)
    {
      //harmony::note_set ns;
      std::set<uint8_t> ground_truth_set;

      for (auto n : ns)
      {
        ground_truth_set.insert(n.value());
        RC_ASSERT(ns.contains(n));
      }

      RC_ASSERT(ns.size() == ground_truth_set.size());

      for (uint8_t i = 0; i < 12; i++)
      {
        bool should_be_there = (ground_truth_set.find(i) != ground_truth_set.end());
        RC_ASSERT(ns.contains(harmony::note{ i }) == should_be_there);
      }
    });
}


TEST_CASE("note_set: insert chaining")
{
    harmony::note_set ns;
    note c{ 0 }, e{ 4 }, g{ 7 };

    ns.insert(c).insert(e).insert(g);

    CHECK(ns.size() == 3);
    CHECK((ns.contains(c) && ns.contains(e) && ns.contains(g)));
}

TEST_CASE("note_set: contains contract")
{
    rc::check("contains only retunrs true for notes actually present",
        [](const harmony::note& n)
        {
            harmony::note_set ns;
            RC_ASSERT(!ns.contains(n));

            ns.insert(n);
            RC_ASSERT(ns.contains(n));
        });
}

TEST_CASE("note_set: size consistency")
{
    rc::check("size matches number of unique notes",
        [](const harmony::note_set ns)
        {
            RC_ASSERT(ns.size() == 0);
            std::set<uint8_t> ground_truth_note_set;
            for (auto n : ns)
            {
                ground_truth_note_set.insert(n.value());
            }
            RC_ASSERT(ns.size() == ground_truth_note_set.size());
        });
}

TEST_CASE("note_set: range based constructor matches manual insertion")
{
    rc::check("sequence of notes results in same set either done by manual insertion or range based construction",
        [](const std::vector<harmony::note>& notes)
        {
            harmony::note_set set_from_range(notes.begin(), notes.end());

            harmony::note_set set_manual;
            for (auto n : notes)
            {
                set_manual.insert(n);
            }
            RC_ASSERT(set_from_range == set_manual);
        });
}

TEST_CASE("note_set: initializer list constructor matches manual insertion")
{
    rc::check("sequence of notes results in same set either done by manual insertion or initilzer list based construction",
        [](const note& n1, const note& n2, const note& n3)
        {
            harmony::note_set set_from_intializer_list{ n1, n2, n3 };
            harmony::note_set set_manual;
            set_manual.insert(n1).insert(n2).insert(n3);
            
            RC_ASSERT(set_from_intializer_list == set_manual);
        });
}

TEST_CASE("note_set: clear method contract") {
    rc::check("clearing a set always results in size 0",
        [](harmony::note_set ns) {
            ns.clear(); 
            RC_ASSERT(ns.size() == 0);

            for (auto n : ns)
            {
                RC_ASSERT(!ns.contains(n));
            }
        });
}

TEST_CASE("note_set: union operator|")
{
    rc::check("union contains notes present in either source set",
        [](harmony::note_set ns1, harmony::note_set ns2)
        {
            harmony::note_set result = ns1 | ns2;

            for (uint8_t i = 0; i < 12; ++i)
            {
                harmony::note n{i};
                bool in_first = ns1.contains(n);
                bool in_second = ns2.contains(n);

                RC_ASSERT(result.contains(n) == (in_first || in_second));
            }
        });
}

TEST_CASE("note_set: operator|= consistency")
{
    rc::check("a |= b results in the same state as a | b",
        [](harmony::note_set a, harmony::note_set b)
        {
            harmony::note_set expected = a | b;

            harmony::note_set& result_ref = (a |= b);

            RC_ASSERT(a == expected);           
            RC_ASSERT(&result_ref == &a);     
        });
}


TEST_CASE("note_set: intersection operator&")
{
    rc::check("intersection contains only notes present in both source sets",
        [](harmony::note_set ns1, harmony::note_set ns2)
        {
            harmony::note_set result = ns1 & ns2;
            for (uint8_t i = 0; i < 12; ++i)
            {
                harmony::note n{i};
                bool in_first = ns1.contains(n);
                bool in_second = ns2.contains(n);
                RC_ASSERT(result.contains(n) == (in_first && in_second));
            }
        });
}

TEST_CASE("note_set: operator&= consistency")
{
    rc::check("a &= b results in the same state as a & b",
        [](harmony::note_set a, harmony::note_set b)
        {
            harmony::note_set expected = a & b;
            harmony::note_set& result_ref = (a &= b);

            RC_ASSERT(a == expected);
            RC_ASSERT(&result_ref == &a);
        });
}


TEST_CASE("note_set: inequality operator!=")
{
    rc::check("inequality operator behaves as expected",
        [](harmony::note_set ns1, harmony::note_set ns2)
        {
            bool sets_are_equal = (ns1 == ns2);
            RC_ASSERT((ns1 != ns2) == !sets_are_equal);
        });
}

TEST_CASE("note_set: equality operator==")
{
    rc::check("equality operator behaves as expected",
        [](harmony::note_set ns1, harmony::note_set ns2)
        {
            std::set<uint8_t> set1, set2;
            for (auto n : ns1) set1.insert(n.value());
            for (auto n : ns2) set2.insert(n.value());
            bool sets_are_equal = (set1 == set2);
            RC_ASSERT((ns1 == ns2) == sets_are_equal);
        });
}

TEST_CASE("note_set: iterator visits all inserted notes")
{
  rc::check("iterator reaches every note exactly once",
    [](harmony::note_set ns)
    {
      std::set<uint8_t> ground_truth;
      for (auto n : ns) ground_truth.insert(n.value());

      std::set<uint8_t> observed;
      for (auto it = ns.begin(); it != ns.end(); ++it)
      {
        observed.insert(it->value()); 
      }

      RC_ASSERT(observed == ground_truth);
    });
}

