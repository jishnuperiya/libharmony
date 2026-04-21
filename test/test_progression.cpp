//******** Copyright © 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Implements unit tests for harmony::chord_progression
//*
//*
//*  See Also: https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
//*            for more on writing doctest test cases.
//*                                                                     0-0
//*                                                                   (| v |)
//**********************************************************************w*w***

#include <doctest/doctest.h>   // For doctest
#include <fstream>             // For std::filebuf, std::ifstream
#include "harmony.hpp"         // For harmony::chord, harmony::note, harmony::chord_progression
#include "progression.hpp"     // For harmony::chord_progression

//****************************************************************************

using namespace harmony;


TEST_CASE("chord_progression: default construction")
{
    chord_progression p;
    CHECK(p.chords().empty());
}


TEST_CASE("chord_progression: iterator constructor")
{
    std::vector<note> notes1 = { note("C"), note("E"), note("G") };
    std::vector<note> notes2 = { note("G"), note("B"), note("D") };
    chord c1(note("C"), notes1.begin(), notes1.end());
    chord c2(note("G"), notes2.begin(), notes2.end());
    std::array<chord, 2> chords_array = { c1, c2};
	chord_progression p(chords_array.begin(), chords_array.end());

    CHECK(p.chords().size() == 2);
    CHECK(p.chords()[0].root().value() == note("C").value());
    CHECK(p.chords()[1].root().value() == note("G").value());
}

TEST_CASE("chord_progression: add() and chords()")
{
    std::vector<note> notes1 = { note("C"), note("E"), note("G") };
    std::vector<note> notes2 = { note("G"), note("B"), note("D") };

    chord c1(note("C"), notes1.begin(), notes1.end());
    chord c2(note("G"), notes2.begin(), notes2.end());

    chord_progression p;
    p.add(c1);
    p.add(c2);

    CHECK(p.chords().size() == 2);
    CHECK(p.chords()[0].root().value() == note("C").value());
    CHECK(p.chords()[1].root().value() == note("G").value());
}


TEST_CASE("chord_progression: operator<< using filebuf + ostream")
{
    std::vector<note> notes1 = { note("C"), note("E"), note("G") };
    std::vector<note> notes2 = { note("G"), note("B"), note("D") };
    chord c1(note("C"), notes1.begin(), notes1.end());
    chord c2(note("G"), notes2.begin(), notes2.end());
    std::array<chord, 2> chords_array = { c1, c2 };
    chord_progression p(chords_array.begin(), chords_array.end());


    std::filebuf fb;
    fb.open("test_chord_progression_stream.txt", std::ios::out);
    REQUIRE(fb.is_open());

    std::ostream os(&fb);
    os << p;
    fb.close();

    std::ifstream in("test_chord_progression_stream.txt");
    std::string contents;
    std::getline(in, contents);

    CHECK(contents == "C G ");
}
