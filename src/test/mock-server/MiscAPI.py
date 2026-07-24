from common import wrap_response, invalid_params, invalid_params_count
from ItemAPI import item_1, resp_record_1


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
            records[identifier] = {
                "result": True,
                "data": record_1,
                "code": 0,
                "message": ""
            }
        else:
            records[identifier] = {
                "result": False,
                "data": None,
                "code": 10407,
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
