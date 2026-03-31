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

#include <vector>									     // for std::vector
#include <initializer_list>            // for std::intializer_list
#include <algorithm>                   // for std::unique, std::sort
#include <doctest/doctest.h>           // for doctest
#include <rapidcheck.h>                

#include "structure.hpp"               // for harmony::structure

//****************************************************************************

using namespace harmony;

/**
 * RapidCheck generator for harmony::structure
 *
 */

template<>
struct rc::Arbitrary<harmony::structure>
{
  static rc::Gen<harmony::structure> arbitrary()
  {
    return rc::gen::map(
      rc::gen::arbitrary<std::vector<int>>(),
      [](std::vector<int> intervals)
      {
        std::sort(intervals.begin(), intervals.end());
        intervals.erase(std::unique(intervals.begin(), intervals.end()), intervals.end());
        
        if (intervals.empty() || intervals[0] != 0)
        {
          intervals.insert(intervals.begin(),0);
        }
        std::bitset<12> bits;
        bits.set(0); //Root always present
        for (int interval : intervals)
        {
          bits.set(static_cast<std::size_t>((interval % 12 + 12) % 12));
        }
        return harmony::structure(bits);
      }
    );
  }
};

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

TEST_CASE("structure: random structures are always valid")
{
  rc::check("any generated structure can make a scale",
    [](const harmony::structure& s)
    {
      scale test_scale = s.make_scale(note{ 0 });
      RC_ASSERT(test_scale.get_notes().contains(note{ 0 }));
    });
}

TEST_CASE("structure: make_scale produces correct root")
{
  rc::check("generated scale has the specified root",
    [](const harmony::structure& s, const harmony::note& root)
    {
      scale generated = s.make_scale(root);
      RC_ASSERT(generated.get_root() == root);
    });
}

TEST_CASE("structure: make_scale cardinality is consistent")
{
  rc::check("same structure produces same number of notes regardless of root",
    [](const harmony::structure& s)
    {
      size_t size1 = s.make_scale(note{ 0 }).get_notes().size();
      size_t size2 = s.make_scale(note{ 5 }).get_notes().size();

      RC_ASSERT(size1 == size2);
    });
}


TEST_CASE("structure: mode(1) returns identity")
{
  rc::check("first mode produces same scale as original",
    [](const harmony::structure& s, const harmony::note& root)
    {
      structure mode1 = s.mode(1);

      scale original = s.make_scale(root);
      scale mode1_scale = mode1.make_scale(root);

      RC_ASSERT(original.get_notes() == mode1_scale.get_notes());
    });
}

TEST_CASE("structure: mode preserves cardinality")
{
  rc::check("mode(n) preserves number of notes",
    [](const harmony::structure& s)
    {
      size_t original_size = s.make_scale(note{ 0 }).get_notes().size();

      for (size_t degree = 1; degree <= original_size && degree <= 12; ++degree)
      {
        structure mode = s.mode(static_cast<int>(degree));
        scale mode_scale = mode.make_scale(note{ 0 });

        RC_ASSERT(mode_scale.get_notes().size() == original_size);
      }
    });
}


TEST_CASE("structure: major scale")
{
  structure major{ 0, 2, 4, 5, 7, 9, 11 };
  scale c_major = major.make_scale(note{ 0 });

  CHECK(c_major.get_notes().size() == 7);
  CHECK(c_major.get_notes().contains(note{ 0 }));
  CHECK(c_major.get_notes().contains(note{ 2 }));
  CHECK(c_major.get_notes().contains(note{ 4 }));
  CHECK(c_major.get_notes().contains(note{ 5 }));
  CHECK(c_major.get_notes().contains(note{ 7 }));
  CHECK(c_major.get_notes().contains(note{ 9 }));
  CHECK(c_major.get_notes().contains(note{ 11 }));
}

TEST_CASE("structure: minor scale")
{
  structure minor{ 0, 2, 3, 5, 7, 8, 10 };
  scale a_minor = minor.make_scale(note{ 9 });

  CHECK(a_minor.get_notes().size() == 7);
  CHECK(a_minor.get_notes().contains(note{ 9 }));
  CHECK(a_minor.get_notes().contains(note{ 11 }));
  CHECK(a_minor.get_notes().contains(note{ 0 }));
}

TEST_CASE("structure: pentatonic scale")
{
  structure pentatonic{ 0, 2, 4, 7, 9 };
  scale penta = pentatonic.make_scale(note{ 0 });

  CHECK(penta.get_notes().size() == 5);
}

TEST_CASE("structure: blues scale")
{
  structure blues{ 0, 3, 5, 6, 7, 10 };
  scale blues_scale = blues.make_scale(note{ 0 });

  CHECK(blues_scale.get_notes().size() == 6);
  CHECK(blues_scale.get_notes().contains(note{ 3 }));
  CHECK(blues_scale.get_notes().contains(note{ 6 }));
  CHECK(blues_scale.get_notes().contains(note{ 10 }));
}

TEST_CASE("structure: chromatic scale")
{
  structure chromatic{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
  scale chroma = chromatic.make_scale(note{ 0 });

  CHECK(chroma.get_notes().size() == 12);
  for (uint8_t i = 0; i < 12; ++i)
  {
    CHECK(chroma.get_notes().contains(note{ i }));
  }
}

TEST_CASE("structure: dorian mode")
{
  structure major{ 0, 2, 4, 5, 7, 9, 11 };
  structure dorian = major.mode(2);

  scale dorian_scale = dorian.make_scale(note{ 0 });

  CHECK(dorian_scale.get_notes().contains(note{ 2 }));
  CHECK(dorian_scale.get_notes().contains(note{ 3 }));
  CHECK(dorian_scale.get_notes().contains(note{ 10 }));
}
