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

#include "structure.hpp"
#include "scale_database.hpp"

//****************************************************************************
namespace harmony
{
  namespace query
  {
    //****************************************************************************

    using predicate = std::function<bool(const structure&)>; 
    // change it into concepts

    /*
    concept - constraint- callable obj and return bool and dervied from structure

    */

    // QUESTION: for the predicates - should i go for templates type deduction or
    //           polymorphic function wrapper like this one? arent our queries runtime in nature?
    //           --dont have the clarity of performance tradeoff with this one--

    /*
    let S,T,U be some set
    S x S cartesian prod of set S by itself std::pair<S,S>
    S x T cartesian prod of S with T modelled by std::pair<S,T>
    (S x T) -> U denotes fun space with domain SxT and co domain U
    S -> (T->U) dnotes set of functions that map elements of S to fucntions from T  to U
    todo: proof of isomorphism
    */

    inline predicate cardinality(int n)  //currying-lookup wiki (lambda calculus) alonso church
    {
      return [n](const structure& s)
        {
          return s.cardinality() == n;
        };
    }

 
    inline predicate has_interval(int interval)
    {
      return [interval](const structure& s)
        {
          return s.contains(interval);
        };
    }

    inline predicate has_tritone()
    {
      return [](const structure& s)
        {
          return s.has_tritone();
        };
    }

   
    inline predicate brightness_range(int min_brightness, int max_brightness)
    {
      return [min_brightness, max_brightness](const structure& s)
        {
          return s.brightness() >= min_brightness && s.brightness() <= max_brightness;
        };
    }



    /**
   * Logical AND composition: both predicates must be true
   */
    inline predicate operator&&(const predicate& a, const predicate& b)
    {
      return [a, b](const structure& s)
        {
          return a(s) && b(s);
        };
    }

    /**
     * Logical OR composition: either predicate must be true
     */
    inline predicate operator||(const predicate& a, const predicate& b)
    {
      return [a, b](const structure& s)
        {
          return a(s) || b(s);
        };
    }

    /**
     * Logical NOT composition: negates the predicate
     */
    inline predicate operator!(const predicate& a)
    {
      return [a](const structure& s)
        {
          return !a(s);
        };
    }

    //find_first()

    /**
     * Find all scales in the database matching a predicate
     * @param pred The predicate to filter scales
     * @return Vector of all matching scales
     */
    //template<typename predicate>
     /* requires requires(predicate p, scale_entry s)
    {
      p(s);
    }*/ 
    [[nodiscard]]inline std::vector<scale_entry> find_all(const predicate& pred)
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



    // std::vector<scale_entry>find_all_2(const predicate& pred);
    // // impl in cpp where db sits
    // /*
    // all code out-of line

    // */


  }
}