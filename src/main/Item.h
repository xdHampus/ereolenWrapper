#ifndef EREOLENWRAPPER_ITEM_H
#define EREOLENWRAPPER_ITEM_H
#include "model/Token.h"
#include "model/Response.h"
#include "model/Record.h"
#include "model/PageResult.h"
#include "model/QuerySettings.h"
#include "src/main/model/Review.h"
#include <string>
#include <optional>
#include <vector>
#include <map>
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
        static const std::string recordsMethod;
        static const std::string searchMethod;
    public:


        static std::vector<ereol::Record> getOthersOfSameTitle(std::string identifier, ereol::Token token);
        static ereol::PageResult getMoreOfSameGenre(std::string identifier, ereol::Token token, ereol::QuerySettings settings = {});
        static ereol::PageResult getMoreOfSameCreator(std::string identifier, ereol::Token token, ereol::QuerySettings settings = {});
        static ereol::PageResult getMoreInSameSeries(std::string identifier, ereol::Token token, ereol::QuerySettings settings = {});
        static std::vector<ereol::Record> getSomethingSimilar(std::string identifier, ereol::Token token, ereol::QuerySettings settings = {});
        //TODO:Not implemented correctly, fix
        static std::vector<ereol::Record> getPersonalRecommendations(std::string identifier, ereol::Token token, ereol::QuerySettings settings = {});
        static std::vector<ereol::Review> getReviews(std::string identifier, ereol::Token token);

        static std::map<std::string, std::string> getCoverUrls(std::vector<std::string> identifiers, ereol::Token token);
        static std::map<std::string, std::string> getLoanStatuses(std::vector<std::string> identifiers, ereol::Token token);
        static ereol::Record getProduct(std::string identifier, ereol::Token token);
        static std::map<std::string, ereol::Record> getRecords(std::vector<std::string> identifiers, ereol::Token token);

        static ereol::PageResult search(std::string queryString, ereol::Token token, ereol::QuerySettings settings = {});

    };
}
#endif //EREOLENWRAPPER_ITEM_H
