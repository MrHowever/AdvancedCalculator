#include "ArithmeticPointerWrapper.hh"
#include "Sum.hh"
#include "Multiplication.hh"
#include "Division.hh"
#include "Value.hh"
#include "Variable.hh"
#include "Exponentiation.hh"

namespace MC::FN
{
    template<typename T>
    PointerWrapper<T>::PointerWrapper() : _ptr(nullptr) {}

    template<typename T>
    PointerWrapper<T>::PointerWrapper(T* ptr) : _ptr(ptr) {}

    template<typename T>
    PointerWrapper<T>::PointerWrapper(const PointerWrapper& wrap) : _ptr(wrap._ptr) {}

    template<typename T>
    PointerWrapper<T>::PointerWrapper(std::nullptr_t) : _ptr(nullptr) {}

    template<typename T>
    bool PointerWrapper<T>::operator==(const PointerWrapper<T>& p)
    {
        return _ptr == p._ptr;
    }

    template<typename T>
    PointerWrapper<T>& PointerWrapper<T>::operator=(const PointerWrapper& wrap)
    {
        Delete();
        _ptr = wrap._ptr;
        return *this;
    }

    template<typename T>
    T& PointerWrapper<T>::operator*()
    {
        return *_ptr;
    }

    template<typename T>
    T* PointerWrapper<T>::operator->()
    {
        return _ptr;
    }

    template<typename T>
    const T* const PointerWrapper<T>::operator->() const
    {
        return _ptr;
    }

    template<typename T>
    void PointerWrapper<T>::Delete()
    {
        delete _ptr;
        _ptr = nullptr;
    }

    template<typename T>
    PointerWrapper<T>& PointerWrapper<T>::operator=(std::nullptr_t)
    {
        _ptr = nullptr;
        return *this;
    }

    template<typename T>
    PointerWrapper<T>::operator bool()
    {
        return _ptr;
    }

    template<typename T>
    PointerWrapper<T>::operator bool() const
    {
        return _ptr;
    }

    template<typename T>
    template<typename To>
    PointerWrapper<T>::operator PointerWrapper<To>()
    {
        PointerWrapper<To> result;
        result = (To*) this->get();
        return result;
    }

    template<typename T>
    template<typename To>
    PointerWrapper<T>::operator PointerWrapper<To>() const
    {
        PointerWrapper<To> result;
        result = (To*) this->get();
        return result;
    }

    template<typename T>
    PointerWrapper<T>& PointerWrapper<T>::operator=(T* ptr)
    {
        Delete();
        _ptr = ptr;
        return *this;
    }

    template<typename T>
    const T& PointerWrapper<T>::operator*() const
    {
        return *_ptr;
    }

    template<typename T>
    PointerWrapper<T>::PointerWrapper(const T* ptr) : _ptr(const_cast<T*>(ptr)) {}

    template<typename T>
    const PointerWrapper<T> PointerWrapper<T>::copyObject() const
    {
        PointerWrapper<T> result;

        if constexpr(not std::is_same_v<T,ArithmeticObject>) {
            result._ptr =  new T(*_ptr);
        } else {
            switch (_ptr->getType()) {
                case SUM:
                    result._ptr = new Sum(*dynamic_cast<const Sum*>(_ptr)); break;
                case MUL:
                    result._ptr = new Multiplication(*dynamic_cast<const Multiplication*>(_ptr)); break;
                case DIV:
                    result._ptr = new Division(*dynamic_cast<const Division*>(_ptr)); break;
                case VAR:
                    result._ptr = new Variable(*dynamic_cast<const Variable*>(_ptr)); break;
                case VAL:
                    result._ptr = new Value(*dynamic_cast<const Value*>(_ptr)); break;
                case EXP:
                    result._ptr = new Exponentiation(*dynamic_cast<const Exponentiation*>(_ptr)); break;

                default:
                    throw InvalidOperationException("Type not handled");
            }
        }

        return result;
    }

    // TODO seriously XD

    template class PointerWrapper<ArithmeticObject>;
    template class PointerWrapper<Sum>;
    template class PointerWrapper<Multiplication>;
    template class PointerWrapper<Division>;
    template class PointerWrapper<Variable>;
    template class PointerWrapper<Value>;
    template class PointerWrapper<Exponentiation>;

    template PointerWrapper<ArithmeticObject>::operator PointerWrapper<Sum>();
    template PointerWrapper<ArithmeticObject>::operator PointerWrapper<Division>();
    template PointerWrapper<ArithmeticObject>::operator PointerWrapper<Multiplication>();
    template PointerWrapper<ArithmeticObject>::operator PointerWrapper<Exponentiation>();
    template PointerWrapper<ArithmeticObject>::operator PointerWrapper<Variable>();
    template PointerWrapper<ArithmeticObject>::operator PointerWrapper<Value>();
    template PointerWrapper<ArithmeticObject>::operator PointerWrapper<ArithmeticObject>();

    template PointerWrapper<Sum>::operator PointerWrapper<Sum>();
    template PointerWrapper<Sum>::operator PointerWrapper<Division>();
    template PointerWrapper<Sum>::operator PointerWrapper<Multiplication>();
    template PointerWrapper<Sum>::operator PointerWrapper<Exponentiation>();
    template PointerWrapper<Sum>::operator PointerWrapper<Variable>();
    template PointerWrapper<Sum>::operator PointerWrapper<Value>();
    template PointerWrapper<Sum>::operator PointerWrapper<ArithmeticObject>();


    template PointerWrapper<Division>::operator PointerWrapper<Sum>();
    template PointerWrapper<Division>::operator PointerWrapper<Division>();
    template PointerWrapper<Division>::operator PointerWrapper<Multiplication>();
    template PointerWrapper<Division>::operator PointerWrapper<Exponentiation>();
    template PointerWrapper<Division>::operator PointerWrapper<Variable>();
    template PointerWrapper<Division>::operator PointerWrapper<Value>();
    template PointerWrapper<Division>::operator PointerWrapper<ArithmeticObject>();

    template PointerWrapper<Multiplication>::operator PointerWrapper<Sum>();
    template PointerWrapper<Multiplication>::operator PointerWrapper<Division>();
    template PointerWrapper<Multiplication>::operator PointerWrapper<Multiplication>();
    template PointerWrapper<Multiplication>::operator PointerWrapper<Exponentiation>();
    template PointerWrapper<Multiplication>::operator PointerWrapper<Variable>();
    template PointerWrapper<Multiplication>::operator PointerWrapper<Value>();
    template PointerWrapper<Multiplication>::operator PointerWrapper<ArithmeticObject>();


    template PointerWrapper<Exponentiation>::operator PointerWrapper<Sum>();
    template PointerWrapper<Exponentiation>::operator PointerWrapper<Division>();
    template PointerWrapper<Exponentiation>::operator PointerWrapper<Multiplication>();
    template PointerWrapper<Exponentiation>::operator PointerWrapper<Exponentiation>();
    template PointerWrapper<Exponentiation>::operator PointerWrapper<Variable>();
    template PointerWrapper<Exponentiation>::operator PointerWrapper<Value>();
    template PointerWrapper<Exponentiation>::operator PointerWrapper<ArithmeticObject>();


    template PointerWrapper<Value>::operator PointerWrapper<Sum>();
    template PointerWrapper<Value>::operator PointerWrapper<Division>();
    template PointerWrapper<Value>::operator PointerWrapper<Multiplication>();
    template PointerWrapper<Value>::operator PointerWrapper<Exponentiation>();
    template PointerWrapper<Value>::operator PointerWrapper<Variable>();
    template PointerWrapper<Value>::operator PointerWrapper<Value>();
    template PointerWrapper<Value>::operator PointerWrapper<ArithmeticObject>();


    template PointerWrapper<Variable>::operator PointerWrapper<Sum>();
    template PointerWrapper<Variable>::operator PointerWrapper<Division>();
    template PointerWrapper<Variable>::operator PointerWrapper<Multiplication>();
    template PointerWrapper<Variable>::operator PointerWrapper<Exponentiation>();
    template PointerWrapper<Variable>::operator PointerWrapper<Variable>();
    template PointerWrapper<Variable>::operator PointerWrapper<Value>();
    template PointerWrapper<Variable>::operator PointerWrapper<ArithmeticObject>();


    template PointerWrapper<ArithmeticObject>::operator PointerWrapper<Sum>() const;
    template PointerWrapper<ArithmeticObject>::operator PointerWrapper<Division>() const;
    template PointerWrapper<ArithmeticObject>::operator PointerWrapper<Multiplication>() const;
    template PointerWrapper<ArithmeticObject>::operator PointerWrapper<Exponentiation>() const;
    template PointerWrapper<ArithmeticObject>::operator PointerWrapper<Variable>() const;
    template PointerWrapper<ArithmeticObject>::operator PointerWrapper<Value>() const;
    template PointerWrapper<ArithmeticObject>::operator PointerWrapper<ArithmeticObject>() const;

    template PointerWrapper<Sum>::operator PointerWrapper<Sum>() const;
    template PointerWrapper<Sum>::operator PointerWrapper<Division>() const;
    template PointerWrapper<Sum>::operator PointerWrapper<Multiplication>() const;
    template PointerWrapper<Sum>::operator PointerWrapper<Exponentiation>() const;
    template PointerWrapper<Sum>::operator PointerWrapper<Variable>() const;
    template PointerWrapper<Sum>::operator PointerWrapper<Value>() const;
    template PointerWrapper<Sum>::operator PointerWrapper<ArithmeticObject>() const;

    template PointerWrapper<Division>::operator PointerWrapper<Sum>() const;
    template PointerWrapper<Division>::operator PointerWrapper<Division>() const;
    template PointerWrapper<Division>::operator PointerWrapper<Multiplication>() const;
    template PointerWrapper<Division>::operator PointerWrapper<Exponentiation>() const;
    template PointerWrapper<Division>::operator PointerWrapper<Variable>() const;
    template PointerWrapper<Division>::operator PointerWrapper<Value>() const;
    template PointerWrapper<Division>::operator PointerWrapper<ArithmeticObject>() const;

    template PointerWrapper<Multiplication>::operator PointerWrapper<Sum>() const;
    template PointerWrapper<Multiplication>::operator PointerWrapper<Division>() const;
    template PointerWrapper<Multiplication>::operator PointerWrapper<Multiplication>() const;
    template PointerWrapper<Multiplication>::operator PointerWrapper<Exponentiation>() const;
    template PointerWrapper<Multiplication>::operator PointerWrapper<Variable>() const;
    template PointerWrapper<Multiplication>::operator PointerWrapper<Value>() const;
    template PointerWrapper<Multiplication>::operator PointerWrapper<ArithmeticObject>() const;

    template PointerWrapper<Exponentiation>::operator PointerWrapper<Sum>() const;
    template PointerWrapper<Exponentiation>::operator PointerWrapper<Division>() const;
    template PointerWrapper<Exponentiation>::operator PointerWrapper<Multiplication>() const;
    template PointerWrapper<Exponentiation>::operator PointerWrapper<Exponentiation>() const;
    template PointerWrapper<Exponentiation>::operator PointerWrapper<Variable>() const;
    template PointerWrapper<Exponentiation>::operator PointerWrapper<Value>() const;
    template PointerWrapper<Exponentiation>::operator PointerWrapper<ArithmeticObject>() const;

    template PointerWrapper<Value>::operator PointerWrapper<Sum>() const;
    template PointerWrapper<Value>::operator PointerWrapper<Division>() const;
    template PointerWrapper<Value>::operator PointerWrapper<Multiplication>() const;
    template PointerWrapper<Value>::operator PointerWrapper<Exponentiation>() const;
    template PointerWrapper<Value>::operator PointerWrapper<Variable>() const;
    template PointerWrapper<Value>::operator PointerWrapper<Value>() const;
    template PointerWrapper<Value>::operator PointerWrapper<ArithmeticObject>() const;

    template PointerWrapper<Variable>::operator PointerWrapper<Sum>() const;
    template PointerWrapper<Variable>::operator PointerWrapper<Division>() const;
    template PointerWrapper<Variable>::operator PointerWrapper<Multiplication>() const;
    template PointerWrapper<Variable>::operator PointerWrapper<Exponentiation>() const;
    template PointerWrapper<Variable>::operator PointerWrapper<Variable>() const;
    template PointerWrapper<Variable>::operator PointerWrapper<Value>() const;
    template PointerWrapper<Variable>::operator PointerWrapper<ArithmeticObject>() const;
}