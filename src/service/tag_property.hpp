#ifndef TAG_PROPERTY_H
#define TAG_PROPERTY_H

#include "./stdex/stdex.h"
#include <cstddef>

namespace PhWidgets
{
    template<
        class ParentT, 
        const void*(ParentT::*Getter)()const, 
        void(ParentT::*Setter)(const void*, std::size_t)
    >
    class tag_property
    {
        template<unsigned N, bool = true> struct priority_tag : priority_tag < N - 1 > {};
        template<bool dummy> struct priority_tag<0, dummy> {};

        typedef const void* value_t;

    public:
        tag_property(ParentT *parent) :
            _obj(parent)
        { }

        inline 
        void set(value_t value, std::size_t size)
        {
            if(value)
                (_obj->*Setter)(value, size);
            else
                (_obj->*Setter)(value, 0);
        }

        template<class T, std::size_t count>
        inline
        void set(const T(&value)[count])
        {
            (_obj->*Setter)(value, count * sizeof(T));
        }

        template<class T>
        inline
        void set(const T &value)
        {
            set_value(value, priority_tag<2>());
        }       

        inline
        value_t get() const
        {
            return (_obj->*Getter)();
        }

        inline 
        operator value_t() const { return get(); }
        
        template<class T>
        inline 
        operator const T*() const { return reinterpret_cast<const T*>( get() ); }
        
        template<class T, std::size_t count>
        inline 
        tag_property &operator=(const T(&value)[count]) { set(value); return *this; }

        template<class T>
        inline
        tag_property &operator=(const T &value) { set(value); return *this; }

        inline 
        value_t operator()(void) const { return get(); }

        template<class T>
        inline 
        value_t operator()(void) const { return reinterpret_cast<const T*>( get() ); }

        inline 
        void operator()(value_t value, std::size_t size) { set(value, size); }

        template<class T, std::size_t count>
        inline
        void operator()(const T(&value)[count]) { set(value); }

        template<class T>
        inline
        void operator()(const T &value) { set(value); }

    private:
        ParentT *_obj;
        
        tag_property(const tag_property &);
        
        template<
            class OtherParentT, 
            class OtherValueT, 
            OtherValueT (OtherParentT::*OtherGetter)() const, 
            template <
                class, 
                class, 
                OtherValueT (OtherParentT::*)() const
            > class T
        >
        inline
        void set_value(const T<OtherParentT, OtherValueT, OtherGetter> &value, priority_tag<2>)
        {
            const OtherValueT tmp = value.get();
            (_obj->*Setter)(&tmp, sizeof(OtherValueT));
        }

        template<
            class OtherParentT, 
            class OtherValueT, 
            OtherValueT (OtherParentT::*OtherGetter)() const, 
            void (OtherParentT::*OtherSetter)(OtherValueT),
            template <
                class, 
                class, 
                OtherValueT (OtherParentT::*)() const,
                void (OtherParentT::*)(OtherValueT)
            > class T
        >
        inline
        void set_value(const T<OtherParentT, OtherValueT, OtherGetter, OtherSetter> &value, priority_tag<1>)
        {
            const OtherValueT tmp = value.get();
            (_obj->*Setter)(&tmp, sizeof(OtherValueT));
        }

        template<class T>
        inline
        void set_value(T value, priority_tag<0>)
        {
            (_obj->*Setter)(&value, sizeof(T));
        }
    };
}


#endif // TAG_PROPERTY_H