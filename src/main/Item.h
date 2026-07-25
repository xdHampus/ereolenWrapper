#ifndef EREOLENWRAPPER_ITEM_H
#define EREOLENWRAPPER_ITEM_H
#include "model/Token.h"
#include "model/Response.h"
#include "model/Record.h"
#include "model/PageResult.h"
#include "model/QuerySettings.h"
#include "model/Review.h"
#include "model/CreatorInfo.h"
#include "model/Suggestion.h"
#include "model/LoanActive.h"
#include <string>
#include <optional>
#include <vector>
#include <map>


namespace ereol {


    class Item {
    public:


        static ereol::Response<std::vector<ereol::Record>> getOthersOfSameTitle(std::string identifier, ereol::Token token);
        static ereol::Response<ereol::PageResult> getMoreOfSameGenre(std::string identifier, ereol::Token token, ereol::QuerySettings settings = {});
        static ereol::Response<ereol::PageResult> getMoreOfSameCreator(std::string identifier, ereol::Token token, ereol::QuerySettings settings = {});
        static ereol::Response<ereol::PageResult> getMoreInSameSeries(std::string identifier, ereol::Token token, ereol::QuerySettings settings = {});
        static ereol::Response<std::vector<ereol::Record>> getSomethingSimilar(std::string identifier, ereol::Token token, ereol::QuerySettings settings = {});

        // Takes no method args -- 4 params, prefix only.
        static ereol::Response<std::vector<ereol::Record>> getPersonalRecommendations(ereol::Token token);
        static ereol::Response<std::vector<ereol::Review>> getReviews(std::string identifier, ereol::Token token);
        static ereol::Response<std::vector<ereol::CreatorInfo>> getAboutCreators(std::string identifier, ereol::Token token);
        // Search typeahead. Unauthenticated; 5 params.
        static ereol::Response<std::vector<ereol::Suggestion>> getSuggestions(std::string prefix, ereol::Token token);

        static ereol::Response<std::map<std::string, std::string>> getCoverUrls(std::vector<std::string> identifiers, ereol::Token token);
        static ereol::Response<std::map<std::string, std::string>> getLoanStatuses(std::vector<std::string> identifiers, ereol::Token token);
        static ereol::Response<ereol::Record> getProduct(std::string identifier, ereol::Token token);
        static ereol::Response<std::map<std::string, ereol::Record>> getRecords(std::vector<std::string> identifiers, ereol::Token token);

        static ereol::Response<ereol::PageResult> search(std::string queryString, ereol::Token token, ereol::QuerySettings settings = {});

        // Borrows a title. Consumes a slot against the library's
        // maxConcurrentLoansPerBorrower quota, and there is no return-loan RPC:
        // loans only expire. Check getLoanStatuses first.
        static ereol::Response<ereol::LoanActive> createLoan(std::string identifier, ereol::Token token);

        // Writes the loan's fulfilment ticket (an .acsm for ebooks) to
        // <path>/<filename><ext> and returns that path. Not fulfilment itself.
        static ereol::Response<std::string> download(const std::string &path, const std::string &filename, const ereol::LoanActive &x);
    };
}
#endif //EREOLENWRAPPER_ITEM_H
