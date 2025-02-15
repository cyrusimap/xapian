/** @file
 * @brief Merge two TermList objects using an OR operation.
 */
/* Copyright (C) 2007,2010,2024 Olly Betts
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef XAPIAN_INCLUDED_ORTERMLIST_H
#define XAPIAN_INCLUDED_ORTERMLIST_H

#include "api/termlist.h"

namespace Xapian {
namespace Internal {
class ExpandStats;
}
}

class OrTermList : public TermList {
  protected:
    /// The two TermList objects we're merging.
    TermList *left, *right;

    /** The result of left->get_termname().compare(right->get_termname()).
     *
     *  Until next() is first called, this will be zero.
     */
    int cmp = 0;

    /// Check that next() has already been called.
    void check_started() const;

  public:
    OrTermList(TermList * left_, TermList * right_)
	: left(left_), right(right_) { }

    ~OrTermList();

    Xapian::termcount get_approx_size() const;

    void accumulate_stats(Xapian::Internal::ExpandStats & stats) const;

    Xapian::termcount get_wdf() const;

    Xapian::doccount get_termfreq() const;

    TermList *next();

    TermList* skip_to(std::string_view term);

    Xapian::termcount positionlist_count() const;

    PositionList* positionlist_begin() const;
};

/** A termlist which ORs two termlists together, adding term frequencies.
 *
 *  This termlist is just like OrTermList, but adds the term frequencies of
 *  terms which appear in both sublists together, rather than asserting that the
 *  frequencies are equal.  This is appropriate for spelling termlists.
 */
class FreqAdderOrTermList : public OrTermList {
  public:
    FreqAdderOrTermList(TermList * left_, TermList * right_)
	    : OrTermList(left_, right_)
    { }

    Xapian::doccount get_termfreq() const;
};

#endif // XAPIAN_INCLUDED_ORTERMLIST_H
