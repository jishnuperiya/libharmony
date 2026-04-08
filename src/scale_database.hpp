//******** Copyright © 2026 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Database of musical scales.
//*
//*
//****************************************************************************
#pragma once
//****************************************************************************

#include <array>
#include <string_view>
#include <vector>

#include "structure.hpp"

//****************************************************************************
namespace harmony{
//****************************************************************************


  struct scale_entry
  {
    std::string_view name;       
    structure pattern;           
  };


  namespace scale_database
  {
    const std::vector<scale_entry>&  catalog();
    const scale_entry*               find_by_name(std::string_view);
    size_t                           size();
  }

  
  // class scale_database                           
  // {                           
  // public:

  //   static const std::vector<scale_entry>& catalog()
  //   {
  //     static std::vector<scale_entry> scales = {                 // QUESTION: make constexpr? vector -> array, structure ctor -> constexpr?
  //       // Pentatonic scales (5 notes)
  //       {"Major Pentatonic",        structure{0, 2, 4, 7, 9}},
  //       {"Minor Pentatonic",        structure{0, 3, 5, 7, 10}},
  //       {"Egyptian",                structure{0, 2, 5, 7, 10}},
  //       {"Hirajoshi",               structure{0, 2, 3, 7, 8}},
  //       {"Insen",                   structure{0, 1, 5, 7, 10}},

  //       // Hexatonic scales (6 notes)
  //       {"Blues Scale",             structure{0, 3, 5, 6, 7, 10}},
  //       {"Whole Tone",              structure{0, 2, 4, 6, 8, 10}},
  //       {"Augmented",               structure{0, 3, 4, 7, 8, 11}},
  //       {"Prometheus",              structure{0, 2, 4, 6, 9, 11}},
  //       {"Tritone",                 structure{0, 1, 4, 6, 7, 10}},

  //       // Heptatonic scales (7 notes)
  //       {"Ionian (Major)",          structure{0, 2, 4, 5, 7, 9, 11}},
  //       {"Dorian",                  structure{0, 2, 3, 5, 7, 9, 10}},
  //       {"Phrygian",                structure{0, 1, 3, 5, 7, 8, 10}},
  //       {"Lydian",                  structure{0, 2, 4, 6, 7, 9, 11}},
  //       {"Mixolydian",              structure{0, 2, 4, 5, 7, 9, 10}},
  //       {"Aeolian (Natural Minor)", structure{0, 2, 3, 5, 7, 8, 10}},
  //       {"Locrian",                 structure{0, 1, 3, 5, 6, 8, 10}},
  //       {"Harmonic Minor",          structure{0, 2, 3, 5, 7, 8, 11}},
  //       {"Melodic Minor (Jazz)",    structure{0, 2, 3, 5, 7, 9, 11}},
  //       {"Phrygian Dominant",       structure{0, 1, 4, 5, 7, 8, 10}},
  //       {"Lydian Dominant",         structure{0, 2, 4, 6, 7, 9, 10}},
  //       {"Altered Scale",           structure{0, 1, 3, 4, 6, 8, 10}},
  //       {"Double Harmonic Major",   structure{0, 1, 4, 5, 7, 8, 11}},
  //       {"Hungarian Minor",         structure{0, 2, 3, 6, 7, 8, 11}},
  //       {"Acoustic (Overtone)",     structure{0, 2, 4, 6, 7, 9, 10}},

  //       // Octatonic scales (8 notes)
  //       {"Diminished (H-W)",        structure{0, 1, 3, 4, 6, 7, 9, 10}},
  //       {"Diminished (W-H)",        structure{0, 2, 3, 5, 6, 8, 9, 11}},
  //       {"Bebop Major",             structure{0, 2, 4, 5, 7, 8, 9, 11}},
  //       {"Bebop Dominant",          structure{0, 2, 4, 5, 7, 9, 10, 11}},
        
  //       // Chromatic (12 notes)
  //       {"Chromatic",               structure{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}}
  //     };
  //     return scales;
  //   }

  //   static const scale_entry* find_by_name(std::string_view name)                                                           
  //   {                                                              
  //     const auto& scales = catalog();
  //     for (const auto& entry : scales)
  //     {
  //       if (entry.name == name)
  //       {
  //         return &entry;
  //       }
  //     }
  //     return nullptr;
  //   }

  
  //   static size_t size()
  //   {
  //     return catalog().size();
  //   }
  // };

  //****************************************************************************
} // namespace harmony
//****************************************************************************