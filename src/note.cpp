//******** Copyright � 2026 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Implementation for class `harmony::note`.
//*
//*
//****************************************************************************

#include <cassert>                  //for assert
#include <cmath>                    //for fabs
#include <stdexcept>                //for inalid_argument

#include "harmony.hpp"              

//****************************************************************************
namespace harmony{
//****************************************************************************

namespace {
  /**
   * Convert a note name to its corresponding note value.
   *
   * @param s Note name as a string view.
   * 
   * @return Corresponding note object.
   * 
   * @throws std::invalid_argument if the note name is invalid.
   */ 
  note note_from_name(std::string_view s)
  {
    for (auto const& [name, n] : std::initializer_list<std::pair<std::string_view, note>>{
      
      {"C", note(0)},  {"B#", note(0)},
      {"C#", note(1)}, {"Db", note(1)},
      {"D", note(2)},
      {"D#", note(3)}, {"Eb", note(3)},
      {"E", note(4)},  {"Fb", note(4)},
      {"F", note(5)},  {"E#", note(5)},
      {"F#", note(6)}, {"Gb", note(6)},
      {"G", note(7)},
      {"G#", note(8)}, {"Ab", note(8)},
      {"A", note(9)},
      {"A#", note(10)}, {"Bb", note(10)},
      {"B", note(11)}, {"Cb", note(11)}
})
    {
        if (s == name)
            return n;
    }
    throw std::invalid_argument("Invalid note name");
  }
}
  /** 
  * Construct a note from its value (0-11).
  * 
  * @param value Note value (0 = C, 1 = C#, ..., 11 = B)
  * 
  * @return Corresponding note object.
  */
  
   note::note(uint8_t value)
    : note_{static_cast<uint8_t>(value % 12)} 
  {}

   /**
   * Construct a note from its name.
   * 
   * @param s Note name as a string view.
   */
  note::note(std::string_view s)
	  : note (note_from_name(s))
  { }

  /**
   * Return the underlying note value (0-11).
   */
  uint8_t note::value() const 
  {
    return note_;
  }

  /**
  * Return the canonical name of the note.
  * 
  * @return Note name as a string.
  */
  std::string note::name() const
  {
    return NOTE_NAMES[note_];
  }

  /**
  * Return the pitch corresponding to this note in the given octave.
  * 
  * @param octave Octave number
  */
  pitch note::get_pitch(int octave) const 
  {
    return pitch((octave + 1) * 12 + note_);
  }

  /**
  * Return the frequency corresponding to this note in the given octave.
  * 
  * @param octave Octave number
  */
  frequency note::get_frequency(int octave) const 
  {
    return get_pitch(octave).get_frequency();
  }

  /**
  * Transpose the note by the given number of semitones.
  * 
  * @param semitones Number of semitones to transpose (positive or negative)
  */
  note& note::transpose(int semitones)
  {
    note_ = static_cast<uint8_t>((((int)note_ + semitones) % 12 + 12) % 12);
    return *this;
  }

  /**
  * Transpose the note by the given number of semitones.
  * 
  * @return Reference to the transposed note.
  */ 
  note& note::operator+=(int semitones)
  {
    return transpose(semitones);
  }

  /**
  * Transpose the note by the given number of semitones.
  * 
  * @return New note transposed by the given number of semitones.
  */
  note operator+(note n, int semitones)
  {
    return n.transpose(semitones);
  }

  /**
  * Compare two notes based on their values.
  * 
  * @return true if lhs is less than rhs, false otherwise.
  */
  bool operator<(note lhs, note rhs)
  {
    return lhs.value() < rhs.value();
  }

  /**
  * Equality comparison of two notes based on their values.
  * 
  * @return true if lhs is equal to rhs, false otherwise.
  */
  bool operator==(note lhs, note rhs)
  {
    return lhs.value() == rhs.value();
  }

  /**
  * Return the interval in semitones between two notes.
  * 
  * @return Number of semitones from rhs to lhs (0-11).
  */
  int interval_in_semitones(note lhs, note rhs)
  {
    return ((int)lhs.value() - (int)rhs.value() + 12) % 12;
  }

  /**
  * check if two notes are octave equivalent.
  * 
  * @return true if lhs and rhs are octave equivalent, false otherwise.
  */
  bool is_octave_equivalent(note lhs, note rhs)
  {
    return lhs.value() == rhs.value();
  }

  /**
  * Output the note's name to the given output stream.
  * 
  * @return Reference to the output stream.
  */
  std::ostream& operator<<(std::ostream& os, note n)
  {
    return os << n.name();
  }

}
