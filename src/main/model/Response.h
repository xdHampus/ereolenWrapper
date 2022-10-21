#ifndef EREOLENWRAPPER_RESPONSE_H
#define EREOLENWRAPPER_RESPONSE_H

#include <vector>
#include <string>
#include <optional>
namespace ereol {
    template <typename T>
    class Response {
    private:
        bool _success{};
        std::string _message;
        std::optional<std::string> _detailedMessage;
        std::optional<T> _data;
    public:
        explicit Response(std::optional<T> data);
        explicit Response(std::optional<T> data, std::string message);
        explicit Response(std::optional<T> data, std::string message, bool state);
        explicit Response(std::optional<T> data, std::string message, bool state, std::optional<std::string> detailedMessage);
        explicit Response(std::string message);
        explicit Response(std::string message, bool state);
        explicit Response(std::string message, bool state, std::optional<std::string> detailedMessage);
        bool success() const;
        std::optional<T> data() const;
        std::string message() const;
        std::optional<std::string> detailedMessage() const;

    };

    template<typename T>
    Response<T>::Response(std::optional<T> data, std::string message, bool state, std::optional<std::string> detailedMessage) {
        Response::_data = data;
        Response::_message = message;
        Response::_success = state;
        Response::_detailedMessage = detailedMessage;
    }

    template<typename T>
    Response<T>::Response(std::optional<T> data, std::string message, bool state) : Response(data, message, state, {}) {  }
    template<typename T>
    Response<T>::Response(std::optional<T> data) : Response(data, "", true, {}) {}
    template<typename T>
    Response<T>::Response(std::optional<T> data, std::string message) : Response(data, message, true, {}) {}
    template<typename T>
    Response<T>::Response(std::string message) : Response({}, message, true, {}) {}
    template<typename T>
    Response<T>::Response(std::string message, bool state) : Response({}, message, state, {}) {}
    template<typename T>
    Response<T>::Response(std::string message, bool state, std::optional<std::string> detailedMessage) : Response({},message,state,detailedMessage) {}
    template<typename T>
    bool Response<T>::success() const {
        return Response::_success;
    }

    template<typename T>
    std::optional<T> Response<T>::data() const  {
        return Response::_data;
    }

    template<typename T>
    std::string Response<T>::message() const {
        return Response::_message;
    }
    template<typename T>
    std::optional<std::string> Response<T>::detailedMessage() const {
        return Response::_detailedMessage;
    }


}
#endif //EREOLENWRAPPER_RESPONSE_H
