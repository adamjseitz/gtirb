//===- Utility.hpp ----------------------------------------------*- C++ -*-===//
//
//  Copyright (C) 2020 GrammaTech, Inc.
//
//  This code is licensed under the MIT license. See the LICENSE file in the
//  project root for license terms.
//
//  This project is sponsored by the Office of Naval Research, One Liberty
//  Center, 875 N. Randolph Street, Arlington, VA 22203 under contract #
//  N68335-17-C-0700.  The content of the information does not necessarily
//  reflect the position or policy of the Government and no official
//  endorsement should be inferred.
//
//===----------------------------------------------------------------------===//
#ifndef GTIRB_UTILITY_H
#define GTIRB_UTILITY_H

#include <gtirb/Addr.hpp>
#include <gtirb/MergeSortedIterator.hpp>
#include <gtirb/Node.hpp>
#include <boost/range/iterator_range.hpp>
#include <optional>

namespace gtirb {

template <typename T> struct AddressOrder {
  using key_type = std::optional<Addr>;
  static key_type key(const T& N) { return N.getAddress(); }
  bool operator()(const T* N1, const T* N2) const {
    return key(*N1) < key(*N2);
  }
};

struct BlockAddressOrder {
  using key_type = std::optional<Addr>;
  static key_type getAddress(const Node* N);

  bool operator()(const Node& N1, const Node& N2) const {
    return getAddress(&N1) < getAddress(&N2);
  }
};

} // namespace gtirb

#endif // GTIRB_UTILITY_H
