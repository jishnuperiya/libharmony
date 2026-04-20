//******** Copyright © 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Represent musical chord progression
//*
//*
//****************************************************************************

#pragma once
#include <vector>				//for std::vector
#include "chord.hpp"			//for harmony::chord

//****************************************************************************

namespace harmony
{
  class chord_progression
  {
  public:
								chord_progression() = default;
    template<typename chord_it>
					         	chord_progression(chord_it b, chord_it e);

	void						add(const chord& c);
	const std::vector<chord>&   chords()              const;

  private:
	std::vector<chord>			chords_;
  };

  std::ostream&					operator<<(std::ostream& os, const chord_progression& p);
}

template<typename chord_it>
harmony::chord_progression::chord_progression(chord_it b, chord_it e)
  : chords_{b,e}{}