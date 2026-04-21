//******** Copyright © 2026 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Implementation of predicate-based query system for scales.
//*
//*
//****************************************************************************

#include "scale_query.hpp"
#include "scale_query_t.hpp"
//****************************************************************************
namespace harmony::query{
//****************************************************************************

  using scale_database::catalog;

/**
 * Return a pointer to the first catalog entry matching the predicate,
 * or nullptr if none matches.
 *
 * @param pred  The predicate to test each catalog entry against.
 */
  [[nodiscard]] optional_scale_entry find_first(const predicate& pred)
  {
    for (const auto& entry : catalog())
    {
      if (pred(entry.pattern))
      {
        return entry;
      }
    }
    return std::nullopt;
  }

/**
 * Return all catalog entries whose pattern satisfies the predicate.
 *
 * @param pred  The predicate to test each catalog entry against.
 */
  [[nodiscard]] std::vector<scale_entry> find_all(const predicate& pred)
  {
    std::vector<scale_entry> result;

    for (const auto& entry : catalog())
    {
      if (pred(entry.pattern))
      {
        result.push_back(entry);
      }
    }
    return result;
  }


//****************************************************************************
} // namespace harmony::query
//****************************************************************************
