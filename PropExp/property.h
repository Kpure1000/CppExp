#ifndef PROPERTY_H
#define PROPERTY_H

#ifndef CLS_NAME
#define CLS_NAME(name) Property_##name
#endif

#ifndef PROP_CORE
    #define PROP_CORE(_type, _val, setter, getter) \
    struct CLS_NAME(_val) { \
        _type value;\
        CLS_NAME(_val)(CLS_NAME(_val)&&) = delete; \
        CLS_NAME(_val)(const CLS_NAME(_val)&) = delete; \
        CLS_NAME(_val)(_type&& value): value(value) { \
        } \
        CLS_NAME(_val)(const _type& value): value(value) { \
        } \
        setter \
        getter \
    };\
    CLS_NAME(_val) _val
#endif // !PROP_CORE

#ifndef PROP_WR
    #define PROP_WR(_type, _val, setter, getter) PROP_CORE(_type, _val, \
        inline _type operator=(const _type& value) {\
            setter\
            return this->value;\
        }\
        inline _type operator=(_type&& value) {\
            setter\
            return this->value;\
        },\
        inline operator _type() const {\
            getter\
        }\
    )
#endif // !PROP_WR

#ifndef PROP_W
    #define PROP_W(_type, _val, setter) PROP_CORE(_type, _val, \
        inline _type operator=(const _type& value) {\
            setter\
            return this->value;\
        }\
        inline _type operator=(_type&& value) {\
            setter\
            return this->value;\
        },\
        operator _type() const = delete; \
    )
#endif // !PROP_W

#ifndef PROP_R
    #define PROP_R(_type, _val, getter) PROP_CORE(_type, _val, \
        _type operator=(const _type& value) = delete;\
        _type operator=(_type&& value) = delete;, \
        inline operator _type() const {\
            getter\
        }\
    )
#endif // !PROP_R

#endif // !PROPERTY_H