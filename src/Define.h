#pragma once

#include <memory>
#include <cstdint>

#define NODISCARD [[nodiscard]]
#define MAYBE_UNUSED [[maybe_unused]]

//! A shorthand definition for static_cast<>
#define CAST static_cast
//! A shorthand definition for dynamic_cast<>
#define D_CAST dynamic_cast
//! A shorthand definition for const_cast<>
#define C_CAST const_cast
//! A shorthand definition for reinterpret_cast<>
#define R_CAST reinterpret_cast
#define PTR_CAST std::dynamic_pointer_cast

#define SHORT_CAST(x)   CAST<int16_t>(x)
#define INT_CAST(x)     CAST<int32_t>(x)
#define INT64_CAST(x)   CAST<int64_t>(x)
#define BYTE_CAST(x)    CAST<uint8_t>(x)
#define USHORT_CAST(x)  CAST<uint16_t>(x)
#define UINT_CAST(x)    CAST<uint32_t>(x)
#define UINT64_CAST(x)  CAST<uint64_t>(x)
#define FLOAT_CAST(x)   CAST<float>(x)
#define DOUBLE_CAST(x)  CAST<double>(x)
#define SIZE_CAST(x)    CAST<size_t>(x)


using Identifier = uint32_t;

/**
 * Reference counting type. This is just an alias to @c std::shared_ptr.
 */
template<typename T>
using Ref = std::shared_ptr<T>;

/**
 * Auto-release pointer. This is just an alias to @c std::unique_ptr.
 */
template<typename T>
using Ptr = std::unique_ptr<T>;

template<typename T>
using WeakRef = std::weak_ptr<T>;

template<typename T>
bool IsA(T* obj)
{
    return D_CAST<T>(obj) != nullptr;
}