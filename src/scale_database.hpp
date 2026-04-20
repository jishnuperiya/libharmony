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

//****************************************************************************
} // namespace harmony
//****************************************************************************