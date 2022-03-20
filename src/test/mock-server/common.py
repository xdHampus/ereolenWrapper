import json, os



# Get environment variables
env_api_key = os.getenv('TEST_API_KEY')
env_username = os.getenv('TEST_USERNAME')
env_password = os.getenv('TEST_PASSWORD')
env_library = os.getenv('TEST_LIBRARY')

def wrap_response(dict, app):
    return app.response_class(
        response=json.dumps(dict),
        status=200,
        mimetype='application/json'
    )

def authorized(token, active_tokens):
    return token in active_tokens



def unauthorized_access_wrapped(data, app):
    return wrap_response({
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": False,
            "data": None,
            "code": 12003,
            "message": ""
        }
    }, app)

def no_results(data):
    return {
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": True,
            "data": [],
            "code": 0,
            "message": ""
        }
    }

def invalid_params(data):
    return {
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "result": {
            "result": False,
            "data": None,
            "code": 10407,
            "message": ""
        }
    }

def invalid_params_count(data):
    return {
        "jsonrpc": "2.0",
        "id": data["id"] if "id" in data else "",
        "error": {
            "code": -32602,
            "message": "Invalid parameter count for method getLoanStatuses. Expected 5 parameters."
        }
    }

def invalid_call_data():
    return {
        "jsonrpc": "2.0",
        "id": "",
        "error": {
            "code": -32600,
            "message": "Invalid call data. Must be either a json array or object submitted via POST or GET."
        }
    }


