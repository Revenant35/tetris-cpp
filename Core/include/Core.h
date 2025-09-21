#pragma once

#include <string>
#include <functional>
#include <sstream>
#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <fstream>
#include <variant>

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

#define BIT(x) (1 << x)