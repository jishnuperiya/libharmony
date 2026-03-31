//*
//*  purpose : implements the test cases for the `scale` class.
//*
//*
//*  see also: https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
//*            for more on the doctest main entry point.
//*                                                                     0-0
//*                                                                   (| v |)
//**********************************************************************w*w***

#include <doctest/doctest.h>           // for doctest
#include <rapidcheck.h>                // for rapidcheck

#include "scale.hpp"                                  
//****************************************************************************
using namespace harmony;
//****************************************************************************


template<>
struct rc::Arbitrary<harmony::scale>
{
  static rc::Gen<harmony::scale> arbitrary()
  {
    return rc::gen::construct<harmony::scale>(
      rc::gen::arbitrary<harmony::note>(),
      rc::gen::arbitrary<harmony::note_set>()
    );
  }
};

TEST_CASE("scale: constructor preserves root and notes")
{
  rc::check("constructed scale stores root and note_set exactly",
    [](const harmony::note& root,
      const harmony::note_set& notes)
    {
      harmony::scale s(root, notes);

      RC_ASSERT(s.get_root() == root);
      RC_ASSERT(s.get_notes() == notes);
    });
}


TEST_CASE("scale: copy constructor preserves semantics")
{
  rc::check("copy of scale is identical",
    [](const harmony::scale& original)
    {
      harmony::scale copy = original;

      RC_ASSERT(copy.get_root() == original.get_root());
      RC_ASSERT(copy.get_notes() == original.get_notes());
    });
}


TEST_CASE("scale: move constructor preserves semantics")
{
  rc::check("moved scale preserves original value",
    [](const harmony::note& root,
      const harmony::note_set& notes)
    {
      harmony::scale temp(root, notes);
      harmony::scale moved = std::move(temp);

      RC_ASSERT(moved.get_root() == root);
      RC_ASSERT(moved.get_notes() == notes);
    });
}



