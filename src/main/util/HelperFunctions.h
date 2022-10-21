#ifndef EREOLENWRAPPER_HELPERFUNCTIONS_H
#define EREOLENWRAPPER_HELPERFUNCTIONS_H

namespace ereol {
    //TODO: C++23, Replace with equivalent std::optional<T>.or_else method
    template<typename _Func, typename T>
    constexpr T or_else(std::optional<T> opt, _Func&& __f) {
        static_assert(std::is_same_v<std::remove_cvref_t<std::invoke_result_t<_Func>>, T>,
            "Result of f() should be the same type as this optional");

        if (opt.has_value())
            return opt.value();
        return __f();
    }
    template<typename T>
    constexpr T or_else(std::optional<T> opt, T v) {
        if (opt.has_value())
            return opt.value();
        return v;
    }
}
#endif //EREOLENWRAPPER_HELPERFUNCTIONS_H
