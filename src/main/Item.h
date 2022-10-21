#ifndef EREOLENWRAPPER_ITEM_H
#define EREOLENWRAPPER_ITEM_H
#include "model/Token.h"
#include "model/Response.h"
#include "model/Record.h"
#include "model/PageResult.h"
#include "model/QuerySettings.h"
#include "model/Review.h"
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
        //TODO:Not implemented correctly, fix
        static ereol::Response<std::vector<ereol::Record>> getPersonalRecommendations(std::string identifier, ereol::Token token, ereol::QuerySettings settings = {});
        static ereol::Response<std::vector<ereol::Review>> getReviews(std::string identifier, ereol::Token token);

        static ereol::Response<std::map<std::string, std::string>> getCoverUrls(std::vector<std::string> identifiers, ereol::Token token);
        static ereol::Response<std::map<std::string, std::string>> getLoanStatuses(std::vector<std::string> identifiers, ereol::Token token);
        static ereol::Response<ereol::Record> getProduct(std::string identifier, ereol::Token token);
        static ereol::Response<std::map<std::string, ereol::Record>> getRecords(std::vector<std::string> identifiers, ereol::Token token);

        static ereol::Response<ereol::PageResult> search(std::string queryString, ereol::Token token, ereol::QuerySettings settings = {});

    };
}
#endif //EREOLENWRAPPER_ITEM_H
