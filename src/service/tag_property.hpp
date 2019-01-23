#ifndef TAG_PROPERTY_H
#define TAG_PROPERTY_H

#include <cstddef>
#include <map>
#include <set>

namespace PhWidgets
{
    namespace
    {
        namespace type_traits
        {
            template<bool>
            struct void_enable_if { typedef void type; };

            template<>
            struct void_enable_if<false> { };

            template<class T>
            struct remove_cv { typedef T type; };

            template<class T>
            struct remove_cv<const T> { typedef typename remove_cv<T>::type type; };

            template<class T>
            struct remove_cv<volatile T> { typedef typename remove_cv<T>::type type; };

            template<class, class>
            struct is_same
            { static const bool value = false; };

            template<class T>
            struct is_same<T, T>
            { static const bool value = true; };

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
                typedef typename remove_cv<T>::type type;
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
        
    public:
        typedef const void* value_type;

        tag_property(ObjectT *obj) :
            _obj(obj)
        { }

        inline 
        void set(value_type value, std::size_t size)
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
        value_type get() const
        {
            return get_ptr( value_type() );
        }

        template<class T>
        inline 
        const T* get() const
        {
            typedef const T* type;
            return get_ptr( type() );
        }

        template<class T>
        inline 
        operator const T*() const { return get<T>(); }
        
        template<class T, std::size_t count>
        inline 
        tag_property &operator=(const T(&value)[count]) { set(value); return *this; }

        template<class T>
        inline
        tag_property &operator=(const T &value) { set(value); return *this; }

        inline 
        value_type operator()(void) const { return get(); }

        inline 
        void operator()(value_type value, std::size_t size) { set(value, size); }

        template<class T, std::size_t count>
        inline
        void operator()(const T(&value)[count]) { set(value); }

        template<class T>
        inline
        void operator()(const T &value) { set(value); }

        template<
            class OtherObjectT, 
            const void*(OtherObjectT::*OtherGetter)()const, 
            void(OtherObjectT::*OtherSetter)(const void*, std::size_t)
        >
        inline
        bool operator==(const tag_property<OtherObjectT, OtherGetter, OtherSetter> &other) 
        { 
            value_type tmp = other.get(); 
            return (get() == tmp); 
        }

        template<
            class OtherObjectT, 
            const void*(OtherObjectT::*OtherGetter)()const, 
            void(OtherObjectT::*OtherSetter)(const void*, std::size_t)
        >
        inline
        bool operator!=(const tag_property<OtherObjectT, OtherGetter, OtherSetter> &other) 
        { 
            value_type tmp = other.get(); 
            return (get() != tmp); 
        }

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
            set_ptr(&tmp, sizeof(OtherValueT), priority_tag<3>());
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
            set_ptr(&tmp, sizeof(OtherValueT), priority_tag<3>());
        }

        template<class T>
        inline
        void set_value_from_get(T value)
        {
            set_ptr(&value, sizeof(T), priority_tag<3>());
        }

        template<class T>
        inline
        typename type_traits::void_enable_if<
            type_traits::has_getter<T>::value
        >::type set_value(T &value, priority_tag<1>)
        {
            set_value_from_get(value.get());
        }

        template<class T>
        inline
        void set_value(T value, priority_tag<0>)
        {
            set_ptr(&value, sizeof(T), priority_tag<3>());
        }


        inline
        void set_ptr(value_type value, std::size_t size, priority_tag<0>)
        {
            (_obj->*Setter)(value, size);
        }

        inline
        value_type get_ptr(value_type) const
        {
            return (_obj->*Getter)();
        }

        // 'remember' types passed:
        #if !defined(NDEBUG) || defined(_DEBUG) || defined(DEBUG)
        #define PH_WIDGETS_DEBUG_BUILD
        #endif

        #ifdef PH_WIDGETS_DEBUG_BUILD
        template<class>
        static void type_id_func() {}

        typedef std::map<value_type, std::set<void (*)()> > map_type;

        static map_type &tag_pointers()
        {
            static map_type ptr_map_;
            return ptr_map_;
        }
        #endif

        template<class T>
        inline
        typename type_traits::remove_cv<T>
        ::type const get_ptr(T) const
        {
            typedef typename type_traits::remove_cv<T>::type const type;

            value_type value = (_obj->*Getter)();
            type result = reinterpret_cast<type>(value);

            #ifdef PH_WIDGETS_DEBUG_BUILD
            {
                static map_type &ptr_map = tag_pointers();
                
                map_type::iterator it = ptr_map.find(value);
                if(ptr_map.end() != it)
                {
                    if(!value)
                        ptr_map.erase(it);
                    else
                    {
                        if( it->second.find(&type_id_func<type>) == it->second.end() )
                        {
                            #ifdef NULL
                                return NULL;
                            #else
                                return 0;
                            #endif
                        }
                    }
                }
            }
            #endif

            return result;
        }

        template<class T>
        inline 
        typename type_traits::void_enable_if<
            false == type_traits::is_same<const T*, const void*>::value
        >::type set_ptr(const T *value, std::size_t size, priority_tag<1>)
        {
            typedef typename type_traits::remove_cv<T>::type const type;

            (_obj->*Setter)(value, size);

            #ifdef PH_WIDGETS_DEBUG_BUILD
            {
                value = get_ptr(value);

                static map_type &ptr_map = tag_pointers();

                map_type::iterator it = ptr_map.find(value);

                if(ptr_map.end() != it)
                {
                    if(!value)
                        ptr_map.erase(it);
                    else
                        it->second.insert(&type_id_func<type>);
                }
                else
                {
                    if(value)
                    {
                        map_type::mapped_type second;
                        second.insert(&type_id_func<type>);
                        ptr_map.insert(std::make_pair(value, second));
                    }
                }
            }
            #endif
        }
    };

    template<
        class ObjectT, 
        const void*(ObjectT::*Getter)()const, 
        void(ObjectT::*Setter)(const void*, std::size_t),
        class T
    >
    inline
    bool operator==(const tag_property<ObjectT, Getter, Setter> &lhs, const T &rhs) { const T *tmp = lhs; return (&rhs == tmp); }

    template<
        class ObjectT, 
        const void*(ObjectT::*Getter)()const, 
        void(ObjectT::*Setter)(const void*, std::size_t),
        class T
    >
    inline
    bool operator==(const T &lhs, const tag_property<ObjectT, Getter, Setter> &rhs) { const T *tmp = rhs; return (&lhs == tmp); }
    

    template<
        class ObjectT, 
        const void*(ObjectT::*Getter)()const, 
        void(ObjectT::*Setter)(const void*, std::size_t),
        class T
    >
    inline
    bool operator!=(const tag_property<ObjectT, Getter, Setter> &lhs, const T &rhs) { const T *tmp = lhs; return (&rhs != tmp); }

    template<
        class ObjectT, 
        const void*(ObjectT::*Getter)()const, 
        void(ObjectT::*Setter)(const void*, std::size_t),
        class T
    >
    inline
    bool operator!=(const T &lhs, const tag_property<ObjectT, Getter, Setter> &rhs) { const T *tmp = rhs; return (&lhs != tmp); }    
}

#ifdef PH_WIDGETS_DEBUG_BUILD
#undef PH_WIDGETS_DEBUG_BUILD
#endif


#endif // TAG_PROPERTY_H