//******** Copyright © 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : wrapper class over std::set for musical notes
//*
//*
//****************************************************************************
#pragma once
//****************************************************************************

#include<set>									     // For set
#include<utility>							     // For pair
#include<bitset>                   // For bitset
#include<cstdint>							     // For uint8_t
#include<iterator>                 // For reverse_iterator
#include<compare>  						     // For operator<=>

#include "harmony.hpp"						 

//****************************************************************************
namespace harmony{
//****************************************************************************

 /**
	* Represents a set of musical notes within a single octave.
	*
	* Internally, the set is represented as a fixed-size bitset of 12 elements,
	* corresponding to the 12 pitch classes in an octave.
	*
	* This class provides set-like operations (union, intersection, insertion,
	* removal) with constant-time complexity and deterministic iteration order.
	*
	* @note This type is intentionally lightweight and does not allocate memory.
	*/
	class note_set
	{
	public:
		class iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;

    using size_type = std::size_t;

	 /**
		* Construct an empty note set.
		*/
	  constexpr note_set() noexcept
		: notes_{0} {}

		/**
		* Construct a note set from a range of notes.
		*
		* Duplicate notes are ignored.
		*
		* @tparam InputIt Input iterator yielding values convertible to `note`
		* @param first Iterator to the first element
		* @param last  Iterator past the last element
		*/
	  template<typename InputIt>
	  note_set(InputIt first, InputIt last) noexcept
		: notes_ {0}
	  {
		  for ( ; first != last ; ++first)
		  {
	      insert(*first);
	 	  }
	  }
		
	 /**
    * Construct a note set from an initializer list of notes.
		*/
	  note_set(const std::initializer_list<note>& notes) noexcept
		  : note_set{ notes.begin(),notes.end() } {}

	 /**
    * Return the number of notes in the set.
		*/
	  [[nodiscard]] constexpr size_t size() const noexcept
	  {
		  return notes_.count();
	  }

	 /**
    * Check if the set contains the given note.
		*/
	  [[nodiscard]] constexpr bool contains(note n) const noexcept
	  {
		  return notes_.test(n.value());
	  }

	 /**
    * Insert a note into the set.
		* 
    * If the note is already present, the set remains unchanged.
		*/
	  note_set& insert(note n) noexcept
	  {
		  notes_.set(n.value(), true);
		  return *this;
	  }

	 /**
    * Compare two note sets for equality.
		*/
	  [[nodiscard]] constexpr bool operator==(const note_set& other) const noexcept
	  {
		  return this->notes_ == other.notes_;
	  }

    [[nodiscard]] constexpr bool operator!=(const note_set& other) const noexcept = default;

	 /**
    * Clear all notes from the set.
		*/
	  constexpr note_set& clear() noexcept
	  {
		  notes_.reset();
		  return *this;
	  }

	 /**
    * Remove a note from the set.
		*/
	  constexpr note_set& remove(const note& n) noexcept
	  {
		  notes_.reset(n.value());
		  return *this;
	  }

		/**
    * Compute the union of this note set with another.
		*/
	  [[nodiscard ]] constexpr note_set& operator|=(const note_set& other) noexcept
	  {
		  this->notes_ |= other.notes_;
		  return *this;
	  }

		/**
    * Compute the intersection of this note set with another.
		*/
	  [[nodiscard]] constexpr note_set& operator&=(const note_set& other) noexcept
	  {
		  this->notes_ &= other.notes_;
		  return *this;
	  }
    // ^=,  +=, -= can be added later as needed

	 /**
    * Return an iterator to the first note in the set.
		*/
		[[nodiscard]] iterator begin() const noexcept
		{
			return iterator(&notes_, 0);
		}

		/**
    * Return an iterator past the last note in the set.
		*/
		[[nodiscard]] iterator end() const noexcept
		{
			return iterator(&notes_, 12);
		}

		/**
    * Return a reverse iterator to the last note in the set.
		*/
		[[nodiscard]] reverse_iterator rbegin() const noexcept
		{
			return reverse_iterator(end());
		}

		/**
    * Return a reverse iterator past the first note in the set.
		*/
		[[nodiscard]] reverse_iterator rend() const noexcept
		{
			return reverse_iterator(begin());
		}

	 /**
	  * Bidirectional iterator over the notes in the set.
	  *
	  * Iteration proceeds in ascending pitch-class order.
	  * Only notes present in the set are visited.
	  */
	  class iterator
	  {
	  public:
		  using iterator_category = std::bidirectional_iterator_tag;
		  using value_type = note;
		  using difference_type = std::ptrdiff_t; 
		  using reference = note;

		 /**
		  * Proxy type enabling operator-> for value-based iteration.
		  */
		  struct pointer 
			{
			  note n;

			  [[nodiscard]] constexpr const note* operator->() const noexcept 
			  { 
				  return &n; 
			  }
		  };

			/**
      * Construct an end iterator.
			*/
		  iterator() noexcept
			: bits_{ nullptr }, index_{ 12 } 
			{
			}

		 /**
      * Construct an iterator at the given index.
			* 
      * The iterator will advance to the next present note.
			*/
		  iterator(const std::bitset<12>* bits, std::size_t index) noexcept
			: bits_{ bits }, index_{ index }
		  {
			  advance();
		  }

		 /**
      * Dereference the iterator to obtain the current note.
			*/
		  [[nodiscard]] reference operator*() const noexcept
		  {
			  return note{ static_cast<uint8_t>(index_) };
		  }

		 /**
      * Member access operator for the iterator.
			*/
		  [[nodiscard]] pointer operator->() const noexcept
		  {
			  return pointer{**this };
		  }

		 /**
      * Pre-increment the iterator to the next note in the set.
			*/
		  iterator& operator++() noexcept
		  {
			  ++index_;
			  advance();
			  return *this;
		  }
			
		 /**
      * Post-increment the iterator to the next note in the set.
			*/
		  iterator operator++(int) noexcept
		  {
			  iterator temp = *this;
			  ++(*this);
			  return temp;
		  }

		 /**
      * Pre-decrement the iterator to the previous note in the set.
			*/
		  iterator& operator--() noexcept
			{
				--index_;
				retreat(); 
				return *this;
			}

		 /**
      * Post-decrement the iterator to the previous note in the set.
			*/
		  iterator operator--(int) noexcept
			{
				iterator temp = *this;
				--(*this);
				return temp;
			}

		  [[nodiscard]] constexpr auto operator<=>(const iterator& other) const noexcept = default;

		 
	  private:

		 /**
      * Advance the iterator to the next present note.
			*/
      void advance() noexcept
		  {
		    while (index_ < 12 && bits_ && !bits_->test(index_))
		    {
			    ++index_;
	      }
		  }

		 /**
      * Retreat the iterator to the previous present note.
			*/
		  void retreat() noexcept
		  {
			  while (index_ > 0 && bits_ && !bits_->test(index_))
			  {
				  --index_;
			  }
		  }
		  const std::bitset<12>* bits_;
		  std::size_t index_;
	  };

	private:
	  std::bitset<12> notes_;
	};

 /**
  * Return the union of two note sets.
	*/
	[[nodiscard]] constexpr note_set operator|(note_set lhs, const note_set& rhs) noexcept
	{
    return lhs|= rhs;
	}

 /**
  * Return the intersection of two note sets.
	*/
	[[nodiscard]] constexpr note_set operator&(note_set lhs, const note_set& rhs) noexcept
	{
		return lhs &= rhs;
	}

//****************************************************************************
} // namespace harmony
//****************************************************************************
