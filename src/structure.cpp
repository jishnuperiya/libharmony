//******** Copyright � 2026 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Implementation for class `harmony::structure`.
//*
//*
//****************************************************************************
#pragma once
//****************************************************************************

#include <initializer_list>     // For initializer_list
#include <assert.h>             // For assert
#include <bitset>               // For bitset
#include <bit>                  // For rotl

#include<iostream>


#include <scale.hpp>
#include <structure.hpp>

//****************************************************************************
namespace harmony{
//****************************************************************************

  /**
     * Build a bitset of intervals from a pattern.
     *
     * Static helper that normalizes all intervals to [0, 11] and ensures
     * the invariant that bit 0 (root note) is always present.
     *
     * @param pattern The interval pattern to normalize
     * @return Constructed bitset with all intervals set
     */
  std::bitset<12> structure::build_intervals(std::initializer_list<int> pattern)
  {
    std::bitset<12> result;
    result.set(0); // Invariant: always contains root
    for (auto interval : pattern)
    {
      // normalize interval to [0, 11] 
      result.set(static_cast<std::size_t>((interval % 12 + 12) % 12));
    }
    return result;
  }
/**
  * Construct a harmonic structure from a list of intervals.
  *
  * Each interval is an integer representing the number of semitones above the root note.
  * Valid intervals are in the range [0, 11].
  *
  * @param pattern An initializer list of intervals defining the harmonic structure.
  */
  structure::structure(std::initializer_list<int> pattern)
    :intervals_(build_intervals(pattern))
  {
  }

/**
  * Construct structure from a bitset of intervals.
  *
  * @param bits A bitset<12> where each bit represents an interval [0, 11]
  */
  structure::structure(std::bitset<12>bits)
    : intervals_(bits)
  {
  }

/**
  * Generate a scale based on the harmonic structure and a given root note.
  *
  * The scale is constructed by applying the interval pattern of the harmonic structure
  * to the root note. For example, if the harmonic structure includes intervals {0, 2, 4},
  * and the root note is C (0), the resulting scale will include C (0), D (2), and E (4).
  *
  * @param root The root note from which to generate the scale.
  * @return A scale object representing the generated scale.
  */ 
  scale structure::make_scale(note root) const
  {
    note_set notes;
    for (std::size_t i = 0; i < 12; ++i) 
    {
      if (intervals_.test(i))
      {
        notes.insert(root + static_cast<int>(i));
      }
    }
    return { root, notes};
  }

  structure structure::mode(int degree) const
  {
    //Finding the degree-th set bit
    int pivot = -1;
    
    // QUESTION:
    // i have added -1 here for the assertion if pivot not found 
    // claude code says: i could use std::optional<int> pivot instead of -1 for clear intent.
    // but then i have to use exception instead of assertion.
    // modern c++ has these kind of nice things - but what is your philosophy on this? 
    // i heard john carmack says he still like c with classes kind of style because then he knows what 
    // are the cost are instead of relying on abstractions..not trying to inherit opinions but i want to 
    // what you think
    int count = 0;
    for (size_t i = 0; i < 12; ++i)
    {
      if (intervals_.test(i))
      {
        count++;
        if (count == degree)
        {
          pivot = static_cast<int>(i);
          break;
        }
      }
    }
    assert(pivot >= 0 && "Mode degree out of range");
    
    // QUESTION:
    // i am still not getting a clear decision taking ability between assertion and throw. 
    // because of these 2 things:
    // - assertions are disabled in runtime and for that throw is better
    // - but user of this API would be probably other programmers-- so for them assertions are enough??
  
    // QUESTION: is throwing exceptions bad? 
    auto rotated = (intervals_ >> pivot) | (intervals_ << (12 - pivot));

    return structure(rotated);
 
  }

  int structure::cardinality() const
  {
    return static_cast<int>(intervals_.count());
  }

  bool structure::contains(int interval) const
  {
    return intervals_.test(static_cast<std::size_t>((interval % 12 + 12) % 12));
  }

  bool structure::has_tritone() const
  {
    return contains(6);
  }

  // Based on the theories of B P Leonard, Brightness is a 
  // measurement of interval content calculated by taking the sum of 
  // each tone's distance from the root
  int structure::brightness() const   // think: can i optimize this??
  {
    int brightness = 0;
    for (int i = 0; i < 12; ++i)
    {
      if (contains(i) && i != 0)
      {
        brightness += i;
      }
    }
    return brightness;
  }

//****************************************************************************
} // namespace harmony
//****************************************************************************