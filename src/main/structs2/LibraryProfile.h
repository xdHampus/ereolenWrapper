#pragma once

namespace ereol {
    struct LibraryProfile {
        uint maxConcurrentLoansPerBorrower;
        uint maxConcurrentReservationsPerBorrower;
        uint maxConcurrentAudioLoansPerBorrower;
        uint maxConcurrentAudioReservationsPerBorrower;
    };
}
