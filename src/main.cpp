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
//****************************************************************************

using namespace harmony;
using namespace harmony::query;

int main()
{

  // Query 1: All 7-note scales with a tritone 

    // auto results = find_all_2(
    //   cardinality(7) && has_tritone() 
    // );

    // auto results = find_all_2(
    //   [](const scale_entry& s) { return s.pattern.cardinalitity() == 7 && s.pattern.has_tritone(); }cardinality(7) && has_tritone()


    // );
    // auto results2 = find_all(
    //   cardinality(7) && has_interval(3) && has_interval(4)
    // );

    auto start = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < 1000000; ++i)
    {
      auto results = find_all(
        cardinality(7) && has_tritone() 
      );
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << ms << " ms\n";
    
 return 0;
}


//****************************************************************************
