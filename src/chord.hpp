//******** Copyright © 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Represent musical chords (root + quality + notes)
//*
//*
//****************************************************************************

#pragma once
#include <vector>              //for std::vector
#include "harmony.hpp"         //for harmony::note

namespace harmony 
{

  class chord
  {
  public:
    enum class quality  
    {
      Major = 0,
      Minor = 1,
      Diminished = 2,
      Augmented = 3
    };

  public:
    template<typename note_it>
                        chord(note r, note_it b, note_it e);
    
    note                root()    const;
    std::string         name()    const;

  
    std::vector<note>   get_notes() const;
    std::vector<pitch>  get_pitches(int octave = 4) const;
  
  private:
    note                 const root_;
    std::array<bool, 12>       notes_;
  };

  std::ostream& operator<<(std::ostream& os, const chord& c);
}

template<typename note_it>
harmony::chord::chord(note r, note_it b, note_it e)
    : root_{ r }, notes_{}
{
  for (auto it = b; it != e; ++it)
  {
    notes_[static_cast<std::size_t>((it->get_pitch(4)).get_midi() % 12)] = true;
  }
}