//******** Copyright � 2026 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : Predicate-based query system for scales
//*
//*
//****************************************************************************
#pragma once
//****************************************************************************

#include <functional>
#include <vector>
#include <optional>

#include "structure.hpp"
#include "scale_database.hpp"

//****************************************************************************
namespace harmony{
  namespace query{
//****************************************************************************

    using predicate         = std::function<bool(const structure&)>;

    template<typename P>
    concept structure_predicate = std::is_invocable_r_v<bool, P, const structure&>;

    using optional_scale_entry = std::optional< std::reference_wrapper<const scale_entry>>;
    //todo: why use std::reference_wrapper and not scale_entry& - why one safe over other

                              // Predicate factories

    inline auto               cardinality(int n);
    inline auto               has_interval(int interval);
    inline auto               has_tritone();
    inline auto               brightness_range(int min_brightness, int max_brightness);

                              // Combinators

                              template<structure_predicate A, structure_predicate B>
    inline auto               operator&&(A a, B b);

                              template<structure_predicate A, structure_predicate B>
    inline auto               operator||(A a, B b);

                              template<structure_predicate A>
    inline auto               operator!(A a);


                              // Search

    optional_scale_entry      find_first(const predicate& pred); // check std:either<a,b>
    std::vector<scale_entry>  find_all(const predicate& pred);    
 
    //***************************************************************************
    // Predicate factories implementations
    //***************************************************************************
    /**
     * Return a predicate that matches scales with exactly n notes.
     *
     * @param n  The desired note count (e.g. 5 for pentatonic, 7 for heptatonic).
     */
    inline auto cardinality(int n)
    {
      return [n](const structure& s)
        {
          return s.cardinality() == n;
        };
    }

    /**
     * Return a predicate that matches scales containing a specific interval.
     *
     * @param interval  The semitone interval to look for (0–11).
     */
    inline auto has_interval(int interval)
    {
      return [interval](const structure& s)
        {
          return s.contains(interval);
        };
    }

    /**
     * Return a predicate that matches scales containing a tritone (interval 6).
     */
    inline auto has_tritone()
    {
      return [](const structure& s)
        {
          return s.has_tritone();
        };
    }

    /**
     * Return a predicate that matches scales whose brightness falls within
     * the given inclusive range.
     *
     * @param min_brightness  Lower bound on brightness.
     * @param max_brightness  Upper bound on brightness.
     */
    inline auto brightness_range(int min_brightness, int max_brightness)
    {
      return [min_brightness, max_brightness](const structure& s)
        {
          return s.brightness() >= min_brightness && s.brightness() <= max_brightness;
        };
    }

  //***************************************************************************
  // Predicate combinators implementations
  //***************************************************************************
    template<structure_predicate A, structure_predicate B>
    inline auto operator&&(A a, B b) //can i pass by const reference predicate?
    {
      return[a, b](const structure& s)
        {
          return a(s) && b(s);
        };
    }

    template<structure_predicate A, structure_predicate B>
    inline auto operator||(A a, B b) //can i pass by const reference predicate?
    {
      return[a, b](const structure& s)
        {
          return a(s) || b(s);
        };
    }

    template<structure_predicate A>
    inline auto operator!(A a) //can i pass by const reference predicate?
    {
      return[a](const structure& s)
        {
          return !a(s);
        };
    }
  //****************************************************************************
 } // namespace query
} // namespace harmony
//****************************************************************************

