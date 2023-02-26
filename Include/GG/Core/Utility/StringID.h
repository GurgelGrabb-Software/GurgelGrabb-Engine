#pragma once

#include <string>

#define OPTIMISE_STRINGID_MEMORY 0

namespace gg
{
    class CStringID
    {
    public:
        CStringID();
        CStringID(const std::string& string);

        bool operator==(const CStringID& other) const;
        bool operator!=(const CStringID& other) const;

        void operator=(const std::string& string);

        operator size_t() const;

        const std::string& String() const;

    private:
        size_t _hash;
#if !OPTIMISE_STRINGID_MEMORY
        std::string _value;
#endif
    };

}