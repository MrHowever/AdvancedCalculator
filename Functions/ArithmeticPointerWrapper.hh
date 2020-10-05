#ifndef FUNCTIONS_ARITHMETICPOINTERWRAPPER_HH
#define FUNCTIONS_ARITHMETICPOINTERWRAPPER_HH

#include <cstddef>
#include "Typedefs.hh"
#include <typeinfo>

namespace MC::FN
{
    class ArithmeticObject;

    template<typename T>
    class PointerWrapper {
        T* _ptr;

    public:
        PointerWrapper();
        PointerWrapper(T*);
        PointerWrapper(const T*);
        PointerWrapper(const PointerWrapper&);
        PointerWrapper(std::nullptr_t);
        PointerWrapper& operator=(std::nullptr_t);
        PointerWrapper& operator=(const PointerWrapper&);
        PointerWrapper& operator=(T*);

        bool operator==(const PointerWrapper&);

        T& operator*();
        const T& operator*() const;
        T* operator->();
        const T* const operator->() const;


        template<ArithmeticRef Type> const Type& toRef() const;

        void Delete();

        template<Arithmetic P> PointerWrapper<P> cast() const;
        T* get() const;

        const PointerWrapper copyObject() const;

        explicit operator bool();
        explicit operator bool() const;
        template<typename To> operator PointerWrapper<To>();
        template<typename To> operator PointerWrapper<To>() const;
    };

    class Division;
    class Value;
    class Sum;
    class ArithmeticObject;
    class Multiplication;
    class Variable;
    class Exponentiation;

    typedef PointerWrapper<ArithmeticObject> ArithmeticPointerWrapper;
    typedef PointerWrapper<Division> DivisionPointerWrapper;
    typedef PointerWrapper<Value> ValuePointerWrapper;
    typedef PointerWrapper<Sum> SumPointerWrapper;
    typedef PointerWrapper<Multiplication> MultiplicationPointerWrapper;
    typedef PointerWrapper<Variable> VariablePointerWrapper;
    typedef PointerWrapper<Exponentiation> ExponentiationPointerWrapper;

    template<typename T>
    template<Arithmetic P>
    PointerWrapper<P> PointerWrapper<T>::cast() const
    {
        return PointerWrapper<P>((P*) _ptr);
    }

    template<typename T>
    T* PointerWrapper<T>::get() const
    {
        return _ptr;
    }

    template<typename T>
    template<ArithmeticRef Type>
    const Type& PointerWrapper<T>::toRef() const
    {
        return *static_cast<Type*>(_ptr);
    }
}

#endif //FUNCTIONS_ARITHMETICPOINTERWRAPPER_HH