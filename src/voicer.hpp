//******** Copyright © 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Represent chord voicings
//*
//*
//****************************************************************************

#pragma once
#include <vector>                //for std::vector
#include "progression.hpp"       //for harmony::chord_progression

//****************************************************************************

namespace harmony
{
std::vector<std::vector<pitch>> generate_voicings(const chord_progression& progression, int octave_start = 4)
{
	std::vector<std::vector<pitch>> voicings;
	for (const auto& chord : progression.chords())
	{
		std::vector<pitch> chord_voicing = chord.get_pitches(octave_start);
		voicings.push_back(chord_voicing);
	}
	return voicings;
}

} // namespace harmony


