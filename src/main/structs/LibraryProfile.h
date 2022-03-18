//
// Created by root on 1/30/22.
//

#ifndef EREOLENWRAPPER_LIBRARYPROFILE_H
#define EREOLENWRAPPER_LIBRARYPROFILE_H

namespace ereol {
    struct LibraryProfile {
        int maxConcurrentLoansPerBorrower;
        int maxConcurrentReservationsPerBorrower;
        int maxConcurrentAudioLoansPerBorrower;
        int maxConcurrentAudioReservationsPerBorrower;
    };
}

#endif //EREOLENWRAPPER_LIBRARYPROFILE_H