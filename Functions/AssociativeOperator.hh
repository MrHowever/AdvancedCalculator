#ifndef FUNCTIONS_ASSOCIATIVEOPERATOR_HH
#define FUNCTIONS_ASSOCIATIVEOPERATOR_HH

#include "ArithmeticPointerWrapper.hh"
#include <list>
#include "ArithmeticObject.hh"
#include "EqualityComparable.hh"

namespace MC::FN
{
    class AssociativeOperator : public ArithmeticObject, public EqualityComparable<AssociativeOperator> {
    protected:
        typedef std::list<ArithmeticPointerWrapper>::const_iterator iterator;
        typedef std::list<ArithmeticPointerWrapper >::size_type size_t;

        std::list<ArithmeticPointerWrapper> _operands;

        template<typename T> void add(std::list<PointerWrapper<T> >&, PointerWrapper<T>);
        template<ArithmeticRef T> void add(std::list<PointerWrapper<T> >&, const T&);
        void clear();
        void copy(const AssociativeOperator&);

        AssociativeOperator() = default;

    public:
        [[nodiscard]] bool contains(const ArithmeticPointerWrapper&) const;
        void remove(const ArithmeticPointerWrapper&);
        template<ArithmeticRef T> void remove(const T&);
        void add(const ArithmeticPointerWrapper&);
        template<ArithmeticRef T> void add(const T&);
        template<class UnaryFunction> void for_each(UnaryFunction);
        template<class UnaryFunction> void for_each(UnaryFunction) const;

        [[nodiscard]] static ArithmeticPointerWrapper commonCore(const AssociativeOperator&, const AssociativeOperator&);

        [[nodiscard]] bool operator==(const AssociativeOperator&) const override;
        [[nodiscard]] bool operator!=(const AssociativeOperator&) const override;

        [[nodiscard]] iterator begin() const;
        [[nodiscard]] iterator end() const;
        [[nodiscard]] size_t size() const;
    };
}

#endif //FUNCTIONS_ASSOCIATIVEOPERATOR_HH

#include "AssociativeOperator.tcc"