//******** Copyright � 2026 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Implementation for class `harmony::scale`.
//*
//*
//****************************************************************************
#pragma once
//****************************************************************************
#include <ostream>           // For ostream

#include "note_set.hpp"

//****************************************************************************
namespace harmony
{
  //****************************************************************************

  class scale
  {
  public:          // Construction
                      scale(note root, note_set notes);
                      
                      //DOUBT) do we need a default ctor?
                      // do we need a default state for every value type?
                      // no default ctor -> user cant do scale s; --> enforces: scale must be always be valid

  public:          // Operations
    note              get_root() const;
    const note_set&   get_notes() const;
  
  private:         // Representation
    note              root_;
    note_set          notes_;
  };

  std::ostream&       operator<<(std::ostream& os, const scale& scale);
}