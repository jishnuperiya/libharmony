//******** Copyright � 2026 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Implementation for class `harmony::frequency`.
//*
//*
//****************************************************************************

#include <cassert>      //for assert
#include <cmath>        //for fabs
#include <stdexcept>    //for inalid_argument

#include "harmony.hpp"

//****************************************************************************
namespace harmony{
//****************************************************************************

/**
* Construct a frequency from a postive real number of Hertz.
*
* @param hz Frequency in Hertz (default: 440.0 Hz)
*/
frequency::frequency(double hz)
         : hz_{hz}
{
  assert(hz_ > 0.0 && "frequency must stay positive");
}

/**
 * Return the underlying Frequency in Hertz.
 */
double frequency::get_hz() const
{
  return hz_;
}

/**
 * Return the nearest MIDI note numbeer.
 *
 * @see [Here](https://computermusicresource.com/midikeys.html)
 *      for more on MIDI note numbers.
 */
uint8_t frequency::get_midi() const
{
  return static_cast<uint8_t>(std::round(69 + 12 * std::log2(hz_ / 440.0)));
}

/**
 * Return the nearest even tempered pitch.
 *
 * @see [Here](https://en.wikipedia.org/wiki/Equal_temperament)
 *      for more on the even temperement tuning system.
 */
pitch frequency::get_pitch() const
{
  return pitch(get_midi());
}

/**
* Scale the frequency by a multiplicative factor.
*/
frequency& frequency::operator*=(double delta_hz)
{
  hz_*=delta_hz;
  assert(hz_ > 0.0 && "frequency must stay positive");
  return *this;
}

/**
* Scale the frequency by a divisive factor.
*/
frequency& frequency::operator/=(double delta_hz)
{
  hz_/=delta_hz;
  assert(hz_ > 0.0 && "frequency must stay positive");
  return *this;
}

/**
* Scale the frequency by a multiplicative factor.
*/
frequency operator*(frequency lhs,double factor)
{
  return frequency(lhs.get_hz()*factor);
}

/**
* Scale the frequency by a divisive factor.
*/
frequency operator/(frequency lhs,double factor)
{
  return frequency(lhs.get_hz()/factor);  
}

/**
* Check if two frequencies are octave equivalent.
*/
bool is_octave_equivalent(frequency lhs, frequency rhs)
{
  double freq_ratio = std::log2(lhs.get_hz()/rhs.get_hz());
  return std::fabs(freq_ratio - std::round(freq_ratio)) < 1e-9;
}

/**
* Output frequency in Hertz to output stream.
*/
std::ostream& operator<<(std::ostream& os, frequency f)
{
   return os << f.get_hz();
}