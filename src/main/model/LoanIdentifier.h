#ifndef EREOLENWRAPPER_LOANIDENTIFIER_H
#define EREOLENWRAPPER_LOANIDENTIFIER_H
#include <string>
namespace ereol {
    struct LoanIdentifier {
        std::string identifier;
        std::string isbn;
    };
    void from_json(const std::string  &s, ereol::LoanIdentifier& x);
    void to_json(std::string & s, const ereol::LoanIdentifier & x);       
}
#endif //EREOLENWRAPPER_LOANIDENTIFIER_H
