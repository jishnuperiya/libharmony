
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
#include "harmony.hpp"									 // For harmony::frequency

//****************************************************************************


using namespace harmony;


TEST_CASE("Frequency: construction and accessors")
{  
  frequency f1(440.0);
  CHECK(doctest::Approx(f1.get_hz()) == 440.0);
  CHECK_EQ(f1.get_midi(),69);
}

TEST_CASE("Frequency: compound assignment operators for frequency class")
{
  frequency f1(440.0);
  f1*=2.0;
  CHECK(doctest::Approx(f1.get_hz()) == 880.0);
  
  f1/=10.0;
  CHECK(doctest::Approx(f1.get_hz()) == 88.0);
}

TEST_CASE("Frequency: non-member arithmetic operations")
{
  frequency f1(440.0);  
  frequency f2 = f1*2.0;
  CHECK(doctest::Approx(f2.get_hz()) == 880.0);

  frequency f3 = f2/2.0;
  CHECK(doctest::Approx(f3.get_hz()) == 440.0);
}

TEST_CASE("Frequency: octave equivalence")
{
  frequency f1(440.0);
  frequency f2(880.0);

  CHECK(is_octave_equivalent(f1, f2));
 
  CHECK_FALSE(is_octave_equivalent(f1, frequency(150.0)));

}

TEST_CASE("Frequency: operator<< works with filebuf / ostream") {

    frequency f1(440.0);

    std::filebuf fb;
    fb.open("test_frequency_stream.txt", std::ios::out);
    REQUIRE(fb.is_open());

    std::ostream os(&fb);
    os << f1;
    fb.close();

    std::ifstream in("test_frequency_stream.txt");
    std::string contents;
    in >> contents;

    CHECK(contents == "440");
}