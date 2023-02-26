#include "GG/Core/Utility/StringID.h"

#include <algorithm>

using namespace gg;

#if OPTIMISE_STRINGID_MEMORY
std::string NOT_AVAILABLE = "NOT_AVAILABLE";
#endif

CStringID::CStringID()
{
}

CStringID::CStringID(const std::string& string)
{
    *this = string;
}

bool CStringID::operator==(const CStringID& other) const
{
    return _hash == other._hash;
}

bool CStringID::operator!=(const CStringID& other) const
{
    return _hash != other._hash;
}

void CStringID::operator=(const std::string& string)
{
    _hash = std::hash<std::string>{}(string);
#if !OPTIMISE_STRINGID_MEMORY
    _value = string;
#endif
}

CStringID::operator size_t() const
{
    return _hash;
}

const std::string& CStringID::String() const
{
#if OPTIMISE_STRINGID_MEMORY
    return NOT_AVAILABLE;
#else
    return _value;
#endif
}