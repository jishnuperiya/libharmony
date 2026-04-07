//******** Copyright � 2026 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Implementation for class `harmony::pitch`.
//*
//*
//****************************************************************************

#include <cmath>            //for pow
#include <cassert>          //for assert
#include <stdexcept>        //for inalid_argument
#include <sstream>          //for ostringstream
#include <array>            //for array

#include "harmony.hpp"      //for harmony::pitch, harmony::frequency, harmony::note, harmony::NOTE_NAMES

//****************************************************************************
namespace harmony{
//****************************************************************************

/**
* Construct a pitch from a MIDI note number.
* 
* valid range is 0 to 127 inclusive.
* 
* @param midi_note MIDI note number (default: 60, Middle C)
*/
pitch::pitch(int midi_note)
  : midi_note_{ static_cast<uint8_t>(midi_note) }
{
  assert(midi_note >= 0 && midi_note <= 127);
}

/**
* Construct a pitch from a frequency.
* 
* The frequency is converted to the nearest equal-tempered MIDI note number.
* 
* @param freq Frequency in Hertz
*/
pitch::pitch(frequency freq)
  : midi_note_{ freq.get_pitch().get_midi() }
{
}

/**
 * Return the underlying MIDI note number.
 *
 * @see [Here](https://computermusicresource.com/midikeys.html)
 *      for more on MIDI note numbers.
 */ 
uint8_t pitch::get_midi() const
{
  return midi_note_;
}

/**
* Return the frequency corresponding to this pitch.
* 
* Uses A4 = 440 Hz as the reference pitch and assumes equal temperament tuning.
*/
frequency pitch::get_frequency() const
{
  return frequency(440.0 * std::pow(2.0, (midi_note_ - 69) / 12.0));
}

/**
* Return the note (pitch class) corresponding to this pitch.
* 
* The note is determined by the pitch's MIDI note number modulo 12.
*/
note pitch::get_note() const
{
  return note(static_cast<uint8_t>(midi_note_ % 12));
}

/**
* Transpose this pitch upward by a number of semitones.
*/
pitch& pitch::operator+=(int semitones)
{
  midi_note_ = static_cast<uint8_t>(midi_note_ + semitones);
  return *this;
}

/**
* Transpose this pitch downward by a number of semitones.
*/
pitch& pitch::operator-=(int semitones)
{
  midi_note_ = static_cast<uint8_t>(midi_note_ - semitones);
  return *this;
}

/**
* Return a pitch transposed upward by a number of semitones.
*/
pitch operator+(pitch lhs, int semitones)
{
  return lhs += semitones;
}

/**
* Return a pitch transposed downward by a number of semitones.
*/
pitch operator-(pitch lhs, int semitones)
{
  return lhs -= semitones;
}

/**
* Return the interval in semitones between two pitches.
*/
int operator-(pitch lhs, pitch rhs)
{
  return lhs.get_midi() - rhs.get_midi();
}

/**
* Check if two pitches are octave equivalent.
* 
* Two pitches are octave equivalent if their MIDI note numbers differ by a multiple of 12.
*/
bool is_octave_equivalent(pitch lhs, pitch rhs)
{
    return ((lhs.get_midi() - rhs.get_midi()) % 12) == 0;
}

/**
* Return the octave number of the pitch.
  *
  * @see [Here](https://computermusicresource.com/midikeys.html)
  *      for more on MIDI note numbers.
  * 
  * MIDI Convention: C4 = MIDI note 60
  */ 
uint8_t octave(pitch p)
{
  return static_cast<uint8_t>((p.get_midi() / 12) - 1);
}

/**
* Return the canonical name of the pitch (e.g., "C4", "A#3").
*/
std::string name(pitch p)
{
  std::ostringstream os;
  os << NOTE_NAMES[static_cast<std::array<const char*, 12>::size_type>(p.get_midi() % 12)] << static_cast<int>(octave(p));
   
  return os.str();
}

/**
* Output the canonical name of the pitch to a stream.
*/
std::ostream& operator<<(std::ostream& os, pitch p)
{
  return os << name(p);
}

//****************************************************************************
} // namespace harmony
//****************************************************************************