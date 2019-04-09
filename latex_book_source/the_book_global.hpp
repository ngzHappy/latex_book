#pragma once

#include <QtGui/QtGui>
#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>

#include <array>
#include <type_traits>
#include <exception>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <string>
#include <string_view>
#include <cassert>
#include <iostream>

using namespace std::string_literals;

#include "InputStream.hpp"

using namespace std::string_view_literals;
using namespace std::chrono_literals;

static inline const QDir & getOutPutFileDir() {
    extern QDir & \uacf1theBookRootDir();
    return \uacf1theBookRootDir();
}

static inline void setOutPutFileDir(const QDir & arg) {
    extern QDir & \uacf1theBookRootDir();
    \uacf1theBookRootDir() = arg;
}

static inline QString getOutPutFileFullPath(const QString & arg) {
    const auto & varDir = getOutPutFileDir();
    return varDir.absoluteFilePath(arg);
}

inline static void theBookThrow(
    const std::string_view & a,
    const std::string_view & b,
    const std::string_view & c,
    int d) {

    std::string varAns;
    varAns = u8R"(error*********************************************************
)"sv;
    varAns += u8R"(what : )"sv;
    varAns += a;
    varAns += u8R"(
function:)"sv;
    varAns += b;
    varAns += u8R"(
file:)"sv;
    varAns += c;
    varAns += u8R"(
line:)"sv;
    varAns += std::to_string(d);
    varAns += u8R"(
)"sv;

    std::cout << varAns << std::endl << std::flush;

    throw(-666);

}

namespace _the_book_detail {

    template<typename T>
    inline void \uacf2_print(QTextStream & o, T && arg) {
        using U = std::remove_cv_t< std::remove_reference_t<T> >;
        o << QLatin1Literal(" ");
        if constexpr (std::is_same_v<U, std::string_view >) {
            if (arg.empty()) {
                return;
            }
            o << QString::fromUtf8(arg.data(), static_cast<int>(arg.size()));
        } else {
            o << arg;
        }

    }

    template<typename ... T>
    inline void \uacf1_assert_throw(
        const std::string_view & a,
        const std::string_view & b,
        int c,
        T && ... args) {

        thread_local QByteArray varTheThrowData;

        QString varAns;
        QTextStream varStream{ &varAns };
        (\uacf2_print(varStream, args), ...);
        varTheThrowData = varAns.toLocal8Bit();

        theBookThrow({ varTheThrowData.data(),static_cast<std::size_t>(varTheThrowData.size()) },
            a, b, c);

    }

}/*_the_book_detail*/

#ifndef qsl
#define qsl QStringLiteral
#endif

#ifndef qbl
#define qbl QByteArrayLiteral
#endif

#ifndef the_book_throw
#define the_book_throw(...) ::_the_book_detail::\uacf1_assert_throw(std::string_view( __FILE__),std::string_view(__func__),__LINE__ ,__VA_ARGS__)
#endif

template<typename T>
inline static void outputHeader(T && o) {

    extern QString the_book_license();

    o << the_book_license();
    o << endl;
    o << endl;
    o << endl;

}

extern QString theBookPlainTextToTexText(const QString &);
