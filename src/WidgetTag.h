#ifndef PT_WIDGET_TAG_H
#define PT_WIDGET_TAG_H

#include "./service/stdex/stdex.h"
#include <cstddef>

namespace PhWidgets
{
    class WidgetTag
    {
    public:
        template<class T>
        WidgetTag(const T *tag):
            _tag(tag),
            _size(tag == nullptr ? 0 : sizeof(T))
        { }

        template<class T, std::size_t count>
        WidgetTag(const T(&arr)[count]):
            _tag(arr),
            _size(count * sizeof(T))
        { }

        WidgetTag(const void *tag, std::size_t size):
            _tag(tag),
            _size(tag == nullptr ? 0 : size)
        { }

        template<class T>
        operator const T*() const
        {
            if(sizeof(T) == _size)
                return _tag;
            return nullptr;
        }

        operator const void*() const
        {
            return _tag;
        }

    private:
        WidgetTag(const void *tag):
            _tag(tag),
            _size(0)
        { }
        
        const void *_tag;
        std::size_t _size;

        friend class Widget;
    };
}


#endif // PT_WIDGET_TAG_H