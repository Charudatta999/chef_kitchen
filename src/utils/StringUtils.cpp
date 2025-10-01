#include "StringUtils.hpp"

namespace util
{
std::string GetUUID()
{
    Poco::UUIDGenerator& generator = Poco::UUIDGenerator::defaultGenerator();    
    Poco::UUID uuid = generator.createRandom();
    return uuid.toString();
}
}