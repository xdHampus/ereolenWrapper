from flask import request
import json
from common import wrap_response, invalid_params, invalid_params_count, no_results

item_1 = "eyJpIjoiOTc4ODc5NDE5ODAyOCIsInMiOiI4NzA5NzAtYmFzaXM6MzkzOTQ3NTgiLCJjIjoibmV0bHlkYm9nIn0="
item_2 = "eyJpIjoiOTc4ODc5MzkzNDM4MiIsInMiOiI4NzA5NzAtYmFzaXM6MzkxMTA5ODkiLCJjIjoibmV0bHlkYm9nIn0="
item_3 = "eyJpIjoiOTc4ODcxMTY0MDA4MSIsInMiOiI4NzA5NzAtYmFzaXM6NTI5NzcwNjEiLCJjIjoiZXJlb2xlbiJ9"
query_1 = "Krimi"
facet_sel_1 = {
    "facet.category": "voksenmaterialer",
    "redia.type": "E-bog"
}

# Example
# {
#     "jsonrpc": "2.0",
#     "method": "getOtherTypesOfSameTitle",
#     "params": [
#         "{{magicId}}",
#         "{{appVersion}}",
#         "{{language}}",
#         "{{library}}",
#         "eyJpIjoiOTc4ODc5NDE5ODAyOCIsInMiOiI4NzA5NzAtYmFzaXM6MzkzOTQ3NTgiLCJjIjoibmV0bHlkYm9nIn0="
#     ],
#     "id": "078096d9-c9d1-1524-ee29-04e47b9f2b5b"
# }
def m_same_title(data, app):
    if len(data["params"]) < 4:
        return wrap_response(invalid_params_count(data), app)
    item = data["params"][4]
    if item == item_1:
        return wrap_response(resp_same_title_1(data), app)
    return wrap_response(invalid_params(data), app)


# Example
# {
#     "jsonrpc": "2.0",
#     "method": "getMoreOfSameGenre",
#     "params": [
#         "{{magicId}}",
#         "{{appVersion}}",
#         "{{language}}",
#         "{{library}}",
#         "eyJpIjoiOTc4ODc5NDE5ODAyOCIsInMiOiI4NzA5NzAtYmFzaXM6MzkzOTQ3NTgiLCJjIjoibmV0bHlkYm9nIn0=",
#         1,
#         2
#     ],
#     "id": "e394f31b-d3f7-f6b1-38a6-5f01d9e8fa96"
# }
def m_same_genre(data, app):
    if len(data["params"])< 6:
        return wrap_response(invalid_params_count(data), app)
    item, start, end = data["params"][4], data["params"][5], data["params"][6]
    if item == item_1:
        if start == 1 and end == 2:
            return wrap_response(resp_same_genre_1(data), app)
        elif start == 2 and end == 3:
            return wrap_response(resp_same_genre_2(data), app)

    return wrap_response(invalid_params(data), app)


def m_same_creator(data, app):
    if len(data["params"]) < 6:
        return wrap_response(invalid_params_count(data), app)
    item, start, end = data["params"][4], data["params"][5], data["params"][6]
    if item == item_2:
        if start == 1 and end == 2:
            return wrap_response(resp_same_creator_1(data), app)
    return wrap_response(invalid_params(data), app)


def m_same_series(data, app):
    if len(data["params"]) < 6:
        return wrap_response(invalid_params_count(data), app)
    item, start, end = data["params"][4], data["params"][5], data["params"][6]
    if item == item_1:
        if start == 1 and end == 2:
            return wrap_response(resp_same_series_1(data), app)
    return wrap_response(invalid_params(data), app)



def m_something_similar(data, app):
    if len(data["params"]) < 6:
        return wrap_response(invalid_params_count(data), app)
    item, start, end = data["params"][4], data["params"][5], data["params"][6]
    if item == item_2:
        if start == 1 and end == 2:
            return wrap_response(resp_similar_1(data), app)

    return wrap_response(invalid_params(data), app)


def m_about_creator(data, app):
    if len(data["params"]) < 4:
        return wrap_response(invalid_params_count(data), app)
    item = data["params"][4]
    if item == item_1:
        return wrap_response(no_results(data), app)
    elif item == item_2:
        return wrap_response(resp_about_creator_1(data), app)

    return wrap_response(invalid_params(data), app)

def m_reviews(data, app):
    if len(data["params"]) < 4:
        return wrap_response(invalid_params_count(data), app)
    item = data["params"][4]
    if item == item_3:
        return wrap_response(resp_reviews_1(data), app)
    elif item == item_2 or item == item_1:
        return wrap_response(no_results(data), app)
    return wrap_response(invalid_params(data), app)

def m_covers(data, app):
    if len(data["params"]) < 4:
        return wrap_response(invalid_params_count(data), app)
    items = data["params"][4]
    if item_1 in items and item_2 in items:
        return wrap_response(resp_covers_3(data), app)
    elif item_1 in items:
        return wrap_response(resp_covers_1(data), app)
    elif item_2 in items:
        return wrap_response(resp_covers_2(data), app)

    return wrap_response(invalid_params(data), app)

def m_personal_recommendations(data, app):
    if len(data["params"]) < 3:
        return wrap_response(invalid_params_count(data), app)
    return wrap_response(resp_recommendations_1(data), app)

# Example
# {
#     "jsonrpc": "2.0",
#     "method": "ereolen.getLoanStatuses",
#     "params": [
#         "{{magicId}}",
#         "{{appVersion}}",
#         "{{language}}",
#         "{{library}}",
#         [
#             "eyJpIjoiOTc4ODc5NDE5ODAyOCIsInMiOiI4NzA5NzAtYmFzaXM6MzkzOTQ3NTgiLCJjIjoibmV0bHlkYm9nIn0=",
#             "eyJpIjoiOTc4ODc5MzkzNDM4MiIsInMiOiI4NzA5NzAtYmFzaXM6MzkxMTA5ODkiLCJjIjoibmV0bHlkYm9nIn0="
#         ]
#     ],
#     "id": "a5cfdd98-087e-ef4b-8a28-ae14ff05187b"
# }
def m_loan_statuses(data, app):
    if len(data["params"]) < 4:
        return wrap_response(invalid_params_count(data), app)
    items = data["params"][4]
    if item_1 in items and item_2 in items:
        return wrap_response(resp_loan_3(data), app)
    elif item_1 in items:
        return wrap_response(resp_loan_1(data), app)
    elif item_2 in items:
        return wrap_response(resp_loan_2(data), app)

    return wrap_response(invalid_params(data), app)

def m_record(data, app):
    if len(data["params"]) < 4:
        return wrap_response(invalid_params_count(data), app)
    item = data["params"][4]
    if item == item_1:
        return wrap_response(resp_record_1(data), app)

    return wrap_response(invalid_params(data), app)


# Example query
# {
#     "jsonrpc": "2.0",
#     "method": "search",
#     "params": [
#         "{{magicId}}",
#         "{{appVersion}}",
#         "{{language}}",
#         "{{library}}",
#         "Krimi",
#         0,
#         10,
#         {
#             "redia.type": "E-bog",
#             "facet.category": "voksenmaterialer"
#         },
#         ""
#     ],
#     "id": "43ff6c1e-a01d-5459-aa71-93cf5ff00529"
# }
def m_search_string(data, app):
    if len(data["params"]) < 7:
        return wrap_response(invalid_params_count(data), app)
    query, start, end, facets = data["params"][4], data["params"][5], data["params"][6], data["params"][7]
    if query == query_1:
        if start == 0 and end == 10 and facets == facet_sel_1:
            return wrap_response(resp_search_1(data), app)
        else:
            return wrap_response(no_results(data), app)
    return wrap_response(invalid_params(data), app)




#TODO: Fill in mock data
def resp_about_creator_1(data):
    return no_results(data)
def resp_reviews_1(data):
    return {
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": [
                {
                    "source": "Lektørudtalelse",
                    "subTitle": "En meget spændende og eventyrlig beretning fra en helt speciel jordomrejse, der ville have fået mindre erfarne rejsende til at give op allerede i Stockholm",
                    "url": "https://ereolen.dk/ting/object/870976-anmeld:129415452/fulltext"
                },
                {
                    "source": "Litteratursiden",
                    "subTitle": "De to danske globetrottere, Hjalte og Nina, er på jordomrejse i en elbil. De er hele tiden på udkig efter næste opladningsmulighed, og det giver en noget anderledes rejseskildring. Det er egentlig en ...",
                    "url": "http://litteratursiden.dk/anmeldelser/helt-elektrisk-jorden-rundt-af-nina-rasmussen-og-hjalte-tin"
                }
            ],
            "code": 0,
            "message": ""
        }
    }
def resp_recommendations_1(data):
    return no_results(data)


def resp_covers_1(data):
    return {
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": {
                "eyJpIjoiOTc4ODc5NDE5ODAyOCIsInMiOiI4NzA5NzAtYmFzaXM6MzkzOTQ3NTgiLCJjIjoibmV0bHlkYm9nIn0=": {
                    "result": True,
                    "data": {
                        "url": "https://images.pubhub.dk/01/bdc2ef78-6846-414a-8527-b591b48a6c96.png"
                    },
                    "code": 0,
                    "message": ""
                }
            },
            "code": 0,
            "message": ""
        }
    }
def resp_covers_2(data):
    return {
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": {
                "eyJpIjoiOTc4ODc5MzkzNDM4MiIsInMiOiI4NzA5NzAtYmFzaXM6MzkxMTA5ODkiLCJjIjoibmV0bHlkYm9nIn0=": {
                    "result": True,
                    "data": {
                        "url": "https://images.pubhub.dk/01/9a592726-dced-41a5-8391-dceeead26dca.jpg"
                    },
                    "code": 0,
                    "message": ""
                }
            },
            "code": 0,
            "message": ""
        }
    }
def resp_covers_3(data):
    return {
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": {
                "eyJpIjoiOTc4ODc5NDE5ODAyOCIsInMiOiI4NzA5NzAtYmFzaXM6MzkzOTQ3NTgiLCJjIjoibmV0bHlkYm9nIn0=": {
                    "result": True,
                    "data": {
                        "url": "https://images.pubhub.dk/01/bdc2ef78-6846-414a-8527-b591b48a6c96.png"
                    },
                    "code": 0,
                    "message": ""
                },
                "eyJpIjoiOTc4ODc5MzkzNDM4MiIsInMiOiI4NzA5NzAtYmFzaXM6MzkxMTA5ODkiLCJjIjoibmV0bHlkYm9nIn0=": {
                    "result": True,
                    "data": {
                        "url": "https://images.pubhub.dk/01/9a592726-dced-41a5-8391-dceeead26dca.jpg"
                    },
                    "code": 0,
                    "message": ""
                }
            },
            "code": 0,
            "message": ""
        }
    }


def resp_record_1(data):
    return {
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": {
                "identifier": "eyJpIjoiOTc4ODc5NDE5ODAyOCIsImMiOiJuZXRseWRib2cifQ==",
                "title": "True Crime - del 1",
                "publisher": "Lyngby-Taarbæk Bibliotekerne",
                "createdDate": 1625043053,
                "updatedDate": 1625043053,
                "cover": "https://images.pubhub.dk/01/bdc2ef78-6846-414a-8527-b591b48a6c96.png",
                "thumbnail": "https://images.pubhub.dk/27/bdc2ef78-6846-414a-8527-b591b48a6c96.png",
                "contributors": [
                    {
                        "type": "aut",
                        "composedName": "Lyngby-Taarbæk Bibliotekerne",
                        "firstName": "Lyngby-Taarbæk",
                        "lastName": "Bibliotekerne"
                    },
                    {
                        "type": "nrt",
                        "composedName": "Lea Fløe Christensen",
                        "firstName": "Lea",
                        "lastName": "Fløe Christensen"
                    },
                    {
                        "type": "nrt",
                        "composedName": "Ole Dissing",
                        "firstName": "Ole",
                        "lastName": "Dissing"
                    }
                ],
                "description": "I denne uge har lytteren Martin skrevet til os i Bogbrevkassen for at få inspiration til romaner, der handler om éneren og mønsterbryderen. Lise, Silja og Patrick har derfor gravet i bogsamlingen og fundet en rund håndfuld romankarakterer, der er fulde af gåpåmod og visioner.\nI bogsnakken kommer vi forbi et af de helt store værker fra den danske litteraturkanon, henover den danske verdensstjerne der blev glemt og videre ud i den store verden, hvor vi møder unge mennesker der bryder med ophav og samfundsnormer. Vi snakker om romankarakterer der viser, hvad det vil sige at være en mønsterbryder. Og om medrivende historier, der har sat sig i kødet på os - bittersøde bøger, der skærer i hjertet, samtidig med at de giver mod og livslyst i en tid hvor verden synes et vakuum og handlerummet begrænset.\nSe anbefalingerne på www.lyngbybib.dk/nyheder/podcast/bogbrevkassen-16\nMedvirkende: Lise Roest-Madsen, Silja Attrup og Patrick Søgaard. Redigering: Ole Dissing. Musik: Nikolaj Lind Christensen\nOg husk, at bogbrevkassens bagmænd meget gerne modtager breve fra folk, der mangler gode boganbefalinger. Skriv til Lise, Lea, Aske og Silja på info@ltk.dk.",
                "isbn": "9788794198028",
                "phid": "bdc2ef78-6846-414a-8527-b591b48a6c96",
                "firstPublished": 1623628800,
                "language": "{{language}}",
                "duration": 0,
                "format": "",
                "mediaType": "audio"
            },
            "code": 0,
            "message": ""
        }
    }

def resp_loan_1(data):
    return {
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": {
                "eyJpIjoiOTc4ODc5NDE5ODAyOCIsInMiOiI4NzA5NzAtYmFzaXM6MzkzOTQ3NTgiLCJjIjoibmV0bHlkYm9nIn0=": {
                    "result": True,
                    "data": {
                        "identifier": "eyJpIjoiOTc4ODc5NDE5ODAyOCIsInMiOiI4NzA5NzAtYmFzaXM6MzkzOTQ3NTgiLCJjIjoibmV0bHlkYm9nIn0=",
                        "loanStatus": "loanable"
                    },
                    "code": 0,
                    "message": ""
                }
            },
            "code": 0,
            "message": ""
        }
    }
def resp_loan_2(data):
    return {
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": {
                "eyJpIjoiOTc4ODc5MzkzNDM4MiIsInMiOiI4NzA5NzAtYmFzaXM6MzkxMTA5ODkiLCJjIjoibmV0bHlkYm9nIn0=": {
                    "result": True,
                    "data": {
                        "identifier": "eyJpIjoiOTc4ODc5MzkzNDM4MiIsInMiOiI4NzA5NzAtYmFzaXM6MzkxMTA5ODkiLCJjIjoibmV0bHlkYm9nIn0=",
                        "loanStatus": "loanable"
                    },
                    "code": 0,
                    "message": ""
                }
            },
            "code": 0,
            "message": ""
        }
    }
def resp_loan_3(data):
    return {
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": {
                "eyJpIjoiOTc4ODc5NDE5ODAyOCIsInMiOiI4NzA5NzAtYmFzaXM6MzkzOTQ3NTgiLCJjIjoibmV0bHlkYm9nIn0=": {
                    "result": True,
                    "data": {
                        "identifier": "eyJpIjoiOTc4ODc5NDE5ODAyOCIsInMiOiI4NzA5NzAtYmFzaXM6MzkzOTQ3NTgiLCJjIjoibmV0bHlkYm9nIn0=",
                        "loanStatus": "loanable"
                    },
                    "code": 0,
                    "message": ""
                },
                "eyJpIjoiOTc4ODc5MzkzNDM4MiIsInMiOiI4NzA5NzAtYmFzaXM6MzkxMTA5ODkiLCJjIjoibmV0bHlkYm9nIn0=": {
                    "result": True,
                    "data": {
                        "identifier": "eyJpIjoiOTc4ODc5MzkzNDM4MiIsInMiOiI4NzA5NzAtYmFzaXM6MzkxMTA5ODkiLCJjIjoibmV0bHlkYm9nIn0=",
                        "loanStatus": "loanable"
                    },
                    "code": 0,
                    "message": ""
                }
            },
            "code": 0,
            "message": ""
        }
    }




def resp_same_title_1(data):
    return {
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": {
                "ebook": None,
                "audiobook": {
                    "identifier": "eyJpIjoiOTc4ODc5NDE5ODAyOCIsInMiOiI4NzA5NzAtYmFzaXM6MzkzOTQ3NTgiLCJjIjoibmV0bHlkYm9nIn0=",
                    "title": "True crime. 1",
                    "creators": [],
                    "abstract": "Kommer bl.a. omkring hvad der sker i lokalsamfundet eller i en familie efter et mord og hvad der foregår i hovedet på en morder. Kommer også omkring økonomisk svindel, Silicon Valley, Me Too og uopklarede historiske mordsager",
                    "description": "Downloades i MP3-format",
                    "series": [
                        "Bogbrevkassen",
                        "True crime"
                    ],
                    "publisher": "Lyngby-Taarbæk Bibliotekerne",
                    "year": "2021",
                    "edition": "",
                    "isbn": "9788794198028",
                    "language": "Dansk",
                    "subjects": [
                        "litteratur",
                        "true crime",
                        "litteraturanmeldelser"
                    ],
                    "types": [
                        "Lydbog"
                    ],
                    "shelfmark": "81.09 > True",
                    "icon": "audiobook",
                    "seriesPart": "[1] \"True crime\"",
                    "subscription": "ERA202129",
                    "eReolenGlobalUrl": "",
                    "mediaType": "audio"
                }
            },
            "code": 0,
            "message": ""
        }
    }

def resp_similar_1(data):
    return {
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": [
                {
                    "identifier": "eyJpIjoiOTc4ODcyNjY0Nzg3NyIsInMiOiI4NzA5NzAtYmFzaXM6MzkwNDcyODQiLCJjIjoibmV0bHlkYm9nIn0=",
                    "title": "Sov godt, fald i søvn på på 15 minutter med guidet meditation (15 minutter)",
                    "creators": [
                        "Metta Myrna (f. 1972)",
                        "Myrna, Metta"
                    ],
                    "abstract": "Meditation til børn for at falde i søvn",
                    "description": "Downloades i MP3-format",
                    "series": [],
                    "publisher": "Lindhardt og Ringhof",
                    "year": "2020",
                    "edition": "",
                    "isbn": "9788726647877",
                    "language": "Dansk",
                    "subjects": [
                        "mindfulness",
                        "meditation",
                        "søvn"
                    ],
                    "types": [
                        "Lydbog"
                    ],
                    "shelfmark": "61.36 > Myrna",
                    "icon": "audiobook",
                    "seriesPart": "",
                    "subscription": "ERA202130",
                    "eReolenGlobalUrl": "",
                    "mediaType": "audio"
                },
                {
                    "identifier": "eyJpIjoiOTc4ODcyNjY0Nzk4MyIsInMiOiI4NzA5NzAtYmFzaXM6MzkwNDcyMzMiLCJjIjoibmV0bHlkYm9nIn0=",
                    "title": "God nat, afslut dagen med 10 minutters guidet meditation",
                    "creators": [
                        "Metta Myrna (f. 1972)",
                        "Myrna, Metta"
                    ],
                    "abstract": "",
                    "description": "Titlen hentet fra indgangssiden",
                    "series": [],
                    "publisher": "Lindhardt og Ringhof",
                    "year": "2020",
                    "edition": "",
                    "isbn": "9788726647983",
                    "language": "Dansk",
                    "subjects": [
                        "mindfulness",
                        "meditation",
                        "søvn"
                    ],
                    "types": [
                        "Lydbog"
                    ],
                    "shelfmark": "61.36 > Myrna",
                    "icon": "audiobook",
                    "seriesPart": "",
                    "subscription": "ERA202137",
                    "eReolenGlobalUrl": "",
                    "mediaType": "audio"
                }
            ],
            "code": 0,
            "message": ""
        }
    }

def resp_same_series_1(data):
    return {
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": {
                "count": 19,
                "more": True,
                "collections": [
                    {
                        "size": 1,
                        "records": [
                            {
                                "identifier": "eyJpIjoiOTc4ODc5NDE5ODAzNSIsInMiOiI4NzA5NzAtYmFzaXM6MzkzOTQ3MzEiLCJjIjoibmV0bHlkYm9nIn0=",
                                "title": "True crime. 2",
                                "creators": [],
                                "abstract": "Om at grave i kilder, hvor en kriminel underverden og parallelsamfund dukker frem, om et tragisk dødsfald i de øverste kendislag, der bliver allemandsret og opføres som operette. Og om en sag, der trækker tråde helt indenfor Lyngby bibliotekets egne mure",
                                "description": "Downloades i MP3-format",
                                "series": [
                                    "Bogbrevkassen",
                                    "True crime"
                                ],
                                "publisher": "Lyngby-Taarbæk Bibliotekerne",
                                "year": "2021",
                                "edition": "",
                                "isbn": "9788794198035",
                                "language": "Dansk",
                                "subjects": [
                                    "litteratur",
                                    "true crime",
                                    "litteraturanmeldelser"
                                ],
                                "types": [
                                    "Lydbog"
                                ],
                                "shelfmark": "81.09 > True",
                                "icon": "audiobook",
                                "seriesPart": "[2] \"True crime\"",
                                "subscription": "ERA202129",
                                "eReolenGlobalUrl": "",
                                "mediaType": "audio"
                            }
                        ]
                    },
                    {
                        "size": 1,
                        "records": [
                            {
                                "identifier": "eyJpIjoiOTc4ODc5ODg2MjIyMiIsInMiOiI4NzA5NzAtYmFzaXM6NDg0MjUzNDgiLCJjIjoibmV0bHlkYm9nIn0=",
                                "title": "Havbøger til kaptajnen, der keder sig med Moby Dick",
                                "creators": [],
                                "abstract": "Podcast med anbefalinger på konkrete og eksistentielle havbøger til en kaptajn, der keder sig med Moby Dick",
                                "description": "Downloades i MP3-format",
                                "series": [
                                    "Bogbrevkassen"
                                ],
                                "publisher": "Lyngby-Taarbæk Bibliotekerne",
                                "year": "2020",
                                "edition": "",
                                "isbn": "9788798862222",
                                "language": "Dansk",
                                "subjects": [
                                    "litteratur",
                                    "litteraturanmeldelser"
                                ],
                                "types": [
                                    "Podcast"
                                ],
                                "shelfmark": "81.04 > Havbøger",
                                "icon": "podcast",
                                "seriesPart": "[2] \"Bogbrevkassen\"",
                                "subscription": "ERA202035",
                                "eReolenGlobalUrl": "",
                                "mediaType": "audio"
                            }
                        ]
                    }
                ],
                "facets": []
            },
            "code": 0,
            "message": ""
        }
    }

def resp_same_creator_1(data):
    return {
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": {
                "count": 21,
                "more": True,
                "collections": [
                    {
                        "size": 1,
                        "records": [
                            {
                                "identifier": "eyJpIjoiOTc4ODc5MzkzNDQ4MSIsInMiOiI4NzA5NzAtYmFzaXM6NjE0Njg5MTkiLCJjIjoibmV0bHlkYm9nIn0=",
                                "title": "Rock, vilde kvinder og mørke undertoner",
                                "creators": [
                                    "Claus Vittus",
                                    "Vittus, Claus"
                                ],
                                "abstract": "Præsentation af fire bøger der hver på sin måde handler om rock- og popmusik: \"Vilde kvinder, mørke toner\", \"Rock & stjernestøv\", \"Clapton\" og \"Nowhere man\"",
                                "description": "Downloades i MP3-format",
                                "series": [
                                    "Bogdate"
                                ],
                                "publisher": "Københavns Biblioteker, Lyd",
                                "year": "2021",
                                "edition": "",
                                "isbn": "9788793934481",
                                "language": "Dansk",
                                "subjects": [
                                    "litteratur",
                                    "rock",
                                    "pop",
                                    "litteraturanmeldelser"
                                ],
                                "types": [
                                    "Lydbog"
                                ],
                                "shelfmark": "81.04 > Vittus",
                                "icon": "audiobook",
                                "seriesPart": "[6] \"Bogdate\"",
                                "subscription": "ERA202141",
                                "eReolenGlobalUrl": "",
                                "mediaType": "audio"
                            }
                        ]
                    },
                    {
                        "size": 1,
                        "records": [
                            {
                                "identifier": "eyJpIjoiOTc4ODc5MzkzNDY3MiIsInMiOiI4NzA5NzAtYmFzaXM6NjIxODc4ODMiLCJjIjoibmV0bHlkYm9nIn0=",
                                "title": "Gasolin, Halfdan & Christianshavn, Christianshavn er et kulturelt smørhul med alternativ livsform",
                                "creators": [
                                    "Claus Vittus",
                                    "Vittus, Claus"
                                ],
                                "abstract": "\"Gasolin' - gudernes vilje\" handler både om Gasolin' og om det Christianshavn som de kom fra. Interview med en af bogens forfattere, Jacob Wendt Jensen. Bogdate har også Halfdan Rasmussen og 1800-talsforfatteren Vilhelm Bergsøes beskrivelser af Christianshavn under koleraepidemien i sommeren 1853 på programmet",
                                "description": "Downloades i MP3-format",
                                "series": [
                                    "Bogdate"
                                ],
                                "publisher": "Københavns Biblioteker, Lyd",
                                "year": "2022",
                                "edition": "",
                                "isbn": "9788793934672",
                                "language": "Dansk",
                                "subjects": [
                                    "litteratur",
                                    "litteraturanmeldelser"
                                ],
                                "types": [
                                    "Lydbog"
                                ],
                                "shelfmark": "81.04 > Vittus",
                                "icon": "audiobook",
                                "seriesPart": "[10] \"Bogdate\"",
                                "subscription": "ERA202209",
                                "eReolenGlobalUrl": "",
                                "mediaType": "audio"
                            }
                        ]
                    }
                ],
                "facets": []
            },
            "code": 0,
            "message": ""
        }
    }

def resp_same_genre_1(data):
    return {
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": {
                "count": 564,
                "more": True,
                "collections": [
                    {
                        "size": 1,
                        "records": [
                            {
                                "identifier": "eyJpIjoiOTc4ODc5ODg2MjI2MCIsInMiOiI4NzA5NzAtYmFzaXM6NDg0NDM3MjkiLCJjIjoibmV0bHlkYm9nIn0=",
                                "title": "Bøger man bliver klogere af",
                                "creators": [],
                                "abstract": "Podcast med anbefalinger på bøger, man bliver klogere af og bringer én ind i litteraturen og fordybelsen",
                                "description": "Downloades i MP3-format",
                                "series": [
                                    "Bogbrevkassen"
                                ],
                                "publisher": "Lyngby-Taarbæk Bibliotekerne",
                                "year": "2020",
                                "edition": "",
                                "isbn": "9788798862260",
                                "language": "Dansk",
                                "subjects": [
                                    "litteratur",
                                    "litteraturanmeldelser"
                                ],
                                "types": [
                                    "Podcast"
                                ],
                                "shelfmark": "81.04 > Bøger",
                                "icon": "podcast",
                                "seriesPart": "[6] \"Bogbrevkassen\"",
                                "subscription": "ERA202035",
                                "eReolenGlobalUrl": "",
                                "mediaType": "audio"
                            }
                        ]
                    },
                    {
                        "size": 1,
                        "records": [
                            {
                                "identifier": "eyJpIjoiOTc4ODc5MzkzNDM4MiIsInMiOiI4NzA5NzAtYmFzaXM6MzkxMTA5ODkiLCJjIjoibmV0bHlkYm9nIn0=",
                                "title": "Med Bjælken i mit øje, sexus, HHV og Philip K. Dick",
                                "creators": [
                                    "Claus Vittus",
                                    "Vittus, Claus"
                                ],
                                "abstract": "Interview med Carsten Jensen om \"Bjælken i mit øje\", litteraturformidler Rasmus Riiskjær fra Husum Bibliotek anbefaler \"HHV Frshwn\" af Hanne Høigaard Viemose, forfatteren Martin Kongstad fortæller om Henry Millers \"Sexus\" og podcastværten Claus Vittus egen anbefaling er \"Filmatiserede noveller\" af Philip K. Dick",
                                "description": "Downloades i MP3-format",
                                "series": [
                                    "Bogdate"
                                ],
                                "publisher": "Københavns Biblioteker, Lyd",
                                "year": "2021",
                                "edition": "",
                                "isbn": "9788793934382",
                                "language": "Dansk",
                                "subjects": [
                                    "litteratur",
                                    "litteraturanmeldelser"
                                ],
                                "types": [
                                    "Lydbog"
                                ],
                                "shelfmark": "81.04 > Vittus",
                                "icon": "audiobook",
                                "seriesPart": "[2] \"Bogdate\"",
                                "subscription": "ERA202135",
                                "eReolenGlobalUrl": "",
                                "mediaType": "audio"
                            }
                        ]
                    }
                ],
                "facets": []
            },
            "code": 0,
            "message": ""
        }
    }
def resp_same_genre_2(data):
    return {
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": {
                "count": 564,
                "more": True,
                "collections": [
                    {
                        "size": 1,
                        "records": [
                            {
                                "identifier": "eyJpIjoiOTc4ODc5MzkzNDM4MiIsInMiOiI4NzA5NzAtYmFzaXM6MzkxMTA5ODkiLCJjIjoibmV0bHlkYm9nIn0=",
                                "title": "Med Bjælken i mit øje, sexus, HHV og Philip K. Dick",
                                "creators": [
                                    "Claus Vittus",
                                    "Vittus, Claus"
                                ],
                                "abstract": "Interview med Carsten Jensen om \"Bjælken i mit øje\", litteraturformidler Rasmus Riiskjær fra Husum Bibliotek anbefaler \"HHV Frshwn\" af Hanne Høigaard Viemose, forfatteren Martin Kongstad fortæller om Henry Millers \"Sexus\" og podcastværten Claus Vittus egen anbefaling er \"Filmatiserede noveller\" af Philip K. Dick",
                                "description": "Downloades i MP3-format",
                                "series": [
                                    "Bogdate"
                                ],
                                "publisher": "Københavns Biblioteker, Lyd",
                                "year": "2021",
                                "edition": "",
                                "isbn": "9788793934382",
                                "language": "Dansk",
                                "subjects": [
                                    "litteratur",
                                    "litteraturanmeldelser"
                                ],
                                "types": [
                                    "Lydbog"
                                ],
                                "shelfmark": "81.04 > Vittus",
                                "icon": "audiobook",
                                "seriesPart": "[2] \"Bogdate\"",
                                "subscription": "ERA202135",
                                "eReolenGlobalUrl": "",
                                "mediaType": "audio"
                            }
                        ]
                    },
                    {
                        "size": 1,
                        "records": [
                            {
                                "identifier": "eyJpIjoiOTc4ODc5NzI1MDAzNyIsInMiOiI4NzA5NzAtYmFzaXM6Mzg4MjE0MzEiLCJjIjoibmV0bHlkYm9nIn0=",
                                "title": "Ferielæsning",
                                "creators": [],
                                "abstract": "Anbefalinger til ferielæsning, både for folk, der bare vil hyggelæse med et smil på læben og folk, der gerne vil høre store, dragende fortællinger",
                                "description": "Downloades i MP3-format",
                                "series": [
                                    "Bogbrevkassen"
                                ],
                                "publisher": "Lyngby-Taarbæk Bibliotekerne",
                                "year": "2020",
                                "edition": "",
                                "isbn": "9788797250037",
                                "language": "Dansk",
                                "subjects": [
                                    "litteratur",
                                    "litteraturanmeldelser"
                                ],
                                "types": [
                                    "Lydbog"
                                ],
                                "shelfmark": "81.04 > Ferielæsning",
                                "icon": "audiobook",
                                "seriesPart": "",
                                "subscription": "ERA202118",
                                "eReolenGlobalUrl": "",
                                "mediaType": "audio"
                            }
                        ]
                    },
                    {
                        "size": 1,
                        "records": [
                            {
                                "identifier": "eyJpIjoiOTc4ODc5MzkzNDY3MiIsInMiOiI4NzA5NzAtYmFzaXM6NjIxODc4ODMiLCJjIjoibmV0bHlkYm9nIn0=",
                                "title": "Gasolin, Halfdan & Christianshavn, Christianshavn er et kulturelt smørhul med alternativ livsform",
                                "creators": [
                                    "Claus Vittus",
                                    "Vittus, Claus"
                                ],
                                "abstract": "\"Gasolin' - gudernes vilje\" handler både om Gasolin' og om det Christianshavn som de kom fra. Interview med en af bogens forfattere, Jacob Wendt Jensen. Bogdate har også Halfdan Rasmussen og 1800-talsforfatteren Vilhelm Bergsøes beskrivelser af Christianshavn under koleraepidemien i sommeren 1853 på programmet",
                                "description": "Downloades i MP3-format",
                                "series": [
                                    "Bogdate"
                                ],
                                "publisher": "Københavns Biblioteker, Lyd",
                                "year": "2022",
                                "edition": "",
                                "isbn": "9788793934672",
                                "language": "Dansk",
                                "subjects": [
                                    "litteratur",
                                    "litteraturanmeldelser"
                                ],
                                "types": [
                                    "Lydbog"
                                ],
                                "shelfmark": "81.04 > Vittus",
                                "icon": "audiobook",
                                "seriesPart": "[10] \"Bogdate\"",
                                "subscription": "ERA202209",
                                "eReolenGlobalUrl": "",
                                "mediaType": "audio"
                            }
                        ]
                    }
                ],
                "facets": []
            },
            "code": 0,
            "message": ""
        }
    }




def resp_search_1(data):
    return {
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": {
                "count": 4395,
                "more": True,
                "collections": [
                    {
                        "size": 1,
                        "records": [
                            {
                                "identifier": "eyJpIjoiOTc4ODc3MDM2MzMyNyIsInMiOiI4NzA5NzAtYmFzaXM6NDYzMzMxMjgiLCJjIjoiZXJlb2xlbiJ9",
                                "title": "Der hvor solen aldrig skinner, skæbnehistorier fra danske fængsler, true crime",
                                "creators": [
                                    "Peter Grønlund (f. 1970-04-11)",
                                    "Grønlund, Peter"
                                ],
                                "abstract": "Tidligere straffede personer fortæller om hvordan de oplevede at sidde indespærret, og hvorfor de overhovedet havnede bag tremmer",
                                "description": "Downloades i EPUB-format",
                                "series": [],
                                "publisher": "Momenta",
                                "year": "2019",
                                "edition": "1. udgave",
                                "isbn": "9788770363327",
                                "language": "Dansk",
                                "subjects": [
                                    "forbrydelser",
                                    "kriminelle",
                                    "kriminalitet",
                                    "fængsler",
                                    "fanger",
                                    "fængselsvæsen",
                                    "fængselsophold"
                                ],
                                "types": [
                                    "E-bog"
                                ],
                                "shelfmark": "34.35 > Grønlund",
                                "icon": "ebook",
                                "seriesPart": "",
                                "subscription": "",
                                "eReolenGlobalUrl": "",
                                "mediaType": "text"
                            }
                        ]
                    },
                    {
                        "size": 1,
                        "records": [
                            {
                                "identifier": "eyJpIjoiOTc4ODc3MTc0NTE5MSIsInMiOiI4NzA5NzAtYmFzaXM6NTIwNzkyMTciLCJjIjoiZXJlb2xlbiJ9",
                                "title": "Stormagasinets hemmelighed, krimi noir",
                                "creators": [
                                    "Ellery Queen",
                                    "Queen, Ellery"
                                ],
                                "abstract": "Krimi. Stormagasinet French er berømt for sit udbud af sjældne varer, men ingen havde dog regnet med noget så sjældent som det syn, der møder folk, da den nye vinduesudstilling bliver afsløret",
                                "description": "Downloades i EPUB-format",
                                "series": [],
                                "publisher": "Rosenkilde & Bahnhof",
                                "year": "2015",
                                "edition": "1. RB-udgave (1. ebogsudgave)",
                                "isbn": "9788771745191",
                                "language": "Dansk",
                                "subjects": [],
                                "types": [
                                    "E-bog"
                                ],
                                "shelfmark": "Queen",
                                "icon": "ebook",
                                "seriesPart": "",
                                "subscription": "ERA201603",
                                "eReolenGlobalUrl": "",
                                "mediaType": "text"
                            }
                        ]
                    }
                ],
                "facets": [
                    {
                        "name": "redia.type",
                        "terms": [
                            {
                                "term": "E-bog",
                                "value": "ebog",
                                "quantity": 4395
                            },
                            {
                                "term": "tegneserie (net)",
                                "value": "tegneserie (net)",
                                "quantity": 2
                            }
                        ],
                        "type": "buttons",
                        "translationKey": "key__filter_facet__type"
                    },
                    {
                        "name": "facet.subject",
                        "terms": [
                            {
                                "term": "krimi",
                                "value": "krimi",
                                "quantity": 2386
                            },
                            {
                                "term": "electronic books",
                                "value": "electronic books",
                                "quantity": 1750
                            },
                            {
                                "term": "fiction",
                                "value": "fiction",
                                "quantity": 1634
                            }
                        ],
                        "type": "list",
                        "translationKey": "key__filter_facet__subject"
                    }
                ]
            },
            "code": 0,
            "message": ""
        }
    }
