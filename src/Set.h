/*
 * Set.h
 *
 *  Created on: May 26, 2017
 *      Author: daniel
 */

#pragma once

#include <set>

namespace elladan {

template < typename K, typename C, typename A>
void keep_intersect(std::set<K,C,A>& edited, const std::set<K,C,A>& must_include) {
    auto ite = edited.begin();
    auto ote = must_include.cbegin();

    C cmp;
    while (ite != edited.end() && ote != must_include.cend()){
        bool ths_lt_oth = cmp(*ite, *ote);
        bool oth_lt_ths = cmp(*ote, *ite);

        // Is the same. Keep it.
        if ((!ths_lt_oth) & (!ths_lt_oth)) {
            ++ite;
            ++ote;
        }

        // This value arrives before the next value... Remove it.
        else if (ths_lt_oth)
            ite = edited.erase(ite);

        // This arrive after the next value... Keep searching.
        else // if (oth_lt_ths)
            ++ote;
    }

    // Remove trailing unmatched values.
    while (ite != edited.end()) {
        ite = edited.erase(ite);
    }
}

template < typename K, typename C, typename A>
void keep_difference(std::set<K,C,A>& edited, const std::set<K,C,A>& must_not_include) {
    auto ite = edited.begin();
    auto ote = must_not_include.cbegin();
    C cmp;

    while (ite != edited.end() && ote != must_not_include.cend()){
        bool ths_lt_oth = cmp(*ite, *ote);
        bool oth_lt_ths = cmp(*ote, *ite);

        // Is the same.. Remove it.
        if ((!ths_lt_oth) & (!ths_lt_oth)){
            ite = edited.erase(ite);
            ++ote;
        }

        // This value arrives before the next value... Keep it.
        else if (ths_lt_oth)
            ++ite;

        // This arrive after the next value... Keep searching.
        else // if (oth_lt_ths)
            ++ote;
    }
}

template < typename K, typename C, typename A>
std::set<K,C,A> intersect(const std::set<K,C,A>& base, const std::set<K,C,A>& other) {
    std::set<K,C,A> copy;
    auto ite = base.cbegin();
    auto ote = other.cbegin();
    C cmp;
    while (ite != base.cend() && ote != other.cend()){
        bool ths_lt_oth = cmp(*ite, *ote);
        bool oth_lt_ths = cmp(*ote, *ite);

        // Is the same... Add it.
        if ((!ths_lt_oth) & (!ths_lt_oth)) {
            copy.insert(copy.end(), *ite);
            ++ite;
            ++ote;
        }

        // This value arrives before the next value... Skip it.
        else if (ths_lt_oth)
            ++ite;

        // This arrive after the next value... Keep searching.
        else // if (oth_lt_ths)
            ++ote;
    }
    return copy;
}

template < typename K, typename C, typename A>
std::set<K,C,A> difference(const std::set<K,C,A>& base, const std::set<K,C,A>& other) {
    std::set<K,C,A> copy;
    auto ite = base.cbegin();
    auto ote = other.cbegin();
    C cmp;
    while (ite != base.cend() && ote != other.cend()){
        bool ths_lt_oth = cmp(*ite, *ote);
        bool oth_lt_ths = cmp(*ote, *ite);

        // Is the same... Skip it.
        if ((!ths_lt_oth) & (!ths_lt_oth)){
            ++ite;
            ++ote;
        }

        // This value arrives before the next value... Add it.
        else if (ths_lt_oth){
            copy.insert(copy.end(), *ite);
            ++ite;
        }

        // This arrive after the next value... Keep searching.
        else // if (oth_lt_ths)
            ++ote;
    }
    return copy;
}

} // namespace elladan
