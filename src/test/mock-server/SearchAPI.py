
# Example query
#  {
#     "jsonrpc": "2.0",
#     "method": "search",
#     "params": [
#         "{{magicId}}",
#         "{{appVersion}}",
#         "{{language}}",
#         "{{library}}",
#         "dkcclphrase.lem=\"humor\" AND facet.extratitles=\"ekstra titler\" NOT term.type=\"lyd (podcast)\" AND facet.category=\"voksenmaterialer\"",
#         0,
#         20,
#         {},
#         ""
#     ],
#     "id": "{{uuid}}"
# }
def m_search_sql(data, app):
    return None

# Example query
#  {
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
#         {},
#         null
#     ],
#     "id": "{{uuid}}"
# }
def m_search_string(data, app):
    return None


