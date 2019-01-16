#ifndef TAG_PROPERTY_H
#define TAG_PROPERTY_H

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
            //const T *tmp = new T(value);
            (_obj->*Setter)(&value, sizeof(T));
            //delete tmp;
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
    };
}


#endif // TAG_PROPERTY_H