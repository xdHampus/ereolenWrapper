//
// Created by root on 1/30/22.
//

#ifndef EREOLENWRAPPER_LIBRARYPROFILE_H
#define EREOLENWRAPPER_LIBRARYPROFILE_H
#ifdef __cplusplus 
namespace ereol {
#endif
    struct LibraryProfile {
        int maxConcurrentLoansPerBorrower;
        int maxConcurrentReservationsPerBorrower;
        int maxConcurrentAudioLoansPerBorrower;
        int maxConcurrentAudioReservationsPerBorrower;
    };
#ifdef __cplusplus 
}
#endif
#endif //EREOLENWRAPPER_LIBRARYPROFILE_H
