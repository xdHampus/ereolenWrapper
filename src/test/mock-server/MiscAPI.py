import copy

from common import wrap_response, invalid_params, invalid_params_count
from ItemAPI import item_1, item_2, resp_record_1


# The identifiers m_loans and m_reservations hand out, so that a loan list built
# from getLoans + getRecordsByIdentifiers shows titles offline the way it does
# against the live API.
loan_titles = {
    "eyJpIjoiOTc4ODcyNjE1MzY2OCIsImMiOiJlcmVvbGVuIn0=":
        ("9788726153668", "Forvandlingen", "Franz Kafka"),
    "eyJpIjoiOTc4ODc2NDQ4MDkyNCIsImMiOiJuZXRseWRib2cifQ==":
        ("9788764480924", "Mord på Bretagnes kyst", "Jean-Luc Bannalec"),
    "eyJpIjoiOTc4ODcyODExNzg1OSIsImMiOiJuZXRseWRib2cifQ==":
        ("9788728117859", "Slaget om Stalingrad", "Troels Ussing"),
    "eyJpIjoiOTc4ODcwMjMxMjYyMSIsImMiOiJlcmVvbGVuIn0=":
        ("9788702312621", "Pan", "Knut Hamsun"),
    "eyJpIjoiOTc4MTYyMzM3MjE5NCIsImMiOiJuZXRseWRib2cifQ==":
        ("9781623372194", "The Rhythm of War", "Brandon Sanderson"),
}


# getRecordsByIdentifiers returns a map keyed by identifier, where each entry is
# itself a {result, data, code, message} envelope -- same shape as getCovers.
def m_records_by_identifier(data, app):
    if len(data["params"]) < 5:
        return wrap_response(invalid_params_count(data), app)

    identifiers = data["params"][4]
    if not isinstance(identifiers, list) or not identifiers:
        return wrap_response(invalid_params(data), app)

    # resp_record_1 is a full getProduct envelope; reuse its record payload.
    record_1 = resp_record_1(data)["result"]["data"]

    records = {}
    for identifier in identifiers:
        if identifier == item_1:
            record = record_1
        elif identifier in loan_titles:
            isbn, title, creator = loan_titles[identifier]
            record = copy.deepcopy(record_1)
            record["identifier"] = identifier
            record["isbn"] = isbn
            record["title"] = title
            record["creators"] = [creator]
        else:
            records[identifier] = {
                "result": False,
                "data": None,
                "code": 10407,
                "message": ""
            }
            continue

        records[identifier] = {
            "result": True,
            "data": record,
            "code": 0,
            "message": ""
        }

    return wrap_response({
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": records,
            "code": 0,
            "message": ""
        }
    }, app)


# createLoan takes one identifier and answers with the created loan. item_1 is
# the fixture that getLoanStatuses reports as "loanable"; item_2 is reported
# unavailable, so borrowing it fails the way the live API does.
def m_create_loan(data, app):
    if len(data["params"]) < 5:
        return wrap_response(invalid_params_count(data), app)

    identifier = data["params"][4]
    if identifier == item_2:
        return wrap_response({
            "jsonrpc": "2.0",
            "id": data["id"] if "id" in data else "",
            "result": {
                "result": False,
                "data": None,
                "code": 11675,
                "message": ""
            }
        }, app)
    if identifier != item_1:
        return wrap_response(invalid_params(data), app)

    return wrap_response({
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": {
                "identifier": item_1,
                "isbn": "9788794198028",
                "retailerOrderNumber": "0f1b6c8e-9d2a-4b71-9c3e-1a2b3c4d5e6f",
                "internalOrderNumber": "5c9a2f31-7e64-4d18-b0a5-9f8e7d6c5b4a",
                "orderDate": 1784935623,
                "expireDate": 1787527623,
                "downloadUrl": "http://acs.pubhub.dk:8080/fulfillment/URLLink.acsm?action=enterloan&ordersource=Pubhub&orderid=5c9a2f31-7e64-4d18-b0a5-9f8e7d6c5b4a",
                "isSubscription": False
            },
            "code": 0,
            "message": ""
        }
    }, app)


# The app version supported by the eReolen API. Uses the 3-param prefix (no
# library code) and needs no session.
def m_supported_version(data, app):
    return wrap_response({
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": {
                "latestVersion": "3.6.1",
                "requiredVersion": "3.6.1"
            },
            "code": 0,
            "message": ""
        }
    }, app)
