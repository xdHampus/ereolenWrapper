//
// Created by root on 1/30/22.
//

#ifndef EREOLENWRAPPER_ITEM_H
#define EREOLENWRAPPER_ITEM_H
#include "model/Token.h"
#ifdef __cplusplus 
#include <string>
#include <optional>
#include <vector>
namespace ereol {
    class Item {
    private:
        static const std::string otherTypesOfSameTitleMethod;
        static const std::string moreOfSameGenreMethod;
        static const std::string moreOfSameCreatorMethod;
        static const std::string moreInSameSeriesMethod;
        static const std::string somethingSimilarMethod;
        static const std::string aboutCreatorsMethod;
        static const std::string reviewsMethod;
        static const std::string coversMethod;
        static const std::string personalRecommendationsMethod;
        static const std::string loanStatusesMethod;
        static const std::string productMethod;
    public:
        static std::optional<std::vector<ereol::LoanHistorical>> getLoanHistory(ereol::Token token);

        static std::optional<std::string> getCover(std::string itemId, ereol::Token token);
        static std::optional<std::vector<std::string>> getCovers(std::string itemIds, ereol::Token token);

    };
#else
LibraryItem*  ereol_Item_getLibraryItem(Library* library); 
LoanActive*  ereol_Item_getLoans(Token* token); 
ChecklistItem* ereol_Item_getChecklist(Token* token); 
Reservation*  ereol_Item_getReservations(Token* token); 
LoanHistorical*  ereol_Item_getLoanHistory(Token* token); 
#endif
#ifdef __cplusplus 
}
#endif


#endif //EREOLENWRAPPER_ITEM_H
