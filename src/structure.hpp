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

#include "scale.hpp"

//****************************************************************************
namespace harmony{
//****************************************************************************

  /**
   * Represents a harmonic structure defined by a set of intervals.
   * 
   * A harmonic structure can generate scales by applying its interval
   * pattern to any root note. For example, a major scale structure
   * would contain intervals {0, 2, 4, 5, 7, 9, 11}.
   */
  class structure 
  {
  public:                   // Construction
                              structure() = default;
                              structure(std::initializer_list<int> pattern);
                              structure(std::bitset<12> bits);


  public:                   // Operations
    scale                     make_scale(note root)       const; 
    structure                 mode(int degree)            const; //? should the mode() return scale_entry struct? 
                                                                 //? and name can be std::optional. and add a fn in 

  public:                   // Queries
    int                       cardinality()               const;
    bool                      contains(int interval)      const;
    bool                      has_tritone()               const; 
    int                       brightness()                const;
    //? get name?

  private:                  // Helper functions
    static std::bitset<12>    build_intervals(std::initializer_list<int> pattern);

  private:                  // Representation
    std::bitset<12>           intervals_; 
    //? add name?
   
    //! adding name property in structure has some issues
    // mode() create a struture programmatically - what name does it gets?
  
   
  };
//****************************************************************************
} // namespace harmony
//****************************************************************************


