#include "IncludeDivision.hh"
#include "OperatorFactory.hh"
#include "OperatorFactory.tcc"
#include "Variable.hh"
#include "Division.hh"

namespace MC::FN
{
    Division::Division() : _nom(nullptr), _denom(nullptr)
    {
    }

    ArithmeticType Division::getType() const
    {
        return DIV;
    }

    void Division::simplify()
    {
        if(_nom->getType() == MUL and _denom->getType() == MUL) {
            Multiplication& multNom = *dynamic_cast<Multiplication*>(_nom);
            Multiplication& multDenom = *dynamic_cast<Multiplication*>(_denom);

            for(auto nomIt = multNom.begin(); nomIt != multNom.end(); ++nomIt) {
                for(auto denomIt = multDenom.begin(); denomIt != multDenom.end(); ++denomIt) {
                    if(multDenom.erase(*nomIt)) {
                        auto tmp = nomIt;
                        ++nomIt;
                        multNom.erase(tmp);
                    }
                }
            }
        }
        else if(_nom->getType() == MUL or _denom->getType() == MUL) {
            Multiplication& mult = _nom->getType() == MUL ? *dynamic_cast<Multiplication *>(_nom)
                                                          : *dynamic_cast<Multiplication *>(_denom);
            ArithmeticObject*& elem = _nom->getType() == MUL ? _denom : _nom;

            if (mult.erase(elem)) {
                delete (elem);
                elem = new Value(1);
                return;
            }
        }
    }

    Value Division::evaluate(const Value& val) const
    {
        return _nom->evaluate(val) / _denom->evaluate(val);
    }

    std::string Division::print() const
    {
        std::string result;

        if(_nom->getType() == VAL or _nom->getType() == VAR or _nom->getType() == LOG)
            result += _nom->print();
        else
            result += "(" + _nom->print() + ")";

        result += " / ";

        if(_denom->getType() == VAL or _denom->getType() == VAR or _denom->getType() == LOG)
            result += _denom->print();
        else
            result += "(" + _denom->print() + ")";

        return result;
    }

    bool Division::operator==(const Division& o) const
    {
        return _nom == o._nom and _denom == o._denom;
    }

    bool Division::operator!=(const Division& o) const
    {
        return !(*this == o);
    }

    Division Division::reverse() const
    {
        Division result(*this);
        std::swap(result._nom,result._denom);
        return result;
    }

    const ArithmeticObject* Division::getNom() const
    {
        return _nom;
    }

    const ArithmeticObject* Division::getDenom() const
    {
        return _denom;
    }

    //TODO test with memchceck
    Division::~Division()
    {
//        if(_nom) delete(_nom);
//        if(_denom) delete(_denom);
    }

    template<>
    void Division::_div(const Division& o)
    {
        if(!_nom && !_denom) {
            *this = o;
        }
        else {
            if(!_denom) {
                ArithmeticObject *tmpNom = _nom;

                _denom = OperatorFactory::copy(o._nom);
                _nom = new Multiplication(o._denom, tmpNom);

                delete(tmpNom);
            }
            else {
                if (o._nom == _denom) {
                    _denom = OperatorFactory::copy(o._denom);
                } else if (o._denom == _nom) {
                    _nom = OperatorFactory::copy(o._nom);
                } else {
                    ArithmeticObject* tmpNom = _nom, *tmpDenom = _denom;

                    _nom = new Multiplication(tmpNom, o._denom);
                    _denom = new Multiplication(tmpDenom, o._nom);

                    delete(tmpNom);
                    delete(tmpDenom);
                }
            }

            simplify();
        }
    }
}