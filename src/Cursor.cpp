#include "Cursor.h"

#include "./service/stdex/stdex.h"

#include <cstring>
#include <functional>

namespace PhWidgets
{
    CursorDef::CursorDef(Cursors::eCursors cursor):
        _def(nullptr),
        _cursor(cursor)
    { }

    CursorDef::CursorDef(const PhCursorDef_t &def):
        _def(new PhCursorDef_t())
    { 
        (*_def) = def;
    }

    CursorDef::CursorDef(const CursorDef &other):
        _def(nullptr)
    {
        if(nullptr != other._def)
        {
            _def = new PhCursorDef_t();
            (*_def) = (*other._def);

            return;
        }

        _cursor = other._cursor;
    }
    
    CursorDef::~CursorDef()
    {
        delete _def;
    }
    
    CursorDef &CursorDef::operator=(const CursorDef &other)
    {
        if(&other == this)
            return *this;

        if(nullptr != other._def)
        {
            if(nullptr == _def)
                _def = new PhCursorDef_t();
            (*_def) = (*other._def);

            return *this;
        }
        
        
        delete _def;
        _def = nullptr;
        _cursor = other._cursor;

        return *this;
    }

    bool CursorDef::operator==(const CursorDef &other) const
    {
        if(&other == this)
            return true;
        
        if(other._def == _def)
        {
            if(nullptr != _def)
                return true;
            return other._cursor == _cursor;
        }
        
        if(nullptr != other._def && nullptr != _def)
            return std::memcmp(other._def, _def, sizeof(*_def)) == 0;
        
        return false;
    }

    bool CursorDef::operator!=(const CursorDef &other) const
    {
        return !(*this == other);
    }

    bool CursorDef::operator<(const CursorDef &other) const
    {
        if(&other == this)
            return false;
        
        if(nullptr == other._def && nullptr == _def)
            return _cursor < other._cursor;
        
        
        if(nullptr != other._def && nullptr != _def) 
            return std::memcmp(other._def, _def, sizeof(*_def));

        return std::less<PhCursorDef_t*>()(_def, other._def);
    }

    CursorDef::operator const PhCursorDef_t*() const
    {
        return _def;
    }


    bool operator==(const Cursors::eCursors &lhs, const CursorDef &other)
    {
        return rhs == lhs;
    }

    bool operator!=(const Cursors::eCursors &lhs, const CursorDef &other)
    {
        return rhs != lhs;
    }

    bool operator<(const Cursors::eCursors &lhs, const CursorDef &other)
    {
        return CursorDef(lhs) < rhs;
    }
}
