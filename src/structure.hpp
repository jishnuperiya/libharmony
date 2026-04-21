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

#include <initializer_list>  // For initializer_list
#include <bitset>            // For bitset
#include <optional>          // For optional
#include <string_view>       // For string_view

#include "scale.hpp"

//****************************************************************************
namespace harmony{
//****************************************************************************
  struct mode_result;
  /**
   * Represents a harmonic structure defined by a set of intervals.
   * 
   * A harmonic structure can generate scales by applying its interval
   * pattern to any root note. For example, a major scale structure
   * would contain intervals {0, 2, 4, 5, 7, 9, 11}.
   */
  class structure 
  {
  public:                         // Construction
                                     structure();
                                     structure(std::initializer_list<int> pattern);
                                     structure(std::bitset<12> bits);

  public:                         // Operations
    bool                             operator==(const structure& other) const;
    scale                            make_scale(note root)       const; 
    std::optional<mode_result>       mode(int degree)            const; 
    
  public:                         // Queries
    int                              cardinality()               const;
    bool                             contains(int interval)      const;
    bool                             has_tritone()               const; 
    int                              brightness()                const;

  public:                         // Name Accessors
    void                             set_name(std::string_view n);
    void                             clear_name();
    std::optional<std::string_view>  name()                      const;


  private:                        // Representation
    std::bitset<12>                  intervals_; 
    std::optional<std::string_view>  name_;
  
  };

  struct mode_result
  {
    structure mode_structure;
    std::optional<std::string_view> mode_name;
  };

//****************************************************************************
} // namespace harmony
//****************************************************************************


