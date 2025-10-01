#ifndef STRING_UTIL_UUID_GEN_HEADER
#define STRING_UTIL_UUID_GEN_HEADER

#include "Poco/UUIDGenerator.h"

namespace util
{

/// @brief Genrates a random UUID using poco
/// @return uuid string std::string format
std::string GetUUID();
}
#endif
