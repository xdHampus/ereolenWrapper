// prefix for disabling tests DISABLED_

#include <gtest/gtest.h>
#include "BaseTestHelper.h"
#include "../main/Auth.h"
#include "../main/ApiEnv.h"
#include "../main/Item.h"
#include <optional>
#include <vector>
#include <string>
#include <map>

class ItemTestHelper : public BaseTestHelper{
public:
    static ereol::Record recordMock1;
    static ereol::Record recordMock2;
    static ereol::PageResult pageResultGenre1;
    static ereol::PageResult pageResultGenre2;
    static ereol::PageResult pageResultCreator1;
    static ereol::PageResult pageResultSeries1;
    static std::vector<ereol::Record> recordsSimilar1;
    static std::vector<ereol::Record> recordsPersonalRecs1;
    static std::vector<ereol::Review> reviews1;
    static std::map<std::string, std::string> coverUrls1;
    static std::map<std::string, std::string> loanStatuses1;
    static ereol::PageResult pageResultSearch1;
    inline const static std::string item1 = "eyJpIjoiOTc4ODc5NDE5ODAyOCIsInMiOiI4NzA5NzAtYmFzaXM6MzkzOTQ3NTgiLCJjIjoibmV0bHlkYm9nIn0=";
    inline const static std::string item2 = "eyJpIjoiOTc4ODc5MzkzNDM4MiIsInMiOiI4NzA5NzAtYmFzaXM6MzkxMTA5ODkiLCJjIjoibmV0bHlkYm9nIn0=";
    inline const static std::string item3 = "eyJpIjoiOTc4ODcxMTY0MDA4MSIsInMiOiI4NzA5NzAtYmFzaXM6NTI5NzcwNjEiLCJjIjoiZXJlb2xlbiJ9";
    inline const static std::string query1 = "Krimi";
    ItemTestHelper() = default;

};
ItemTestHelper itemTH = ItemTestHelper();
TEST(ItemTest, GetOthersOfSameTitle) {
    itemTH.ensureLoaded();

    EXPECT_TRUE(itemTH.optToken.has_value());
    EXPECT_TRUE(ereol::Auth::isAuthenticated(itemTH.optToken.value()).success());

    ereol::Response<std::vector<ereol::Record>> records = ereol::Item::getOthersOfSameTitle(
            ItemTestHelper::item1,
            itemTH.optToken.value()
            );
    EXPECT_TRUE(records.success());
    EXPECT_TRUE(records.data().has_value());
    if(records.data().has_value()) {
        ereol::Record result = records.data().value()[0];
        ItemTestHelper::tryCompare(ItemTestHelper::recordMock1, result);
    }
}

TEST(ItemTest, GetMoreOfSameGenre) {
    itemTH.ensureLoaded();

    EXPECT_TRUE(itemTH.optToken.has_value());
    EXPECT_TRUE(ereol::Auth::isAuthenticated(itemTH.optToken.value()).success());

    ereol::Response<ereol::PageResult> result1 = ereol::Item::getMoreOfSameGenre(
            ItemTestHelper::item1,
            itemTH.optToken.value(),
            ereol::QuerySettings {
                1,
                2
            }
    );
    EXPECT_TRUE(result1.success());
    EXPECT_TRUE(result1.data().has_value() && result1.data().value().count > 0);
    if(result1.data().has_value() && result1.data().value().count > 0) {
        ItemTestHelper::tryCompare(ItemTestHelper::pageResultGenre1, (ereol::PageResult &) result1.data().value());
    }

    ereol::Response<ereol::PageResult> result2 = ereol::Item::getMoreOfSameGenre(
            "eyJpIjoiOTc4ODc5NDE5ODAyOCIsInMiOiI4NzA5NzAtYmFzaXM6MzkzOTQ3NTgiLCJjIjoibmV0bHlkYm9nIn0=",
            itemTH.optToken.value(),
            ereol::QuerySettings {
                    2,
                    3
            }
    );

    EXPECT_TRUE(result2.success());
    EXPECT_TRUE(result2.data().has_value() && result2.data().value().count > 0);
    if(result2.data().has_value() && result2.data().value().count > 0) {
        ItemTestHelper::tryCompare(ItemTestHelper::pageResultGenre2, (ereol::PageResult &) result2.data().value());
    }
}
TEST(ItemTest, GetMoreOfSameCreator) {
    itemTH.ensureLoaded();

    EXPECT_TRUE(itemTH.optToken.has_value());
    EXPECT_TRUE(ereol::Auth::isAuthenticated(itemTH.optToken.value()).success());

    ereol::Response<ereol::PageResult> result = ereol::Item::getMoreOfSameCreator(
            ItemTestHelper::item2,
            itemTH.optToken.value(),
            ereol::QuerySettings {
                    1,
                    2
            }
    );
    EXPECT_TRUE(result.success());
    EXPECT_TRUE(result.data().has_value() && result.data().value().count > 0);
    if(result.data().has_value() && result.data().value().count > 0) {
        ItemTestHelper::tryCompare(ItemTestHelper::pageResultCreator1, (ereol::PageResult &) result.data().value());
    }
}
TEST(ItemTest, GetMoreInSameSeries) {
    itemTH.ensureLoaded();

    EXPECT_TRUE(itemTH.optToken.has_value());
    EXPECT_TRUE(ereol::Auth::isAuthenticated(itemTH.optToken.value()).success());

    ereol::Response<ereol::PageResult> result = ereol::Item::getMoreInSameSeries(
            ItemTestHelper::item1,
            itemTH.optToken.value(),
            ereol::QuerySettings {
                    1,
                    2
            }
    );
    EXPECT_TRUE(result.success());
    EXPECT_TRUE(result.data().has_value() && result.data().value().count > 0);
    if(result.data().has_value() && result.data().value().count > 0) {
        ItemTestHelper::tryCompare(ItemTestHelper::pageResultSeries1, (ereol::PageResult &) result.data().value());
    }
}
TEST(ItemTest, GetSomethingSimilar) {
    itemTH.ensureLoaded();

    EXPECT_TRUE(itemTH.optToken.has_value());
    EXPECT_TRUE(ereol::Auth::isAuthenticated(itemTH.optToken.value()).success());

    ereol::Response<std::vector<ereol::Record>> result = ereol::Item::getSomethingSimilar(
            ItemTestHelper::item2,
            itemTH.optToken.value(),
            ereol::QuerySettings {
                    1,
                    2
            }
    );
    EXPECT_TRUE(result.success());
    EXPECT_TRUE(result.data().has_value());
    EXPECT_EQ(result.data().value().size(), ItemTestHelper::recordsSimilar1.size());
    if(result.data().has_value() && (result.data().value().size() == ItemTestHelper::recordsSimilar1.size())) {
        for (int i = 0; i < result.data().value().size(); ++i) {
            ItemTestHelper::tryCompare(ItemTestHelper::recordsSimilar1[i], result.data().value()[i]);
        }
    }
}
TEST(ItemTest, DISABLED_GetPersonalRecommendations) {
    itemTH.ensureLoaded();

    EXPECT_TRUE(itemTH.optToken.has_value());
    EXPECT_TRUE(ereol::Auth::isAuthenticated(itemTH.optToken.value()).success());

    ereol::Response<std::vector<ereol::Record>> result = ereol::Item::getPersonalRecommendations(
            ItemTestHelper::item1,
            itemTH.optToken.value(),
            ereol::QuerySettings {
                    0,
                    20
            }
    );

}
TEST(ItemTest, GetReviews) {
    itemTH.ensureLoaded();

    EXPECT_TRUE(itemTH.optToken.has_value());
    EXPECT_TRUE(ereol::Auth::isAuthenticated(itemTH.optToken.value()).success());

    ereol::Response<std::vector<ereol::Review>> result = ereol::Item::getReviews(
            ItemTestHelper::item3,
            itemTH.optToken.value()
    );
    EXPECT_TRUE(result.success());
    EXPECT_TRUE(result.data().has_value());
    EXPECT_EQ(result.data().value().size(), ItemTestHelper::reviews1.size());
    if(result.data().has_value() && (result.data().value().size() == ItemTestHelper::reviews1.size())) {
        for (int i = 0; i < result.data().value().size(); ++i) {
            ItemTestHelper::tryCompare(ItemTestHelper::reviews1[i], result.data().value()[i]);
        }
    }
}
TEST(ItemTest, GetCovers) {
    itemTH.ensureLoaded();

    EXPECT_TRUE(itemTH.optToken.has_value());
    EXPECT_TRUE(ereol::Auth::isAuthenticated(itemTH.optToken.value()).success());

    ereol::Response<std::map<std::string, std::string>> result = ereol::Item::getCoverUrls(
            std::vector<std::string>{
                    ItemTestHelper::item1,
                    ItemTestHelper::item2
                },
            itemTH.optToken.value()
    );
    EXPECT_TRUE(result.success());
    EXPECT_TRUE(result.data().has_value());
    EXPECT_EQ(result.data().value().size(), ItemTestHelper::coverUrls1.size());
    if(result.data().has_value() && (result.data().value().size() == ItemTestHelper::coverUrls1.size())) {
        for (auto const& [key, val] : ItemTestHelper::coverUrls1)
        {
            EXPECT_TRUE(result.data().value().contains(key));
            if(result.data().value().contains(key)){
                EXPECT_STREQ(val.c_str(), result.data().value()[key].c_str());
            }
        }
    }
}
TEST(ItemTest, GetLoanStatuses) {
    itemTH.ensureLoaded();

    EXPECT_TRUE(itemTH.optToken.has_value());
    EXPECT_TRUE(ereol::Auth::isAuthenticated(itemTH.optToken.value()).success());

    ereol::Response<std::map<std::string, std::string>> result = ereol::Item::getLoanStatuses(
            std::vector<std::string>{
                    ItemTestHelper::item1,
                    ItemTestHelper::item2
            },
            itemTH.optToken.value()
    );

    EXPECT_TRUE(result.success());
    EXPECT_TRUE(result.data().has_value());
    EXPECT_EQ(result.data().value().size(), ItemTestHelper::loanStatuses1.size());
    if(result.data().has_value() && (result.data().value().size() == ItemTestHelper::loanStatuses1.size())) {
        for (auto const& [key, val] : ItemTestHelper::loanStatuses1)
        {
            EXPECT_TRUE(result.data().value().contains(key));
            if(result.data().value().contains(key)){
                EXPECT_STREQ(val.c_str(), result.data().value()[key].c_str());
            }
        }
    }
}
TEST(ItemTest, GetProduct) {
    itemTH.ensureLoaded();
    EXPECT_TRUE(itemTH.optToken.has_value());
    EXPECT_TRUE(ereol::Auth::isAuthenticated(itemTH.optToken.value()).success());

    ereol::Response<ereol::Record> result = ereol::Item::getProduct(
            ItemTestHelper::item1,
            itemTH.optToken.value()
    );
    ItemTestHelper::tryCompare(ItemTestHelper::recordMock2, (ereol::Record &) result.data().value());
}
TEST(ItemTest, Search) {
    itemTH.ensureLoaded();
    EXPECT_TRUE(itemTH.optToken.has_value());
    EXPECT_TRUE(ereol::Auth::isAuthenticated(itemTH.optToken.value()).success());

    ereol::Response<ereol::PageResult> result = ereol::Item::search(
            ItemTestHelper::query1,
            itemTH.optToken.value(),
            ereol::QuerySettings {
                    0,
                    10,
                    std::map<std::string, std::string> {
                            std::pair<std::string, std::string>("facet.category", "voksenmaterialer"),
                            std::pair<std::string, std::string>("redia.type", "E-bog")
                    }
            }
    );
    EXPECT_TRUE(result.success());
    EXPECT_TRUE(result.data().has_value() && result.data().value().count > 0);
    if(result.data().has_value() && result.data().value().count > 0) {
        ItemTestHelper::tryCompare(ItemTestHelper::pageResultSearch1, (ereol::PageResult &) result.data().value());
    }
}

ereol::Record ItemTestHelper::recordMock1  = {
        ereol::LoanIdentifier{
                "eyJpIjoiOTc4ODc5NDE5ODAyOCIsInMiOiI4NzA5NzAtYmFzaXM6MzkzOTQ3NTgiLCJjIjoibmV0bHlkYm9nIn0=",
                "9788794198028"
        },
        "True crime. 1",
        "Lyngby-Taarbæk Bibliotekerne",
        "Downloades i MP3-format",
        "Dansk",
        "audio",
        std::nullopt,
        std::nullopt,
        std::nullopt,
        std::nullopt,
        "audiobook",
        std::nullopt,
        std::nullopt,
        std::nullopt,
        std::nullopt,
        "Kommer bl.a. omkring hvad der sker i lokalsamfundet eller i en familie efter et mord og hvad der foregår i hovedet på en morder. Kommer også omkring økonomisk svindel, Silicon Valley, Me Too og uopklarede historiske mordsager",
        "2021",
        "",
        "81.09 > True",
        "[1] \"True crime\"",
        "ERA202129",
        "",
        std::nullopt,
        std::vector<std::string>{},
        std::vector<std::string>{
                "Bogbrevkassen",
                "True crime"
        },
        std::vector<std::string>{
                "litteratur",
                "true crime",
                "litteraturanmeldelser"
        },
        std::vector<std::string>{
                "Lydbog"
        }
};


ereol::Record ItemTestHelper::recordMock2  = {
        ereol::LoanIdentifier{
                "eyJpIjoiOTc4ODc5NDE5ODAyOCIsImMiOiJuZXRseWRib2cifQ==",
                "9788794198028"
        },
        "True Crime - del 1",
        "Lyngby-Taarbæk Bibliotekerne",
        "I denne uge har lytteren Martin skrevet til os i Bogbrevkassen for at få inspiration til romaner, der handler om éneren og mønsterbryderen. Lise, Silja og Patrick har derfor gravet i bogsamlingen og fundet en rund håndfuld romankarakterer, der er fulde af gåpåmod og visioner.\nI bogsnakken kommer vi forbi et af de helt store værker fra den danske litteraturkanon, henover den danske verdensstjerne der blev glemt og videre ud i den store verden, hvor vi møder unge mennesker der bryder med ophav og samfundsnormer. Vi snakker om romankarakterer der viser, hvad det vil sige at være en mønsterbryder. Og om medrivende historier, der har sat sig i kødet på os - bittersøde bøger, der skærer i hjertet, samtidig med at de giver mod og livslyst i en tid hvor verden synes et vakuum og handlerummet begrænset.\nSe anbefalingerne på www.lyngbybib.dk/nyheder/podcast/bogbrevkassen-16\nMedvirkende: Lise Roest-Madsen, Silja Attrup og Patrick Søgaard. Redigering: Ole Dissing. Musik: Nikolaj Lind Christensen\nOg husk, at bogbrevkassens bagmænd meget gerne modtager breve fra folk, der mangler gode boganbefalinger. Skriv til Lise, Lea, Aske og Silja på info@ltk.dk.",
        "{{language}}",
        "audio",
        1625043053,
        1625043053,
        1623628800,
        0,
        std::nullopt,
        "https://images.pubhub.dk/01/bdc2ef78-6846-414a-8527-b591b48a6c96.png",
        "bdc2ef78-6846-414a-8527-b591b48a6c96",
        "",
        "https://images.pubhub.dk/27/bdc2ef78-6846-414a-8527-b591b48a6c96.png",
        std::nullopt,
        std::nullopt,
        std::nullopt,
        std::nullopt,
        std::nullopt,
        std::nullopt,
        std::nullopt,
        std::vector<ereol::Contributor>{
                {
                    "aut",
                    "Lyngby-Taarbæk Bibliotekerne",
                    "Lyngby-Taarbæk",
                    "Bibliotekerne"
                },
                {
                    "nrt",
                    "Lea Fløe Christensen",
                    "Lea",
                    "Fløe Christensen"
                },
                {
                    "nrt",
                    "Ole Dissing",
                    "Ole",
                    "Dissing"
                }
            },
        std::nullopt,
        std::nullopt,
        std::nullopt,
        std::nullopt
};

ereol::PageResult ItemTestHelper::pageResultGenre1  = {
        {
                {ereol::Record {
                        ereol::LoanIdentifier{
                                "eyJpIjoiOTc4ODc5ODg2MjI2MCIsInMiOiI4NzA5NzAtYmFzaXM6NDg0NDM3MjkiLCJjIjoibmV0bHlkYm9nIn0=",
                                "9788798862260"
                        },
                        "Bøger man bliver klogere af",
                        "Lyngby-Taarbæk Bibliotekerne",
                        "Downloades i MP3-format",
                        "Dansk",
                        "audio",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "podcast",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "Podcast med anbefalinger på bøger, man bliver klogere af og bringer én ind i litteraturen og fordybelsen",
                        "2020",
                        "",
                        "81.04 > Bøger",
                        "[6] \"Bogbrevkassen\"",
                        "ERA202035",
                        "",
                        std::nullopt,
                        std::vector<std::string>{},
                        std::vector<std::string>{
                                "Bogbrevkassen"
                        },
                        std::vector<std::string>{
                                "litteratur",
                                "litteraturanmeldelser"
                        },
                        std::vector<std::string>{
                                "Podcast"
                        }
                }},
                {ereol::Record{
                        ereol::LoanIdentifier{
                                "eyJpIjoiOTc4ODc5MzkzNDM4MiIsInMiOiI4NzA5NzAtYmFzaXM6MzkxMTA5ODkiLCJjIjoibmV0bHlkYm9nIn0=",
                                "9788793934382"
                        },
                        "Med Bjælken i mit øje, sexus, HHV og Philip K. Dick",
                        "Københavns Biblioteker, Lyd",
                        "Downloades i MP3-format",
                        "Dansk",
                        "audio",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "audiobook",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "Interview med Carsten Jensen om \"Bjælken i mit øje\", litteraturformidler Rasmus Riiskjær fra Husum Bibliotek anbefaler \"HHV Frshwn\" af Hanne Høigaard Viemose, forfatteren Martin Kongstad fortæller om Henry Millers \"Sexus\" og podcastværten Claus Vittus egen anbefaling er \"Filmatiserede noveller\" af Philip K. Dick",
                        "2021",
                        "",
                        "81.04 > Vittus",
                        "[2] \"Bogdate\"",
                        "ERA202135",
                        "",
                        std::nullopt,
                        std::vector<std::string>{
                            "Claus Vittus",
                            "Vittus, Claus"
                            },
                        std::vector<std::string>{
                                "Bogdate",
                        },
                        std::vector<std::string>{
                                "litteratur",
                                "litteraturanmeldelser"
                        },
                        std::vector<std::string>{
                                "Lydbog"
                        }
                }}
        },
        564,
        true,
        {},

};

ereol::PageResult ItemTestHelper::pageResultGenre2  = {
        {
                {ereol::Record{
                        ereol::LoanIdentifier{
                                "eyJpIjoiOTc4ODc5MzkzNDM4MiIsInMiOiI4NzA5NzAtYmFzaXM6MzkxMTA5ODkiLCJjIjoibmV0bHlkYm9nIn0=",
                                "9788793934382"
                        },
                        "Med Bjælken i mit øje, sexus, HHV og Philip K. Dick",
                        "Københavns Biblioteker, Lyd",
                        "Downloades i MP3-format",
                        "Dansk",
                        "audio",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "audiobook",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "Interview med Carsten Jensen om \"Bjælken i mit øje\", litteraturformidler Rasmus Riiskjær fra Husum Bibliotek anbefaler \"HHV Frshwn\" af Hanne Høigaard Viemose, forfatteren Martin Kongstad fortæller om Henry Millers \"Sexus\" og podcastværten Claus Vittus egen anbefaling er \"Filmatiserede noveller\" af Philip K. Dick",
                        "2021",
                        "",
                        "81.04 > Vittus",
                        "[2] \"Bogdate\"",
                        "ERA202135",
                        "",
                        std::nullopt,
                        std::vector<std::string>{
                                "Claus Vittus",
                                "Vittus, Claus"
                        },
                        std::vector<std::string>{
                                "Bogdate",
                        },
                        std::vector<std::string>{
                                "litteratur",
                                "litteraturanmeldelser"
                        },
                        std::vector<std::string>{
                                "Lydbog"
                        }
                }},
                {ereol::Record {
                        ereol::LoanIdentifier{
                                "eyJpIjoiOTc4ODc5NzI1MDAzNyIsInMiOiI4NzA5NzAtYmFzaXM6Mzg4MjE0MzEiLCJjIjoibmV0bHlkYm9nIn0=",
                                "9788797250037"
                        },
                        "Ferielæsning",
                        "Lyngby-Taarbæk Bibliotekerne",
                        "Downloades i MP3-format",
                        "Dansk",
                        "audio",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "audiobook",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "Anbefalinger til ferielæsning, både for folk, der bare vil hyggelæse med et smil på læben og folk, der gerne vil høre store, dragende fortællinger",
                        "2020",
                        "",
                        "81.04 > Ferielæsning",
                        "",
                        "ERA202118",
                        "",
                        std::nullopt,
                        std::vector<std::string>{},
                        std::vector<std::string>{
                                "Bogbrevkassen"
                        },
                        std::vector<std::string>{
                                "litteratur",
                                "litteraturanmeldelser"
                        },
                        std::vector<std::string>{
                                "Lydbog"
                        }
                }},
                {ereol::Record{
                        ereol::LoanIdentifier{
                                "eyJpIjoiOTc4ODc5MzkzNDY3MiIsInMiOiI4NzA5NzAtYmFzaXM6NjIxODc4ODMiLCJjIjoibmV0bHlkYm9nIn0=",
                                "9788793934672"
                        },
                        "Gasolin, Halfdan & Christianshavn, Christianshavn er et kulturelt smørhul med alternativ livsform",
                        "Københavns Biblioteker, Lyd",
                        "Downloades i MP3-format",
                        "Dansk",
                        "audio",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "audiobook",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "\"Gasolin' - gudernes vilje\" handler både om Gasolin' og om det Christianshavn som de kom fra. Interview med en af bogens forfattere, Jacob Wendt Jensen. Bogdate har også Halfdan Rasmussen og 1800-talsforfatteren Vilhelm Bergsøes beskrivelser af Christianshavn under koleraepidemien i sommeren 1853 på programmet",
                        "2022",
                        "",
                        "81.04 > Vittus",
                        "[10] \"Bogdate\"",
                        "ERA202209",
                        "",
                        std::nullopt,
                        std::vector<std::string>{
                                "Claus Vittus",
                                "Vittus, Claus"
                        },
                        std::vector<std::string>{
                                "Bogdate",
                        },
                        std::vector<std::string>{
                                "litteratur",
                                "litteraturanmeldelser"
                        },
                        std::vector<std::string>{
                                "Lydbog"
                        }
                }}
        },
        564,
        true,
        {},

};

ereol::PageResult ItemTestHelper::pageResultCreator1  = {
        {
                {ereol::Record {
                        ereol::LoanIdentifier{
                                "eyJpIjoiOTc4ODc5MzkzNDQ4MSIsInMiOiI4NzA5NzAtYmFzaXM6NjE0Njg5MTkiLCJjIjoibmV0bHlkYm9nIn0=",
                                "9788793934481"
                        },
                        "Rock, vilde kvinder og mørke undertoner",
                        "Københavns Biblioteker, Lyd",
                        "Downloades i MP3-format",
                        "Dansk",
                        "audio",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "audiobook",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "Præsentation af fire bøger der hver på sin måde handler om rock- og popmusik: \"Vilde kvinder, mørke toner\", \"Rock & stjernestøv\", \"Clapton\" og \"Nowhere man\"",
                        "2021",
                        "",
                        "81.04 > Vittus",
                        "[6] \"Bogdate\"",
                        "ERA202141",
                        "",
                        std::nullopt,
                        std::vector<std::string>{
                                "Claus Vittus",
                                "Vittus, Claus"
                                },
                        std::vector<std::string>{
                                "Bogdate"
                        },
                        std::vector<std::string>{
                                "litteratur",
                                "rock",
                                "pop",
                                "litteraturanmeldelser"
                        },
                        std::vector<std::string>{
                                "Lydbog"
                        }
                }},
                {ereol::Record{
                        ereol::LoanIdentifier{
                                "eyJpIjoiOTc4ODc5MzkzNDY3MiIsInMiOiI4NzA5NzAtYmFzaXM6NjIxODc4ODMiLCJjIjoibmV0bHlkYm9nIn0=",
                                "9788793934672"
                        },
                        "Gasolin, Halfdan & Christianshavn, Christianshavn er et kulturelt smørhul med alternativ livsform",
                        "Københavns Biblioteker, Lyd",
                        "Downloades i MP3-format",
                        "Dansk",
                        "audio",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "audiobook",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "\"Gasolin' - gudernes vilje\" handler både om Gasolin' og om det Christianshavn som de kom fra. Interview med en af bogens forfattere, Jacob Wendt Jensen. Bogdate har også Halfdan Rasmussen og 1800-talsforfatteren Vilhelm Bergsøes beskrivelser af Christianshavn under koleraepidemien i sommeren 1853 på programmet",
                        "2022",
                        "",
                        "81.04 > Vittus",
                        "[10] \"Bogdate\"",
                        "ERA202209",
                        "",
                        std::nullopt,
                        std::vector<std::string>{
                                "Claus Vittus",
                                "Vittus, Claus"
                        },
                        std::vector<std::string>{
                                "Bogdate",
                        },
                        std::vector<std::string>{
                                "litteratur",
                                "litteraturanmeldelser"
                        },
                        std::vector<std::string>{
                                "Lydbog"
                        }
                }}
        },
        21,
        true,
        {},

};

ereol::PageResult ItemTestHelper::pageResultSeries1  = {
        {
                {ereol::Record {
                        ereol::LoanIdentifier{
                                "eyJpIjoiOTc4ODc5NDE5ODAzNSIsInMiOiI4NzA5NzAtYmFzaXM6MzkzOTQ3MzEiLCJjIjoibmV0bHlkYm9nIn0=",
                                "9788794198035"
                        },
                        "True crime. 2",
                        "Lyngby-Taarbæk Bibliotekerne",
                        "Downloades i MP3-format",
                        "Dansk",
                        "audio",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "audiobook",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "Om at grave i kilder, hvor en kriminel underverden og parallelsamfund dukker frem, om et tragisk dødsfald i de øverste kendislag, der bliver allemandsret og opføres som operette. Og om en sag, der trækker tråde helt indenfor Lyngby bibliotekets egne mure",
                        "2021",
                        "",
                        "81.09 > True",
                        "[2] \"True crime\"",
                        "ERA202129",
                        "",
                        std::nullopt,
                        std::vector<std::string>{},
                        std::vector<std::string>{
                                "Bogbrevkassen",
                                "True crime"
                        },
                        std::vector<std::string>{
                                "litteratur",
                                "true crime",
                                "litteraturanmeldelser"
                        },
                        std::vector<std::string>{
                                "Lydbog"
                        }
                }},
                {ereol::Record{
                        ereol::LoanIdentifier{
                                "eyJpIjoiOTc4ODc5ODg2MjIyMiIsInMiOiI4NzA5NzAtYmFzaXM6NDg0MjUzNDgiLCJjIjoibmV0bHlkYm9nIn0=",
                                "9788798862222"
                        },
                        "Havbøger til kaptajnen, der keder sig med Moby Dick",
                        "Lyngby-Taarbæk Bibliotekerne",
                        "Downloades i MP3-format",
                        "Dansk",
                        "audio",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "podcast",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "Podcast med anbefalinger på konkrete og eksistentielle havbøger til en kaptajn, der keder sig med Moby Dick",
                        "2020",
                        "",
                        "81.04 > Havbøger",
                        "[2] \"Bogbrevkassen\"",
                        "ERA202035",
                        "",
                        std::nullopt,
                        std::vector<std::string>{},
                        std::vector<std::string>{
                                "Bogbrevkassen",
                        },
                        std::vector<std::string>{
                                "litteratur",
                                "litteraturanmeldelser"
                        },
                        std::vector<std::string>{
                                "Podcast"
                        }
                }}
        },
        19,
        true,
        {},

};

std::vector<ereol::Record> ItemTestHelper::recordsSimilar1 = {
        {
            ereol::LoanIdentifier{
                    "eyJpIjoiOTc4ODcyNjY0Nzg3NyIsInMiOiI4NzA5NzAtYmFzaXM6MzkwNDcyODQiLCJjIjoibmV0bHlkYm9nIn0=",
                    "9788726647877"
            },
                    "Sov godt, fald i søvn på på 15 minutter med guidet meditation (15 minutter)",
                    "Lindhardt og Ringhof",
                    "Downloades i MP3-format",
                    "Dansk",
                    "audio",
                    std::nullopt,
                    std::nullopt,
                    std::nullopt,
                    std::nullopt,
                    "audiobook",
                    std::nullopt,
                    std::nullopt,
                    std::nullopt,
                    std::nullopt,
                    "Meditation til børn for at falde i søvn",
                    "2020",
                    "",
                    "61.36 > Myrna",
                    "",
                    "ERA202130",
                    "",
                    std::nullopt,
                    std::vector<std::string>{
                            "Metta Myrna (f. 1972)",
                            "Myrna, Metta"
                            },
                    std::vector<std::string>{},
                    std::vector<std::string>{
                            "mindfulness",
                            "meditation",
                            "søvn"
                    },
                    std::vector<std::string>{
                            "Lydbog"
                    }
        },
        {
                ereol::LoanIdentifier{
                        "eyJpIjoiOTc4ODcyNjY0Nzk4MyIsInMiOiI4NzA5NzAtYmFzaXM6MzkwNDcyMzMiLCJjIjoibmV0bHlkYm9nIn0=",
                        "9788726647983"
                },
                "God nat, afslut dagen med 10 minutters guidet meditation",
                "Lindhardt og Ringhof",
                "Titlen hentet fra indgangssiden",
                "Dansk",
                "audio",
                std::nullopt,
                std::nullopt,
                std::nullopt,
                std::nullopt,
                "audiobook",
                std::nullopt,
                std::nullopt,
                std::nullopt,
                std::nullopt,
                "",
                "2020",
                "",
                "61.36 > Myrna",
                "",
                "ERA202137",
                "",
                std::nullopt,
                std::vector<std::string>{
                        "Metta Myrna (f. 1972)",
                        "Myrna, Metta"
                },
                std::vector<std::string>{},
                std::vector<std::string>{
                        "mindfulness",
                        "meditation",
                        "søvn"
                },
                std::vector<std::string>{
                        "Lydbog"
                }
        }
};
std::vector<ereol::Review> ItemTestHelper::reviews1 = {
        {
            "Lektørudtalelse",
            "En meget spændende og eventyrlig beretning fra en helt speciel jordomrejse, der ville have fået mindre erfarne rejsende til at give op allerede i Stockholm",
            "https://ereolen.dk/ting/object/870976-anmeld:129415452/fulltext"
        },
        {
            "Litteratursiden",
            "De to danske globetrottere, Hjalte og Nina, er på jordomrejse i en elbil. De er hele tiden på udkig efter næste opladningsmulighed, og det giver en noget anderledes rejseskildring. Det er egentlig en ...",
            "http://litteratursiden.dk/anmeldelser/helt-elektrisk-jorden-rundt-af-nina-rasmussen-og-hjalte-tin"
        }
};
std::map<std::string, std::string> ItemTestHelper::coverUrls1 = {
        std::pair<std::string, std::string>(
                "eyJpIjoiOTc4ODc5NDE5ODAyOCIsInMiOiI4NzA5NzAtYmFzaXM6MzkzOTQ3NTgiLCJjIjoibmV0bHlkYm9nIn0=",
                "https://images.pubhub.dk/01/bdc2ef78-6846-414a-8527-b591b48a6c96.png"
        ),
        std::pair<std::string, std::string>(
                "eyJpIjoiOTc4ODc5MzkzNDM4MiIsInMiOiI4NzA5NzAtYmFzaXM6MzkxMTA5ODkiLCJjIjoibmV0bHlkYm9nIn0=",
                "https://images.pubhub.dk/01/9a592726-dced-41a5-8391-dceeead26dca.jpg"
        ),

};
std::map<std::string, std::string> ItemTestHelper::loanStatuses1 = {
        std::pair<std::string, std::string>(
                "eyJpIjoiOTc4ODc5NDE5ODAyOCIsInMiOiI4NzA5NzAtYmFzaXM6MzkzOTQ3NTgiLCJjIjoibmV0bHlkYm9nIn0=",
                "loanable"
        ),
        std::pair<std::string, std::string>(
                "eyJpIjoiOTc4ODc5MzkzNDM4MiIsInMiOiI4NzA5NzAtYmFzaXM6MzkxMTA5ODkiLCJjIjoibmV0bHlkYm9nIn0=",
                "loanable"
        ),

};

ereol::PageResult ItemTestHelper::pageResultSearch1  = {
        {
                {ereol::Record {
                        ereol::LoanIdentifier{
                                "eyJpIjoiOTc4ODc3MDM2MzMyNyIsInMiOiI4NzA5NzAtYmFzaXM6NDYzMzMxMjgiLCJjIjoiZXJlb2xlbiJ9",
                                "9788770363327"
                        },
                        "Der hvor solen aldrig skinner, skæbnehistorier fra danske fængsler, true crime",
                        "Momenta",
                        "Downloades i EPUB-format",
                        "Dansk",
                        "text",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "ebook",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "Tidligere straffede personer fortæller om hvordan de oplevede at sidde indespærret, og hvorfor de overhovedet havnede bag tremmer",
                        "2019",
                        "1. udgave",
                        "34.35 > Grønlund",
                        "",
                        "",
                        "",
                        std::nullopt,
                        std::vector<std::string>{
                            "Peter Grønlund (f. 1970-04-11)",
                            "Grønlund, Peter"
                        },
                        std::vector<std::string>{},
                        std::vector<std::string>{
                            "forbrydelser",
                            "kriminelle",
                            "kriminalitet",
                            "fængsler",
                            "fanger",
                            "fængselsvæsen",
                            "fængselsophold"
                        },
                        std::vector<std::string>{
                            "E-bog"
                        }
                }},
                {ereol::Record{
                        ereol::LoanIdentifier{
                                "eyJpIjoiOTc4ODc3MTc0NTE5MSIsInMiOiI4NzA5NzAtYmFzaXM6NTIwNzkyMTciLCJjIjoiZXJlb2xlbiJ9",
                                "9788771745191"
                        },
                        "Stormagasinets hemmelighed, krimi noir",
                        "Rosenkilde & Bahnhof",
                        "Downloades i EPUB-format",
                        "Dansk",
                        "text",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "ebook",
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        std::nullopt,
                        "Krimi. Stormagasinet French er berømt for sit udbud af sjældne varer, men ingen havde dog regnet med noget så sjældent som det syn, der møder folk, da den nye vinduesudstilling bliver afsløret",
                        "2015",
                        "1. RB-udgave (1. ebogsudgave)",
                        "Queen",
                        "",
                        "ERA201603",
                        "",
                        std::nullopt,
                        std::vector<std::string>{
                            "Ellery Queen",
                            "Queen, Ellery"
                        },
                        std::vector<std::string>{},
                        std::vector<std::string>{},
                        std::vector<std::string>{
                                "E-bog"
                        }
                }}
        },
        4395,
        true,
        std::vector<ereol::Facet> {
            {
                "redia.type",
                std::vector<ereol::Term> {
                    {
                        "E-bog",
                        "ebog",
                        4395
                    },
                    {
                            "E-bog",
                            "ebog",
                            4395
                    }
                },
                "buttons",
                "key__filter_facet__type"
            },
            {
                "facet.subject",
                std::vector<ereol::Term> {
                    {
                        "krimi",
                        "krimi",
                        2386
                    },
                    {
                        "electronic books",
                        "electronic books",
                        1750
                    },
                    {
                        "fiction",
                        "fiction",
                        1634
                    }
                },
                "list",
                "key__filter_facet__subject"
            }
        }

};

/*

        std::string name;
        std::vector<ereol::Term> terms;
        std::string type;
        std::string translationKey;
 */