//******** Copyright © 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose :
//*
//*
//****************************************************************************
#include <iostream>                 // For cout
#include <iomanip>
#include <chrono>                   // For timing
                          
#include "structure.hpp"            // For structure
#include "scale_query.hpp"
#include "scale_query_t.hpp"
//****************************************************************************

int main()
{
    const int ITERATIONS = 1000000;

    // --- Benchmark 1: std::function version ---
    {
      using namespace harmony::query;

      auto start = std::chrono::high_resolution_clock::now();
      for(int i = 0; i < ITERATIONS; ++i)
      {
        auto results = find_all(
          cardinality(7) && has_tritone() 
        );
      } 
      auto end = std::chrono::high_resolution_clock::now();
      auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
      std::cout << "std::function : " << ms << " ms\n";
    }

    // --- Benchmark 2: template/concept version ---
    {
      using namespace harmony::tquery;

      auto start = std::chrono::high_resolution_clock::now();
      for(int i = 0; i < ITERATIONS; ++i)
      {
        auto results = find_all(
          cardinality(7) && has_tritone() 
        );
      }
      auto end = std::chrono::high_resolution_clock::now();
      auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
      std::cout << "template/concept: " << ms << " ms\n";
    }

 return 0;
}


//****************************************************************************
