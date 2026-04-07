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
    structure                 mode(int degree)            const;

  public:                   // Queries
    int                       cardinality()             const;
    bool                      contains(int interval)      const;
    //bool                      is_rotationally_symmetric() const;
    bool                      has_tritone()               const; //should i need queries for maj3, min3 etc. so each interval qualities? or do i calclulate it on spot??
    //bool                      is_maximally_even()         const;
    int                       brightness()                const;
    //get name
  private:                  // Helper functions
    static std::bitset<12>    build_intervals(std::initializer_list<int> pattern);

  private:                  // Representation
    std::bitset<12>           intervals_; 
    //name
    // 
  
    // QUESTION:
    // when we design value types/ types with value semantics, does it make sense to make intervals_ const?? 
    // scott meyers says make everything const if pssible.
    // but it will break assignment operations right? also move..
  };
//****************************************************************************
} // namespace harmony
//****************************************************************************


