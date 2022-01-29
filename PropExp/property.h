#ifndef PROPERTY_H
#define PROPERTY_H

#ifndef CLS_NAME
#define CLS_NAME(name) Property_##name
#endif

#ifndef PROP_CORE
    #define PROP_CORE(_cls, _type, _val, setter, getter) \
    struct CLS_NAME(_val) { \
        CLS_NAME(_val)(CLS_NAME(_val)&&) = delete; \
        CLS_NAME(_val)(const CLS_NAME(_val)&) = delete; \
        CLS_NAME(_val)(_type&& value): _val(value) { \
        } \
        CLS_NAME(_val)(const _type& value): _val(value) { \
        } \
        setter \
        getter \
        private: \
        friend _cls;\
        _type _val;\
    };\
    CLS_NAME(_val) _val
#endif // !PROP_CORE

#ifndef PROP_WR
    #define PROP_WR(_cls, _type, _val, setter, getter) PROP_CORE(_cls, _type, _val, \
        inline _type operator=(const _type& value) {\
            setter\
            return this->_val;\
        }\
        inline _type operator=(_type&& value) {\
            setter\
            return this->_val;\
        },\
        inline operator _type() const {\
            getter\
        }\
    )
#endif // !PROP_WR

#ifndef PROP_W
    #define PROP_W(_cls, _type, _val, setter) PROP_CORE(_cls, _type, _val, \
        inline _type operator=(const _type& value) {\
            setter\
            return this->_val;\
        }\
        inline _type operator=(_type&& value) {\
            setter\
            return this->_val;\
        },\
        operator _type() const = delete; \
    )
#endif // !PROP_W

#ifndef PROP_R
    #define PROP_R(_cls, _type, _val, getter) PROP_CORE(_cls, _type, _val, \
        _type operator=(const _type& value) = delete;\
        _type operator=(_type&& value) = delete;, \
        inline operator _type() const {\
            getter\
        }\
    )
#endif // !PROP_R

#endif // !PROPERTY_H