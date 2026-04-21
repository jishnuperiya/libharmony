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

#include <initializer_list>     // For initializer_list
#include <assert.h>             // For assert
#include <bitset>               // For bitset
#include <bit>                  // For rotl
#include<optional>              // For optional

#include<iostream>


#include <scale.hpp>
#include <structure.hpp>
#include <scale_database.hpp>

//****************************************************************************
namespace harmony{
//****************************************************************************

  namespace
  {
    /**
     * Build a bitset of intervals from a pattern.
     *
     * TU-local helpers, internal linkage, no need to make it as
     * a static helper function and expose to client in header
     * 
     *  normalizes all intervals to [0, 11] and ensures
     * the invariant that bit 0 (root note) is always present.
     *
     * @param pattern The interval pattern to normalize
     * @return Constructed bitset with all intervals set
     */
    std::bitset<12> build_intervals(std::initializer_list<int> pattern)
    {
      std::bitset<12> result;
      for (auto interval : pattern)
      {
        // normalize interval to [0, 11] 
        result.set(static_cast<std::size_t>((interval % 12 + 12) % 12));
      }
      return result;
    }
  }
  
  /**
  * Construct structure from a bitset of intervals.
  * 
  * Canonical ctor enforces invariant: bit 0 (root) is always set
  * 
  * @param bits A bitset<12> where each bit represents an interval [0, 11]
  */
  structure::structure(std::bitset<12>bits)
    : intervals_(bits)
  {
    intervals_.set(0);
  }

 /**
  * Default construct a structure (delegates to bitset ctor which enforces invariant).
  */
  structure::structure()
    : structure(std::bitset<12>{})
  {
  }

/**
  * Construct a harmonic structure from a list of intervals.
  *
  * Each interval is an integer representing the number of semitones above the root note.
  * Valid intervals are in the range [0, 11].
  * 
  * Delegated initializer_list to the canonical bitset ctor so the pattern is preserved.
  *
  * @param pattern An initializer list of intervals defining the harmonic structure.
  */
  structure::structure(std::initializer_list<int> pattern)
    :structure(build_intervals(pattern))
  {
  }

  // structural equality: compare underlying bitsets
  bool structure::operator==(const structure& other) const
  {
    return intervals_ == other.intervals_;
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

  std::optional<mode_result> structure::mode(int degree) const
  {
    if (degree <= 0 || degree > cardinality())
    {
      assert(false);
      return std::nullopt;
    }

    int count = 0;
    std::optional<int> pivot; 

    for (size_t i = 0; i < 12; ++i)
    {
      if (intervals_.test(i))
      {
        ++count;
        if (count == degree)
        {
          pivot = static_cast<int>(i);
          break;
        }
      }
    }

    if (!pivot)
    {
      return std::nullopt;
    }
      
    auto rotated = structure((intervals_ >> pivot.value()) | (intervals_ << (12 - pivot.value())));

    for (const auto& entry : scale_database::catalog())
    {
      if (entry.pattern == rotated)
      {
        return mode_result(rotated, std::optional<std::string_view>{entry.name});
      }
    }
 
    return  mode_result{rotated, std::optional<std::string_view>{} };
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

  /**
   * Based on the theories of B P Leonard, Brightness is a 
   * measurement of interval content calculated by taking the sum of 
   * each tone's distance from the root
   *
   */
  int structure::brightness() const  
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

  void structure::set_name(std::string_view n)
  {
    name_.emplace(n);
  }

  void structure::clear_name()
  {
    name_.reset();
  }

  std::optional<std::string_view> structure::name() const
  {
    if (name_)
    {
      return std::string_view{ name_->data(),name_->size() };
    }
    return std::nullopt;
  }

//****************************************************************************
} // namespace harmony
//****************************************************************************