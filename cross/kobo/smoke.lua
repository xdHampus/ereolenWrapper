--[[--
Smoke test for a cross-built libereolenwrapper.so: load the module, then walk
the login -> loans -> record-metadata path against the live API.

    EREOL_CARD=... EREOL_PIN=... EREOL_LIBRARY=odensebib \
        ./cross/kobo/qemu-run.sh cross/kobo/smoke.lua

Without credentials it stops after the unauthenticated version probe, which is
still enough to prove the module loads and can do HTTPS.
]]

require("libereolenwrapper")

-- On a device with no system trust store, point libcurl at the bundle the host
-- application ships. Unset on a desktop, where the system store applies.
local ca = os.getenv("EREOL_CA_BUNDLE")
if ca then ereol.ApiEnv.setCaBundle(ca) end

local classes = 0
for _ in pairs(ereol) do classes = classes + 1 end
print(("loaded %s, %d classes registered"):format(jit and jit.version or _VERSION, classes))

print("appVersion:", ereol.ApiEnv.getAppVersion())
local synced = ereol.ApiEnv.syncAppVersion()
print("syncAppVersion():", synced, "->", ereol.ApiEnv.getAppVersion())
if not synced then
    print("FAIL: could not reach getSupportedVersion -- check TLS and the CA bundle")
    os.exit(1)
end

local card, pin = os.getenv("EREOL_CARD"), os.getenv("EREOL_PIN")
if not (card and pin) then
    print("no EREOL_CARD/EREOL_PIN set; stopping after the version probe")
    return
end

local code = os.getenv("EREOL_LIBRARY") or "odensebib"
local library = ereol.ApiEnv.getLibraryFromCode(code)
if not library then
    print("FAIL: unknown library code " .. code)
    os.exit(1)
end

local session = ereol.Auth.authenticate(card, pin, library)
print("authenticate:", session.success, session.code, session.message)
if not session.success then os.exit(1) end
local token = session.data

-- 12003 ("no authenticated user") comes back intermittently on a session that
-- is in fact fine, so retry before giving up -- as the plugin's call() does.
local loans
for attempt = 1, 3 do
    loans = ereol.Profile.getLoans(token)
    if loans.success then break end
    print("  getLoans attempt " .. attempt .. " -> code " .. tostring(loans.code))
end
print("getLoans:", loans.success, loans.code, "n =", loans.data and #loans.data or 0)
if not loans.success then os.exit(1) end

local identifiers = {}
for i = 1, #loans.data do
    local loan = loans.data[i]
    identifiers[i] = loan.loanIdentifier.identifier
    print(("  %d. isbn=%s expires=%s"):format(i, loan.loanIdentifier.isbn,
        os.date("%Y-%m-%d", loan.expireDate)))
end
if #identifiers == 0 then return end

local records = ereol.Item.getRecords(identifiers, token)
print("getRecords:", records.success, records.code)
if not records.success then os.exit(1) end
for _, record in pairs(records.data) do
    -- ISBN lives on the nested loanIdentifier, not on the record itself.
    print(("   %s | %s | %s"):format(record.title,
        record.creators and record.creators[1] or "?",
        record.loanIdentifier.isbn))
end
