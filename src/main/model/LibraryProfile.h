#ifndef EREOLENWRAPPER_LIBRARYPROFILE_H
#define EREOLENWRAPPER_LIBRARYPROFILE_H
#include <string>
namespace ereol {
    struct LibraryProfile {
        int maxConcurrentLoansPerBorrower = 0;
        int maxConcurrentReservationsPerBorrower = 0;
        int maxConcurrentAudioLoansPerBorrower = 0;
        int maxConcurrentAudioReservationsPerBorrower = 0;
    };
    void from_json(const std::string  &s, ereol::LibraryProfile& x);
    void to_json(std::string & s, const ereol::LibraryProfile & x);
}
#endif //EREOLENWRAPPER_LIBRARYPROFILE_H
