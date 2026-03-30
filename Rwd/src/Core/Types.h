/**
 * < Rewind Engine > Types.h
 * Author: DeckardZ46
 * Date: 2024/08/30
 * Note: This file includes customized type & containers in Rewind Engine
 * Codebase: https://github.com/DeckardZ46/RewindEngine
 */
#pragma once

#include <memory>
#include <mutex>
#include <vector>
#include <cstdint>
#include <string>
#include <unordered_map>

#include <Core/Containers/CircularQueue.hpp>

/**
 *  For now it's just a wrapper for STL types and containers, maybe replace them with other implementation in the future
 */
namespace Rwd {
// types
using float64   = double;
using uint      = unsigned int;
using uint8     = std::uint8_t;
using uint16    = std::uint16_t;
using uint32    = std::uint32_t;
using uint64    = std::uint64_t;

// containers
template <typename k, typename v, typename hash = std::hash<k>> using RHashmap = std::unordered_map<k, v, hash>;
template <typename T> using RCqueue = CircularQueue<T>;
template <typename T> using RSafeCqueue = SafeCircularQueue<T>;

// smart pointers
template <typename T> using RUniquePtr = std::unique_ptr<T>;
template <typename T> using RSharedPtr = std::shared_ptr<T>;
template <typename T> using RWeakPtr = std::weak_ptr<T>;

template <typename T, typename... Args> RUniquePtr<T> make_unique(Args &&...args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args> RSharedPtr<T> make_shared(Args &&...args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}


} // namespace Rwd