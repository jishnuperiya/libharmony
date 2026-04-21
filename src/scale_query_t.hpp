//******** Copyright © 2026 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Template/concept-based query system for scales.
//*            Alternative to scale_query.hpp (std::function version).
//*            Everything must be inline — templates need to be visible
//*            at the point of instantiation.
//*
//*
//****************************************************************************
#pragma once
//****************************************************************************

#include <concepts>
#include <vector>

#include "structure.hpp"
#include "scale_database.hpp"

//****************************************************************************
namespace harmony{
namespace tquery{
//****************************************************************************

template<typename P>
concept structure_predicate = std::is_invocable_r_v<bool, P , const structure&>;

  /*
  structural typing - wiki
  duck typing - wiki
  
  */
  // Predicate types

  struct cardinality_pred
  {
    int n;
    bool operator()(const structure& s) const { return s.cardinality() == n; }
  };

  static_assert(structure_predicate<cardinality_pred>);

  struct has_tritone_pred
  {
    bool operator()(const structure& s) const { return s.has_tritone(); }
  };

  // Predicate factories

  inline cardinality_pred cardinality(int n) { return {n}; }
  inline has_tritone_pred has_tritone() { return {}; }

  // Combinators

  template<structure_predicate A, structure_predicate B>
  struct and_pred
  {
    [[no_unique_address]] A a;
    [[no_unique_address]] B b;
    bool operator()(const structure& s) const { return a(s) && b(s); }
  };


  template<structure_predicate A, structure_predicate B>
  auto operator&&(A a, B b) { return and_pred<A, B>{a, b}; }

  // Search

  //template<structure_predicate P>
  [[nodiscard]] std::vector<scale_entry> find_all(structure_predicate auto pred)
  {
    std::vector<scale_entry> result;
    for (const auto& entry : scale_database::catalog())
    {
      if (pred(entry.pattern))
      {
        result.push_back(entry);
      }
    }
    return result;
  }


//****************************************************************************
} // namespace tquery
} // namespace harmony
//****************************************************************************
