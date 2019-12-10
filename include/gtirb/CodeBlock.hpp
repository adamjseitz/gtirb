//===- CodeBlock.hpp ------------------------------------------------*- C++
//-*-===//
//
//  Copyright (C) 2018 GrammaTech, Inc.
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
#ifndef GTIRB_BLOCK_H
#define GTIRB_BLOCK_H

#include <gtirb/Addr.hpp>
#include <gtirb/CFG.hpp>
#include <gtirb/CfgNode.hpp>
#include <gtirb/Export.hpp>
#include <gtirb/Node.hpp>
#include <proto/CodeBlock.pb.h>
#include <boost/range/iterator_range.hpp>
#include <cstdint>
#include <vector>

/// \file CodeBlock.hpp
/// \ingroup CFG_GROUP
/// \brief Classes gtirb::CodeBlock and gtirb::Offset.
/// \see CFG_GROUP

namespace proto {
class Offset;
} // namespace proto

namespace gtirb {
class ByteInterval;

/// \class CodeBlock
///
/// \brief A basic block.
/// \see \ref CFG_GROUP
class GTIRB_EXPORT_API CodeBlock : public CfgNode {
public:
  /// \brief Create a CodeBlock object.
  ///
  /// \param C          The Context in which this block will be held.
  /// \param Size       The size of the block in bytes.
  /// \param DecodeMode The decode mode of the block.
  ///
  /// \return The newly created CodeBlock.
  static CodeBlock* Create(Context& C, ByteInterval* Parent, uint64_t Size,
                           uint64_t DecodeMode = 0) {
    return C.Create<CodeBlock>(C, Parent, Size, DecodeMode);
  }

  /// \brief Get the \ref ByteInterval this block belongs to.
  ByteInterval* getByteInterval() const { return Parent; }

  /// \brief Get the size from a \ref CodeBlock.
  ///
  /// \return The size in bytes.
  ///
  /// Use with CodeBlock::getAddress() to obtain arguments to pass to
  /// ByteMap::data() for an iterator over the contents of a \ref CodeBlock.
  uint64_t getSize() const { return Size; }

  /// \brief Get the decode mode from a \ref CodeBlock.
  ///
  /// \return The decode mode.
  uint64_t getDecodeMode() const { return DecodeMode; }

  /// \brief Get the offset from the beginning of the \ref ByteInterval this
  /// block belongs to.
  uint64_t getOffset() const;

  /// \brief Get the address of this block, if present. See \ref
  /// ByteInterval.getAddress for details on why this address may not be
  /// present.
  std::optional<Addr> getAddress() const;

  /// @cond INTERNAL
  /// \brief The protobuf message type used for serializing CodeBlock.
  using MessageType = proto::CodeBlock;

  /// \brief Serialize into a protobuf message.
  ///
  /// \param[out] Message   Serialize into this message.
  ///
  /// \return void
  void toProtobuf(MessageType* Message) const;

  /// \brief Construct a CodeBlock from a protobuf message.
  ///
  /// \param C  The Context in which the deserialized CodeBlock will be held.
  /// \param Message  The protobuf message from which to deserialize.
  ///
  /// \return The deserialized CodeBlock object, or null on failure.
  static CodeBlock* fromProtobuf(Context& C, ByteInterval* Parent,
                                 const MessageType& Message);

  static bool classof(const Node* N) { return N->getKind() == Kind::CodeBlock; }
  /// @endcond

private:
  CodeBlock(Context& C) : CfgNode(C, Kind::CodeBlock) {}
  CodeBlock(Context& C, ByteInterval* P, uint64_t S, uint64_t Decode)
      : CfgNode(C, Kind::CodeBlock), Parent(P), Size(S), DecodeMode(Decode) {}

  void setByteInterval(ByteInterval* BI) { Parent = BI; }

  ByteInterval* Parent;
  uint64_t Size{0};
  uint64_t DecodeMode{0};

  friend class Context;
  friend class ByteInterval;
};

/// \class Offset
///
/// \brief Describes a location inside a block or data object.
struct GTIRB_EXPORT_API Offset {

  /// \brief The UUID of the block or data object.
  UUID ElementId;

  /// \brief The displacement from the start of the block or data object, in
  /// bytes.
  uint64_t Displacement;

  /// \brief Constructor using a ElemId uuid and a Displacement.
  Offset(const UUID& ElemId, uint64_t Disp)
      : ElementId(ElemId), Displacement(Disp) {}

  /// \brief Default constructor.
  Offset() = default;

  /// @cond INTERNAL
  /// \brief The protobuf message type used for serializing Offset.
  using MessageType = proto::Offset;

  /// \brief Serialize into a protobuf message.
  ///
  /// \param[out] Message   Serialize into this message.
  ///
  /// \return void
  void toProtobuf(MessageType* Message) const;

  /// \brief Construct a Offset from a protobuf message.
  ///
  /// \param C  The Context in which the deserialized Offset will be
  ///           held.
  /// \param Message  The protobuf message from which to deserialize.
  ///
  /// \return The deserialized Offset object, or null on failure.
  void fromProtobuf(Context& C, const MessageType& Message);
  /// @endcond

  /// \brief Equality operator for \ref Offset.
  // Note:boost uiid is not constexpr
  friend bool operator==(const Offset& LHS, const Offset& RHS) noexcept {
    return LHS.ElementId == RHS.ElementId &&
           LHS.Displacement == RHS.Displacement;
  }

  /// \brief Inequality operator for \ref Offset.
  friend bool operator!=(const Offset& LHS, const Offset& RHS) noexcept {
    return !operator==(LHS, RHS);
  }

  /// \brief Less-than operator for \ref Offset.
  friend constexpr bool operator<(const Offset& LHS,
                                  const Offset& RHS) noexcept {
    return std::tie(LHS.ElementId, LHS.Displacement) <
           std::tie(RHS.ElementId, RHS.Displacement);
  }

  /// \brief Greater-than operator for \ref Offset.
  friend constexpr bool operator>(const Offset& LHS,
                                  const Offset& RHS) noexcept {
    return operator<(RHS, LHS);
  }

  /// \brief Less-than-or-equal operator for \ref Offset.
  friend constexpr bool operator<=(const Offset& LHS,
                                   const Offset& RHS) noexcept {
    return !operator<(RHS, LHS);
  }

  /// \brief Greater-than-or-equal operator for \ref Offset.
  friend constexpr bool operator>=(const Offset& LHS,
                                   const Offset& RHS) noexcept {
    return !operator<(LHS, RHS);
  }
};

} // namespace gtirb

namespace std {

/// \brief Hash implementation of gtirb::UUID.
template <> struct hash<boost::uuids::uuid> {
  size_t operator()(const boost::uuids::uuid& uid) const {
    return boost::hash<boost::uuids::uuid>()(uid);
  }
};
/// \brief Hash operation for \ref Offset.
template <> struct hash<gtirb::Offset> {
  size_t operator()(const gtirb::Offset& x) const {
    std::size_t seed = 0;
    boost::hash_combine(seed, x.ElementId);
    boost::hash_combine(seed, x.Displacement);
    return seed;
  }
};
} // namespace std

#endif // GTIRB_BLOCK_H
