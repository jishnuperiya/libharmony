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

#include<set>									     // For set
#include<utility>							     // For pair
#include<bitset>                   // For bitset
#include<cstdint>							     // For uint8_t
#include<iterator>                 // For reverse_iterator
#include<compare>  						     // For operator<=>
#include "harmony.hpp"						 // For note

//****************************************************************************

namespace harmony
{
	class note_set
	{
	public:
		class iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;

    using size_type = std::size_t;

	  constexpr note_set() noexcept
		: notes_{0} {}

	  template<typename InputIt>
	  note_set(InputIt first, InputIt last) noexcept
		: notes_ {0}
	  {
		  for ( ; first != last ; ++first)
		  {
	      insert(*first);
	 	  }
	  }

	  note_set(const std::initializer_list<note>& notes) noexcept
		  : note_set{ notes.begin(),notes.end() } {}

	  constexpr note_set(const note_set&) noexcept = default;
	  constexpr note_set& operator=(const note_set&) noexcept = default;
	  constexpr note_set(note_set&&) = default;
	  constexpr note_set& operator=(note_set&&) noexcept = default;

	  [[nodiscard]] constexpr size_t size() const noexcept
	  {
		  return notes_.count();
	  }

	  [[nodiscard]] constexpr bool contains(note n) const noexcept
	  {
		  return notes_.test(n.value());
	  }

	  note_set& insert(note n) noexcept
	  {
		  notes_.set(n.value(), true);
		  return *this;
	  }

	  [[nodiscard]] constexpr bool operator==(const note_set& other) const noexcept
	  {
		  return this->notes_ == other.notes_;
	  }

    [[nodiscard]] constexpr bool operator!=(const note_set& other) const noexcept = default;

	  constexpr note_set& clear() noexcept
	  {
		  notes_.reset();
		  return *this;
	  }

	  constexpr note_set& remove(const note& n) noexcept
	  {
		  notes_.reset(n.value());
		  return *this;
	  }

	  [[nodiscard ]] constexpr note_set& operator|=(const note_set& other) noexcept
	  {
		  this->notes_ |= other.notes_;
		  return *this;
	  }

	  [[nodiscard]] constexpr note_set& operator&=(const note_set& other) noexcept
	  {
		  this->notes_ &= other.notes_;
		  return *this;
	  }
    // ^=,  +=, -= can be added later as needed


		[[nodiscard]] iterator begin() const noexcept
		{
			return iterator(&notes_, 0);
		}

		[[nodiscard]] iterator end() const noexcept
		{
			return iterator(&notes_, 12);
		}

		[[nodiscard]] reverse_iterator rbegin() const noexcept
		{
			return reverse_iterator(end());
		}

		[[nodiscard]] reverse_iterator rend() const noexcept
		{
			return reverse_iterator(begin());
		}

	  class iterator
	  {
	  public:
		  using iterator_category = std::bidirectional_iterator_tag;
		  using value_type = note;
		  using difference_type = std::ptrdiff_t; 
		  using reference = note;

		  struct pointer 
			{
			  note n;

			  [[nodiscard]] constexpr const note* operator->() const noexcept 
			  { 
				  return &n; 
			  }
		  };

		  iterator() noexcept
			: bits_{ nullptr }, index_{ 12 } 
			{
			}

		  iterator(const std::bitset<12>* bits, std::size_t index) noexcept
			: bits_{ bits }, index_{ index }
		  {
			  advance();
		  }

		  [[nodiscard]] reference operator*() const noexcept
		  {
			  return note{ static_cast<uint8_t>(index_) };
		  }

		  [[nodiscard]] pointer operator->() const noexcept
		  {
			  return pointer{**this };
		  }

		  iterator& operator++() noexcept
		  {
			  ++index_;
			  advance();
			  return *this;
		  }
			
		  iterator operator++(int) noexcept
		  {
			  iterator temp = *this;
			  ++(*this);
			  return temp;
		  }

		  iterator& operator--() noexcept
			{
				--index_;
				retreat(); 
				return *this;
			}

		  iterator operator--(int) noexcept
			{
				iterator temp = *this;
				--(*this);
				return temp;
			}

		  [[nodiscard]] constexpr auto operator<=>(const iterator& other) const noexcept = default;

		 
	  private:
      void advance() noexcept
		  {
		    while (index_ < 12 && bits_ && !bits_->test(index_))
		    {
			    ++index_;
	      }
		  }
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

	[[nodiscard]] constexpr note_set operator|(note_set lhs, const note_set& rhs) noexcept
	{
    return lhs|= rhs;
	}

	[[nodiscard]] constexpr note_set operator&(note_set lhs, const note_set& rhs) noexcept
	{
		return lhs &= rhs;
	}

}