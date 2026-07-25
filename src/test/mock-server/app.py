from flask import Flask, request

from common import env_api_key, env_library, wrap_response, invalid_call_data, invalid_params, unauthorized_access_wrapped, authorized

from AuthAPI import m_auth, m_deauth, m_isauth
from ProfileAPI import m_library_profile, m_loans, m_reservations, m_checklist, m_loan_history, m_add_to_checklist, m_remove_from_checklist, m_add_reservation, m_remove_reservations
from ItemAPI import m_search_string, m_record, m_covers, m_reviews, m_same_creator, m_about_creator, m_same_series, m_same_genre, m_same_title, m_loan_statuses, m_something_similar, m_personal_recommendations
from MiscAPI import m_records_by_identifier, m_supported_version, m_create_loan

active_tokens = set()
app = Flask(__name__)


@app.route("/", methods = ['GET'])
def index():
    return "Hello! -- eReolenWrapper tests"



@app.route("/mock-rpc", methods = ['POST'])
def mock_rpc():
    data =  request.get_json(True, True, True)
    if ((data is None) == False) and ("method" in data):
        return handle_method(data)
    return wrap_response(invalid_call_data(), app)


def handle_method(data):
    method = data["method"]

    active_auth = authorized(request.cookies.get('PHPSESSID'), active_tokens)

    #getSupportedVersion uses the 3-param prefix, so it carries no library code
    #and has to be routed before the library check below.
    if method == "getSupportedVersion":
        return m_supported_version(data, app)

    #Detect whether library and api key is properly set
    if ("params" in data == False) or ((env_api_key in data["params"] == False) or ((env_library in data["params"]) == False and "alleroedbib" not in data["params"])):
        return wrap_response(invalid_params(data), app)


    #Route data to appropriate method
    ##Auth
    if method == "authenticate":
        return m_auth(data, active_tokens, app)
    elif method == "deauthenticate":
        return m_deauth(data, active_tokens, app)
    elif method == "isAuthenticated":
        return m_isauth(data, active_auth, app)

    ##
    ##Profile
    elif method == "ereolen.getLibraryProfile":
        return m_library_profile(data, app)
    elif method == "ereolen.getCheckList":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_checklist(data, app)
    elif method == "getReservations":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_reservations(data, app)
    elif method == "getLoanHistory":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_loan_history(data, app)
    elif method == "getLoans":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_loans(data, app)
    elif method == "ereolen.addToCheckList":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_add_to_checklist(data, app)
    elif method == "ereolen.removeFromCheckList":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_remove_from_checklist(data, app)
    elif method == "addReservation":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_add_reservation(data, app)
    elif method == "removeReservations":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_remove_reservations(data, app)

    ##
    ##Item
    elif method == "getOtherTypesOfSameTitle":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_same_title(data, app)
    elif method == "getMoreOfSameGenre":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_same_genre(data, app)
    elif method == "getMoreOfSameCreator":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_same_creator(data, app)
    elif method == "getMoreInSameSeries":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_same_series(data, app)
    elif method == "getSomethingSimilar":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_something_similar(data, app)
    elif method == "getAboutCreators":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_about_creator(data, app)
    elif method == "getReviews":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_reviews(data, app)
    elif method == "getCovers":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_covers(data, app)
    elif method == "getPersonalRecommendations":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_personal_recommendations(data, app)
    elif method == "ereolen.getLoanStatuses":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_loan_statuses(data, app)
    elif method == "getProduct":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_record(data, app)
    elif method == "getRecordsByIdentifiers":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_records_by_identifier(data, app)
    elif method == "createLoan":
        if not active_auth:
            return unauthorized_access_wrapped(data, app)
        return m_create_loan(data, app)
    elif method == "search":
        return m_search_string(data, app)




    return wrap_response({
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "error": {
            "code": -32601,
            "message": "No method named " +method+" exists"
        }
    }, app)



