#include <map>
#include <sstream>
#include "chord.hpp"

using namespace harmony;

note chord::root() const { return root_; }

std::string chord::name() const 
{ 
  std::ostringstream o;
  o << root_;
  // Add quality implementation later
  return o.str();
}

std::vector<note> chord::get_notes() const
{
  std::vector<note> result;
  result.reserve(12);
  
  for (int pc = 0; pc < 12; ++pc)
    {
      if (notes_[static_cast<std::size_t>(pc)]) 
        result.emplace_back(NOTE_NAMES[static_cast<std::size_t>(pc)]);
    }

return result;
}

std::vector<pitch> chord::get_pitches(int octave) const
{
  std::vector<pitch> result;

  auto notes = get_notes();

  result.reserve(notes.size());

  for (auto n : notes)
  {
    result.push_back(n.get_pitch(octave));
  }
  return result;
}

std::ostream& harmony::operator<<(std::ostream& os, const chord& c) 
{
  os << c.name();
  return os;
}
