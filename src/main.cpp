//******** Copyright © 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose :
//*
//*
//****************************************************************************
#include <cassert>					// For assert
#include <algorithm>                // For std::set_intersection	
#include <iostream>                 // For cout
#include <vector>                   // For std::vector
#include <array>                    // For std::array
#include "harmony.hpp"              // For pitch, frequency and note                                 
#include "chord.hpp"                // For harmony::chord
#include "progression.hpp"          // For harmony::chord_progression
#include "voicer.hpp"               // For generate_voicings
#include "note_set.hpp"             // For harmony::note_set

//****************************************************************************


int main(int, const char* [])
{
	using namespace harmony;

  std::cout << "Harmony Library Test Runner\n";
 /* note_set c_major{ note{0}, note{4}, note{7} };

  note_set extensions{ note{9}, note{11} };

  note_set c_major_plus = c_major | extensions;

  for(note_set::iterator it = c_major_plus.begin(); it != c_major_plus.end(); ++it)
  {
      std::cout << it->name() << " ";
  }*/
  return 0;
}



//****************************************************************************
