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

TEST_CASE("Pitch: frequency construction and accessors")
{  
  pitch p1(69);
  CHECK(doctest::Approx(p1.get_frequency().get_hz()) == 440.0);
  CHECK_EQ(p1.get_midi(),69);
}

TEST_CASE("Pitch: compound assignment operators for pitch class")
{
  pitch p1(69);
  p1+=20;
  CHECK_EQ(p1.get_midi(),89);
  
  p1-=10;
  CHECK_EQ(p1.get_midi(),79);
}

TEST_CASE("Pitch: non-member arithmetic operations")
{
  pitch p1(20);
  pitch p2 = p1+2;
  CHECK_EQ(p2.get_midi(), 22);

  pitch p3 = p2-2;
  CHECK_EQ(p3.get_midi(),20);

  int interval = p3-p2;
  CHECK_EQ(interval,-2);
}

TEST_CASE("Pitch: octave equivalence")
{
  pitch c4(60);
  pitch c5(72);

  CHECK(is_octave_equivalent(c4, c5));
 
  CHECK_FALSE(is_octave_equivalent(c4, pitch(61)));
}

TEST_CASE("Pitch: scientific notation")
{
  pitch c4(60);
  CHECK_EQ(name(c4),"C4");   
}


TEST_CASE("Pitch: operator<< works with filebuf / ostream") {

    pitch c4(60);

    std::filebuf fb;
    fb.open("test_pitch_stream.txt", std::ios::out);
    REQUIRE(fb.is_open());

    std::ostream os(&fb);
    os << c4;
    fb.close();

    std::ifstream in("test_pitch_stream.txt");
    std::string contents;
    in >> contents;

    CHECK(contents == "C4");
}