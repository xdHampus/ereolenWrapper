from flask import request
import uuid
import json
from common import env_username, env_password, wrap_response, authorized


def m_auth(data, active_tokens, app):
    username = data["params"][4]
    password = data["params"][5]

    if username != env_username or password != env_password:
        return {
            "jsonrpc": "2.0",
            "id": data["id"] if "id" in data else "",
            "result": {
                "result": False,
                "data": None,
                "code": 11101,
                "message": "Forkert brugernavn eller kode"
            }
        }

    resp = wrap_response({
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": {
                "shownPrivacyPolicy": 1,
                "acceptedPappsPolicy": True,
                "dbcUserGuidExist": True
            },
            "code": 0,
            "message": ""
        }
    }, app)

    new_token = uuid.uuid4().hex
    active_tokens.add(new_token)
    resp.set_cookie("PHPSESSID", new_token)
    return resp

def m_deauth(data, active_tokens, app):

    token = request.cookies.get('PHPSESSID')
    active_tokens.discard(token)

    resp = wrap_response({
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": None,
            "code": 0,
            "message": ""
        }
    }, app)
    resp.set_cookie("PHPSESSID", "")

    return resp

def m_isauth(data, active_auth, app):
    if active_auth:
        return wrap_response({
            "jsonrpc": "2.0",
            "id": data["id"] if "id" in data else "",
            "result": {
                "result": True,
                "data": True,
                "code": 0,
                "message": ""
            }
        }, app)
    else:
        return wrap_response({
            "jsonrpc": "2.0",
            "id": data["id"] if "id" in data else "",
            "result": {
                "result": True,
                "data": False,
                "code": 0,
                "message": ""
            }
        }, app)