#ifndef EREOLENWRAPPER_RESPONSELUA_H
#define EREOLENWRAPPER_RESPONSELUA_H
#include "../model/Response.h"


namespace luabridge {
    template<class T>
    struct Stack<ereol::Response<T>>
{
    static void push(lua_State* L, ereol::Response<T> const& response) {
        bool containsData = response.data() != std::nullopt && response.data().has_value();
        lua_createtable(L, 0, containsData ? 4 : 3);


        if(containsData)
        {
            Stack<std::string>::push(L, "data");
            Stack<T>::push(L, *response.data());
            lua_settable(L, -3);
        }

        Stack<std::string>::push(L, "success");
        Stack<bool>::push(L, response.success());
        lua_settable(L, -3);

        Stack<std::string>::push(L, "message");
        Stack<std::string>::push(L, response.message());
        lua_settable(L, -3);

        Stack<std::string>::push(L, "detailedMessage");
        Stack<std::string>::push(L, (response.detailedMessage()) ? *response.detailedMessage() : "");
        lua_settable(L, -3);

    }

    static ereol::Response<T> get(lua_State* L, int index)
    {
        if (!lua_istable(L, index))
        {
            luaL_error(L, "#%d argument must be a table", index);
        }

        size_t len = lua_objlen(L,1);

        int const absindex = lua_absindex(L, index);
        lua_pushnil(L);
        std::optional<T> data = std::nullopt;
        if(len == 4) {
            lua_next(L, absindex);
            Stack<std::string>::get(L, -2);
            data = std::optional(Stack<T>::get(L, -1));
            lua_pop(L, 1);
        }

        lua_next(L, absindex);
        Stack<std::string>::get(L, -2);
        bool success = Stack<bool>::get(L, -1);
        lua_pop(L, 1);

        lua_next(L, absindex);
        Stack<std::string>::get(L, -2);
        std::string message = Stack<std::string>::get(L, -1);
        lua_pop(L, 1);

        lua_next(L, absindex);
        Stack<std::string>::get(L, -2);
        std::optional<std::string> detailedMessage = std::optional(Stack<std::string>::get(L, -1));
        lua_pop(L, 1);

        return ereol::Response<T>(data, message, success, detailedMessage);
    }

    static bool isInstance(lua_State* L, int index) { return lua_istable(L, index); }
};

} // namespace luabridge

#endif //EREOLENWRAPPER_RESPONSELUA_H
