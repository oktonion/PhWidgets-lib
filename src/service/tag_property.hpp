#ifndef TAG_PROPERTY_H
#define TAG_PROPERTY_H

#include "./stdex/stdex.h"
#include <cstddef>

namespace PhWidgets
{
    namespace
    {
        namespace type_traits
        {
            typedef char yes_type;
            struct no_type {char dummy[8];};

            template<class ObjectT, int> 
            struct sfinae {};

            template<class ObjectT>
            yes_type has_getter_tester(sfinae<ObjectT, sizeof(&ObjectT::get)>*);
            template<class ObjectT>
            no_type has_getter_tester(...);

            template<class T>
            struct has_getter
            {
                typedef typename std::remove_cv<T>::type type;
                static const bool value = sizeof(has_getter_tester<type>(0)) == sizeof(yes_type);
            };
        }
    }

    template<
        class ObjectT, 
        const void*(ObjectT::*Getter)()const, 
        void(ObjectT::*Setter)(const void*, std::size_t)
    >
    class tag_property
    {
        template<unsigned N, bool = true> struct priority_tag : priority_tag < N - 1 > {};
        template<bool dummy> struct priority_tag<0, dummy> {};

        typedef const void* value_t;

    public:
        tag_property(ObjectT *obj) :
            _obj(obj)
        { }

        inline 
        void set(value_t value, std::size_t size)
        {
            if(value)
                set_ptr(value, size);
            else
                set_ptr(value, 0);
        }

        template<class T, std::size_t count>
        inline
        void set(const T(&value)[count])
        {
            set_ptr(value, count * sizeof(T));
        }

        template<class T>
        inline
        void set(T &value)
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
        ObjectT *_obj;
        
        tag_property(const tag_property &);
        
        template<
            class OtherObjectT, 
            class OtherValueT, 
            OtherValueT (OtherObjectT::*OtherGetter)() const, 
            template <
                class, 
                class, 
                OtherValueT (OtherObjectT::*)() const
            > class T
        > // ro cpp property
        inline
        void set_value(const T<OtherObjectT, OtherValueT, OtherGetter> &value, priority_tag<3>)
        {
            const OtherValueT tmp = value;
            set_ptr(&tmp, sizeof(OtherValueT));
        }

        template<
            class OtherObjectT, 
            class OtherValueT, 
            OtherValueT (OtherObjectT::*OtherGetter)() const, 
            void (OtherObjectT::*OtherSetter)(OtherValueT),
            template <
                class, 
                class, 
                OtherValueT (OtherObjectT::*)() const,
                void (OtherObjectT::*)(OtherValueT)
            > class T
        > // rw cpp property
        inline
        void set_value(const T<OtherObjectT, OtherValueT, OtherGetter, OtherSetter> &value, priority_tag<2>)
        {
            const OtherValueT tmp = value;
            set_ptr(&tmp, sizeof(OtherValueT));
        }

        template<class T>
        inline
        void set_value_from_get(T value)
        {
            set_ptr(&value, sizeof(T));
        }

        template<class T>
        inline
        typename std::enable_if<
            type_traits::has_getter<T>::value,
            void
        >::type set_value(T &value, priority_tag<1>)
        {
            set_value_from_get(value.get());
        }

        
        template<class T>
        inline
        void set_value(T value, priority_tag<0>)
        {
            set_ptr(&value, sizeof(T));
        }

        template<class T>
        inline
        void set_ptr(const T *value, std::size_t size)
        {
            (_obj->*Setter)(value, size);
        }
    };
}


#endif // TAG_PROPERTY_H