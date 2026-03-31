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
                          
#include "structure.hpp"            // For structure
//****************************************************************************

using namespace harmony;
int main()
{

  structure major{ 0, 2, 4, 5, 7, 9, 11 };

  std::cout << major.mode(4).make_scale(note{"C"}) << std::endl; // TODO: currently the note takes only Uppercase note names

  return 0;
}


//****************************************************************************
