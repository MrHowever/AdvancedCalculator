#ifndef FUNCTIONS_ASSOCIATIVEOPERATOR_TCC
#define FUNCTIONS_ASSOCIATIVEOPERATOR_TCC

namespace MC::FN
{
    template<typename T>
    void AssociativeOperator::add(std::list<PointerWrapper<T>>& container, PointerWrapper<T> value)
    {
        container.push_back(value);
        _operands.push_back(container.back());
    }

    template<ArithmeticRef T>
    void AssociativeOperator::add(std::list<PointerWrapper<T>>& container, const T& value)
    {
        container.emplace_back(new T(value));
        _operands.push_back(container.back());
    }

    template<ArithmeticRef T>
    void AssociativeOperator::remove(const T& o)
    {
        _operands.push_back(PointerWrapper<T>(&o));
    }

    template<ArithmeticRef T>
    void AssociativeOperator::add(const T& o)
    {
        _operands.push_back(PointerWrapper<T>(new T(o)));
    }

    template<class UnaryFunction>
    void AssociativeOperator::for_each(UnaryFunction func)
    {
       std::for_each(begin(), end(), func);
    }

    template<class UnaryFunction>
    void AssociativeOperator::for_each(UnaryFunction func) const
    {
       std::for_each(begin(), end(), func);
    }
}

#endif //FUNCTIONS_ASSOCIATIVEOPERATOR_TCC
