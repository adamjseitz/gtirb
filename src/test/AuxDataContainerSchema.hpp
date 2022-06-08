#ifndef AUX_DATA_CONTAINER_SCHEMA_HPP
#define AUX_DATA_CONTAINER_SCHEMA_HPP

#include <gtirb/AuxData.hpp>
#include <cstdint>

// Schema for AuxDataContainer's unit tests

namespace gtirb {
namespace schema {

struct RegisteredType {
  static constexpr const char* Name = "registered type";
  typedef int64_t Type;
};

struct UnRegisteredType {
  static constexpr const char* Name = "unregistered type";
  typedef int64_t Type;
};

struct DuplicateNameType {
  static constexpr const char* Name = "registered type";
  typedef int32_t Type;
};

struct BadDeSerializationType {
  static constexpr const char* Name = "bad deserialization type";
  typedef struct {
    int32_t x;
    int32_t y;
  } Type;
};

} // namespace schema

// The BadDeSerializationType schema will serialize but will fail to
// deserialize. This models several situations that a client of
// GTIRB might be in:
//
// 1) They incorrectly implement their custom auxdata_traits<> for
// their custom schema.
//
// 2) They are processing a GTIRB file generated by a different
// client that used an incompatible schema. In which case, when they
// attempt to unserialize the AuxData, it will fail to unserialize
// even though they have a schema registered for it.
//
// 3) They are processing a GTIRB file that's just outright corrupted.
template <> struct auxdata_traits<schema::BadDeSerializationType::Type> {
  using T = schema::BadDeSerializationType::Type;
  static void toBytes(const T& Object, ToByteRange& TBR) {
    // Store as little-endian.
    T reversed = boost::endian::conditional_reverse<
        boost::endian::order::little, boost::endian::order::native>(Object);
    auto srcBytes_begin = reinterpret_cast<std::byte*>(&reversed);
    auto srcBytes_end = reinterpret_cast<std::byte*>(&reversed + 1);
    std::for_each(srcBytes_begin, srcBytes_end, [&](auto b) { TBR.write(b); });
  }

  static bool fromBytes(T& Object [[maybe_unused]],
                        FromByteRange& FBR [[maybe_unused]]) {
    // Fail to deserialize.
    return false;
  }

  static std::string type_name() { return "badbadbad"; }
};

} // namespace gtirb

#endif // AUX_DATA_CONTAINER_SCHEMA_HPP
