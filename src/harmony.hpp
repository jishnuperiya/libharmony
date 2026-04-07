//******** Copyright � 2026 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Represents the fundamental elements of harmony as value types.
//*
//*
//****************************************************************************
#pragma once
//****************************************************************************

#include <string>           //For std::string
#include <cstdint>          //For uint8_t
#include <ostream>          //For std::ostream
#include <array>            //For std::array
#include <string_view>      //For std::string_view
#include <utility>          //For std::pair

//****************************************************************************
namespace harmony{
//****************************************************************************

  class frequency;
  class pitch;
  class note;
  
  /**
  * Canonical names of the 12 pitch classes
  */
  inline constexpr std::array<const char*, 12> NOTE_NAMES = 
  {{"C", "C#", "D", "D#", "E", "F","F#", "G", "G#", "A", "A#", "B"}};
  
  /**
  * Represents a musical pitch using MIDI notation
  *
  * A pitch is internally stored as a MIDI note number and provides
  * conversions to frequency and note representations.
  * 
  * @see [Here](https://en.wikipedia.org/wiki/MIDI_tuning_standard)
  *      for more on MIDI note numbers.
  */
  class pitch 
  {
  public:    // Construction
                pitch(int midi_note = 60);
                pitch(frequency);

  public:    // Operations  
    uint8_t     get_midi()                  const;
    frequency   get_frequency()             const;
    note        get_note()                  const;
    pitch&      operator+=(int semitones);
    pitch&      operator-=(int semitones);

  private:   // Representation
    uint8_t     midi_note_;  
  };

  pitch         operator+(pitch lhs, int semitones);
  pitch         operator-(pitch lhs, int semitones);
  int           operator-(pitch lhs, pitch rhs);
  bool          is_octave_equivalent(pitch lhs, pitch rhs);
  std::ostream& operator<<(std::ostream& os, pitch p);
  uint8_t       octave(pitch p); 
  std::string   name(pitch p);


 /**
 * Represents an audio frequency as a real number of Hertz.
 *
 * @see [Here](https://en.wikipedia.org/wiki/Audio_frequency)
 *      for more on audio frequencies.
 *
 * @see [Here](https://en.wikipedia.org/wiki/Hertz)
 *      for more on the Hertz unit.
 */
  class frequency 
  {
  public:   // Construction
                frequency(double hz = 440.0);
  
  public:   // Operations
    double      get_hz()                    const;
    uint8_t     get_midi()                  const;
    pitch       get_pitch()                 const;
    frequency&  operator*=(double delta_hz);
    frequency&  operator/=(double delta_hz);

  private:  //  Representation
    double      hz_; 
  };

  frequency     operator*(frequency lhs, double factor);
  frequency     operator/(frequency lhs, double divisor);
  bool          is_octave_equivalent(frequency lhs, frequency rhs);
  std::ostream& operator<<(std::ostream& os, frequency f);

  /**
  * Represents a musical note (pitch class) within an octave.
  * 
  * @see [Here](https://en.wikipedia.org/wiki/Musical_note)
  *      for more on musical notes.
  * 
  * @see [Here](https://en.wikipedia.org/wiki/Pitch_class)
  *      for more on pitch classes.
  */
  class note
  {
  public:    // Construction
    explicit    note(uint8_t value = 0);
    explicit    note(std::string_view name);

  public:    // Operations
    uint8_t     value()                     const;
    std::string name()                      const;
    pitch       get_pitch(int octave)       const;
    frequency   get_frequency(int octave)   const;
    note&       transpose(int semitones);
    note&       operator+=(int);

  private:   // Representation
    uint8_t     note_;
  };

  note          operator+(note, int semitones);
  bool          operator<(note, note);
  bool 		      operator==(note, note);
  int           interval_in_semitones(note, note);
  bool          is_octave_equivalent(note, note);
  std::ostream& operator<<(std::ostream&, note);

//****************************************************************************
} // namespace harmony
//****************************************************************************