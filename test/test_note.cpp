//******** Copyright © 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Implements the main entry point to the test runner.
//*
//*
//*  See Also: https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
//*            for more on the doctest main entry point.
//*                                                                     0-0
//*                                                                   (| v |)
//**********************************************************************w*w***

#include <doctest/doctest.h>                             // For doctest
#include "fstream"                                       // For std::filebuf, std::ifstream
#include <cmath>                                         // For std::fabs
#include "harmony.hpp"                                   // For harmony::chord

//****************************************************************************


using namespace harmony;
double EPS = 1e-2;

TEST_CASE("Note: note construction and naming") {
    note c(0);
    note a(9);
    note b(11);

    CHECK_EQ(c.value(), 0);
    CHECK_EQ(a.value(), 9);
    CHECK_EQ(b.value(), 11);

    CHECK_EQ(c.name(), "C");
    CHECK_EQ(a.name(), "A");
    CHECK_EQ(b.name(), "B");
}

TEST_CASE("Note: note transposition wraps correctly") {
    note n(0); // C
    n.transpose(-1);  
    CHECK_EQ(n.value(), 11);

    n.transpose(2);  
    CHECK_EQ(n.value(), 1);
}

TEST_CASE("Note: note converts to pitch and frequency correctly") {
    note c(0); // C
    pitch p = c.get_pitch(4); // assuming octave 4
    frequency f = c.get_frequency(4);

    CHECK_EQ(p.get_midi(), 60);
    CHECK(std::fabs(f.get_hz() - 261.63) < EPS);

    note a(9); // A
    pitch p2 = a.get_pitch(4);
    frequency f2 = a.get_frequency(4);

    CHECK_EQ(p2.get_midi(), 69);
    CHECK(std::fabs(f2.get_hz() - 440.0) < EPS);
}

TEST_CASE("Note: interval_in_semitones and is_octave_equivalent") {
    note c(0);
    note g(7);
    note c2(0);

    CHECK_EQ(interval_in_semitones(g, c), 7);
    CHECK_EQ(interval_in_semitones(c2, c), 0);
    CHECK(is_octave_equivalent(c, c2));
    CHECK_FALSE(is_octave_equivalent(c, g));
}

TEST_CASE("Note: operator<< works with filebuf / ostream") {

    note c(0);

    std::filebuf fb;
    fb.open("test_note_stream.txt", std::ios::out);
    REQUIRE(fb.is_open());

    std::ostream os(&fb);
    os << c;
    fb.close();

    std::ifstream in("test_note_stream.txt");
    std::string contents;
    in >> contents;

    CHECK(contents == "C");
}
