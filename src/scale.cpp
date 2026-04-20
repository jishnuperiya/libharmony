//******** Copyright � 2026 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Implementation for class `harmony::harmonic_structure`.
//*
//*
//****************************************************************************
#include <ostream>               // For ostream

#include <scale.hpp>

//****************************************************************************
namespace harmony
{
  /**
   * Construct a scale from a root note and a set of scale degrees.
    *
    * @param root The root note of the scale.
    * @param notes The set of notes in the scale, represented as intervals from the root.
   */
  scale::scale(note root, note_set notes)
    :root_(root), notes_(notes)
  {
  }

  /**
  * Return the root note of the scale.
   *
   * @return The root note of the scale.
   *
  */
  note scale::get_root() const
  {
    return root_;
  }

  /**
  * Return the set of notes in the scale.
  */
  const note_set& scale::get_notes() const
  {
    return notes_;
  }

  /**
  * Stream output operator for scale.
  * Prints the root note and the set of notes in the scale.
  */
  std::ostream& operator<<(std::ostream& os, const scale& scale)
  {
    note root = scale.get_root();    
    //print starting from root, wrap around the octave
    for (int i =0; i < 12; ++i)
    {
      note n = root + i;
      if (scale.get_notes().contains(n))
      {
        os << n << " ";
      }
    }
    return os;
  }

//****************************************************************************
} // namespace harmony
//****************************************************************************