//
// Created by mrhowever on 28.01.20.
//

#ifndef FUNCTIONS_LOGARITHM_HH
#define FUNCTIONS_LOGARITHM_HH

#include "ArithmeticObject.hh"
#include "Typedef.hh"

namespace MC::FN
{
    template<typename T> class LogarithmMap;

    class Logarithm : public ArithmeticObject {
        ArithmeticObject* _base;
        ArithmeticObject* _operand;

    public:
        //TODO make private
        Logarithm();
        // TODO copy and swap idiom??
        Logarithm(const Logarithm&);
        Logarithm& operator=(const Logarithm&);

        [[nodiscard]] const ArithmeticObject* getBase() const;

        void simplify() override;
        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] ArithmeticType getType() const override;
        [[nodiscard]] std::string print() const override;

        Logarithm operator+(const Logarithm&) const;
        Logarithm& operator+=(const Logarithm&);

        [[nodiscard]] bool operator==(const Logarithm&) const;
        [[nodiscard]] bool operator!=(const Logarithm&) const;
    };

    typedef std::list<Logarithm> LogList;
    typedef std::unique_ptr<Logarithm> LogPtr;
}

#endif //FUNCTIONS_SUM_HH
