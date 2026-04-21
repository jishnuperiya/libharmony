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
#include "chord.hpp"                                     // For harmony::chord
//****************************************************************************


using namespace harmony;

TEST_CASE("Chord: root() and basic construction") {
    std::vector<note> notes = { note("C"), note("E"), note("G") };

    chord c(note("C"), notes.begin(), notes.end());

    CHECK(c.root().value() == note("C").value());
}

TEST_CASE("Chord: name() outputs only root for now") {
    std::vector<note> notes = { note("C"), note("E"), note("G") };

    chord c(note("C"), notes.begin(), notes.end());

    CHECK(c.name() == "C");
}

TEST_CASE("Chord: get_notes() returns correct pitch classes") {
    
    std::vector<note> notes = { note("C"), note("E"), note("G") };

    chord c(note("C"), notes.begin(), notes.end());

    auto ns = c.get_notes();

    CHECK(ns.size() == 3);
    CHECK(ns[0].value() == note("C").value());
    CHECK(ns[1].value() == note("E").value());
    CHECK(ns[2].value() == note("G").value());
}

TEST_CASE("Chord: get_pitches() returns correct MIDI notes") {
   
    std::vector<note> notes = { note("C"), note("E"), note("G") };

    chord c(note("C"), notes.begin(), notes.end());

    auto ps = c.get_pitches(4);

    REQUIRE(ps.size() == 3);

    CHECK(ps[0].get_midi() == 60); // C4
    CHECK(ps[1].get_midi() == 64); // E4
    CHECK(ps[2].get_midi() == 67); // G4
}


TEST_CASE("Chord: operator<< works with filebuf / ostream") {
     
    std::vector<note> notes = { note("C"), note("E"), note("G") };
    chord c(note("C"), notes.begin(), notes.end());

    std::filebuf fb;
    fb.open("test_chord_stream.txt", std::ios::out);
    REQUIRE(fb.is_open());

    std::ostream os(&fb);
    os << c;
    fb.close();

    std::ifstream in("test_chord_stream.txt");
    std::string contents;
    in >> contents;

    CHECK(contents == "C");
}