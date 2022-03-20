from flask import request
import json
from common import wrap_response, invalid_params


def m_library_profile(data, app):

    if "alleroedbib" in data["params"]:
        return wrap_response({
            "jsonrpc": "2.0",
            "id": data["id"] if "id" in data else "",
            "result": {
                "result": True,
                "data": {
                    "maxConcurrentLoansPerBorrower": 10,
                    "maxConcurrentReservationsPerBorrower": 3,
                    "maxConcurrentAudioLoansPerBorrower": 10,
                    "maxConcurrentAudioReservationsPerBorrower": 3
                },
                "code": 0,
                "message": ""
            }
        }, app)
    elif "odensebib" in data["params"]:
        return wrap_response({
            "jsonrpc": "2.0",
            "id": data["id"] if "id" in data else "",
            "result": {
                "result": True,
                "data": {
                    "maxConcurrentLoansPerBorrower": 3,
                    "maxConcurrentReservationsPerBorrower": 3,
                    "maxConcurrentAudioLoansPerBorrower": 3,
                    "maxConcurrentAudioReservationsPerBorrower": 3
                },
                "code": 0,
                "message": ""
            }
        }, app)
    else:
        return wrap_response(invalid_params(data), app)


def m_loans(data, app):
    return wrap_response({
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": [
                {
                    "identifier": "eyJpIjoiOTc4ODcyNjE1MzY2OCIsImMiOiJlcmVvbGVuIn0=",
                    "isbn": "9788726153668",
                    "retailerOrderNumber": "3002cc7e-90d4-4f67-bc76-de62590423db",
                    "internalOrderNumber": "7ab14d7f-4b75-4f9b-b3d5-ffffb7422cd8",
                    "orderDate": 1643587442,
                    "expireDate": 1646179441,
                    "downloadUrl": "http://acs.pubhub.dk:8080/fulfillment/URLLink.acsm?action=enterloan&ordersource=Pubhub&orderid=7ab14d7f-4b75-4f9b-b3d5-ffffb7422cd8&resid=urn%3Auuid%3A8fcc0bc8-e75e-450a-a969-c292a0b478f0&rights=%24lat%231646175841%24&gbauthdate=01%2f30%2f2022+23%3a04+UTC&dateval=1643587441&gblver=4&auth=6ba3d8b243bef18e4c5c4a6575ffc83aeb6b7482",
                    "isSubscription": True
                },
                {
                    "identifier": "eyJpIjoiOTc4ODc2NDQ4MDkyNCIsImMiOiJuZXRseWRib2cifQ==",
                    "isbn": "9788764480924",
                    "retailerOrderNumber": "cb39652b-204c-445a-b68c-04b6a953110f",
                    "internalOrderNumber": "2dc56e71-bc6e-4772-b360-f4556af7e056",
                    "orderDate": 1643587904,
                    "expireDate": 1646179903,
                    "downloadUrl": "https://download.pubhub.dk/audio/Download.ashx?cvoid=2dc56e71-bc6e-4772-b360-f4556af7e056",
                    "isSubscription": False
                },
                {
                    "identifier": "eyJpIjoiOTc4ODcyODExNzg1OSIsImMiOiJuZXRseWRib2cifQ==",
                    "isbn": "9788728117859",
                    "retailerOrderNumber": "f0b234b2-adf4-4a12-abbe-fd5b817748ce",
                    "internalOrderNumber": "fa702b8b-372b-4c7b-a534-a904bf94d5fb",
                    "orderDate": 1643588494,
                    "expireDate": 1646180493,
                    "downloadUrl": "https://download.pubhub.dk/audio/Download.ashx?cvoid=fa702b8b-372b-4c7b-a534-a904bf94d5fb",
                    "isSubscription": True
                },
                {
                    "identifier": "eyJpIjoiOTc4ODcwMjMxMjYyMSIsImMiOiJlcmVvbGVuIn0=",
                    "isbn": "9788702312621",
                    "retailerOrderNumber": "18553271-0aa7-4626-ba00-cd7f484194a4",
                    "internalOrderNumber": "0379b0c3-b2d6-406c-aef6-70a77b44ff2c",
                    "orderDate": 1643588625,
                    "expireDate": 1646180624,
                    "downloadUrl": "http://acs.pubhub.dk:8080/fulfillment/URLLink.acsm?action=enterloan&ordersource=Pubhub&orderid=0379b0c3-b2d6-406c-aef6-70a77b44ff2c&resid=urn%3Auuid%3A39369da7-a3d5-4974-b358-3f72b0344880&rights=%24lat%231646177024%24&gbauthdate=01%2f30%2f2022+23%3a23+UTC&dateval=1643588624&gblver=4&auth=a95243dee303d4a0ab7bb85ec2b5a6b612c99f65",
                    "isSubscription": False
                }
            ],
            "code": 0,
            "message": ""
        }
    }, app)

def m_checklist(data, app):
    return wrap_response({
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": [
                {
                    "identifier": "eyJpIjoiOTc4ODcwMjA5NjQwOCIsImMiOiJlcmVvbGVuIn0=",
                    "isbn": "9788702096408",
                    "creationDateUtc": 1643584514
                },
                {
                    "identifier": "eyJpIjoiOTc4ODc5OTg2Mzc5MiIsImMiOiJlcmVvbGVuIn0=",
                    "isbn": "9788799863792",
                    "creationDateUtc": 1643584466
                },
                {
                    "identifier": "eyJpIjoiOTc4ODc5MzczNzI3MyIsImMiOiJlcmVvbGVuIn0=",
                    "isbn": "9788793737273",
                    "creationDateUtc": 1643584445
                },
                {
                    "identifier": "eyJpIjoiOTc4ODcyODIxMzIzMCIsImMiOiJuZXRseWRib2cifQ==",
                    "isbn": "9788728213230",
                    "creationDateUtc": 1643584316
                },
                {
                    "identifier": "eyJpIjoiOTc4ODcyNjE0MTM0NCIsImMiOiJuZXRseWRib2cifQ==",
                    "isbn": "9788726141344",
                    "creationDateUtc": 1643583885
                },
                {
                    "identifier": "eyJpIjoiOTc4ODcwMjE5MTI3MSIsImMiOiJlcmVvbGVuIn0=",
                    "isbn": "9788702191271",
                    "creationDateUtc": 1643583461
                }
            ],
            "code": 0,
            "message": ""
        }
    }, app)

def m_reservations(data, app):
    return wrap_response({
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": [
                {
                    "identifier": "eyJpIjoiOTc4MTYyMzM3MjE5NCIsImMiOiJuZXRseWRib2cifQ==",
                    "isbn": "9781623372194",
                    "bookid": "9c0ede52-9e7c-4ad1-9795-9e58c7753f42",
                    "createdUtc": 1643584290,
                    "status": "queued",
                    "expireUtc": -1,
                    "expectedRedeemDateUtc": 1651270017
                }
            ],
            "code": 0,
            "message": ""
        }
    }, app)

def m_loan_history(data, app):
    return wrap_response({
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": [
                {
                    "loanId": "023a64382e6d8611b31506bb810d997abcca8f1aefd35bfe9a77c2ab4eda16f2",
                    "identifier": "eyJpIjoiOTc4ODcwMjMxMjYyMSIsInMiOiI4NzA5NzAtYmFzaXM6NjE2ODQ4OTEifQ==",
                    "loanDate": 1643588625,
                    "manuallyAdded": False,
                    "isbn": "9788702312621",
                    "title": "Pan",
                    "creator": "Knut Hamsun",
                    "publicationDate": "2021",
                    "materialTypes": [
                        "Ebog"
                    ]
                },
                {
                    "loanId": "b963fffcdec03276228276ba7a5cc938d85cf16a7382accc36c54def37a208b8",
                    "identifier": "eyJpIjoiOTc4ODcyODExNzg1OSIsInMiOiI4NzA5NzAtYmFzaXM6NjE2OTk5NTMifQ==",
                    "loanDate": 1643588494,
                    "manuallyAdded": False,
                    "isbn": "9788728117859",
                    "title": "Slaget om Stalingrad",
                    "creator": "Troels Ussing",
                    "publicationDate": "2021",
                    "materialTypes": [
                        "Lydbog (net)"
                    ]
                },
                {
                    "loanId": "ea45589fbaf653a0dd990ed70c57afe282a9aff2511609c0689c55e992c6ccab",
                    "identifier": "eyJpIjoiOTc4ODc2NDQ4MDkyNCIsInMiOiI4NzA5NzAtYmFzaXM6NjE3NDYwMDUifQ==",
                    "loanDate": 1643587904,
                    "manuallyAdded": False,
                    "isbn": "9788764480924",
                    "title": "Mord på Bretagnes kyst",
                    "creator": "Jean-Luc Bannalec",
                    "publicationDate": "2021",
                    "materialTypes": [
                        "Lydbog (net)"
                    ]
                },
                {
                    "loanId": "bf27a2896c2530f5199df78b110a1ce698d67ff99229c6653affd3634586798c",
                    "identifier": "eyJpIjoiOTc4ODcyNjE1MzY2OCIsInMiOiI4NzA5NzAtYmFzaXM6NDg5MDA3NDcifQ==",
                    "loanDate": 1643587442,
                    "manuallyAdded": False,
                    "isbn": "9788726153668",
                    "title": "Forvandlingen",
                    "creator": "Franz Kafka",
                    "publicationDate": "2020",
                    "materialTypes": [
                        "Ebog"
                    ]
                }
            ],
            "code": 0,
            "message": ""
        }
    }, app)

#TODO: Create mock data
def m_collect_events(data, app):
    return wrap_response({
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": [
                {
                    "result": True,
                    "data": None,
                    "code": 0,
                    "message": ""
                }
            ],
            "code": 0,
            "message": ""
        }
    }, app)

