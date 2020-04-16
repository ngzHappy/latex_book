#include <QtCore/QtCore>
#include <vector>
#include <list>
#include <random>

namespace sstd_convert_source_file {

    namespace sstd_private {

        enum class StringType {
            None,
            Left,
            Right,
            Changed,
        };

        class TypedString {
        public:
            int start{ 0 };
            int length{ 0 };
            StringType type{ StringType::None };
            inline TypedString(int a, int b, StringType c) :
                start(a),
                length(b),
                type(c) {
            }
        };

        inline void convertSourceString(const QString& arg,
            const QString& argLeft,
            const QString& argRight,
            std::vector< TypedString >* argAns) {
            int varLeft{ 0 };
            for (;;) {
                auto varPos = arg.indexOf(argLeft, varLeft);
                if (varPos < 0) {/*将最后的部分输出...*/
                    argAns->emplace_back(varLeft, arg.size() - varLeft, StringType::None);
                    return;
                }
                auto varPosEnd = arg.indexOf(argRight, varLeft);
                if (varPos > varLeft) {/*将前面的部分输出...*/
                    argAns->emplace_back(varLeft, varPos - varLeft, StringType::None);
                }
                argAns->emplace_back(0, 0, StringType::Left);
                argAns->emplace_back(varPos + argLeft.size(), varPosEnd - varPos - argLeft.size(), StringType::Changed);
                argAns->emplace_back(0, 0, StringType::Right);
                varLeft = varPosEnd + argRight.size();
            }

        }

        inline QString replaceQStringRef(const QStringRef& arg, const QString& l, const QString& r) {
            QRegularExpression const static varRegex{ QStringLiteral(R"(-)") };
            QString varAns = arg.toString();
            varAns.replace(varRegex, l + QStringLiteral(R"(\hspace{0.05em}\rule[0.52ex]{0.5em}{0.48pt}\hspace{0.05em})") + r);
            return std::move(varAns);
        }

    }/**/

    QString __convertSourceString(const QString& arg,
        const QString& argLeft,
        const QString& argRight) {

        if (arg.isEmpty()) {
            return {};
        }

        std::vector< sstd_private::TypedString > data;
        sstd_private::convertSourceString(arg, argLeft, argRight, &data);

        {
            QString ans;
            for (const auto& varI : data) {
                if (varI.type == sstd_private::StringType::None) {
                    ans += sstd_private::replaceQStringRef(QStringRef(&arg, varI.start, varI.length),
                        argLeft, argRight);
                } else if (varI.type == sstd_private::StringType::Changed) {
                    ans += QStringRef(&arg, varI.start, varI.length);
                } else if (varI.type == sstd_private::StringType::Left) {
                    ans += argLeft;
                } else if (varI.type == sstd_private::StringType::Right) {
                    ans += argRight;
                }
            }
            return std::move(ans);
        }

    }

    class RandomPack {
    public:
        QString gen() {
            return QString::number(mdis(mgen));
        }
        RandomPack() {
            mdis = std::uniform_int_distribution<int>(12, 99);
        }
        std::mt19937 mgen{ std::default_random_engine{}() };
        std::uniform_int_distribution<int> mdis;
    };

    QString convertSourceString(const QString& arg_,
        const QString& argLeft,
        const QString& argRight) {
        thread_local RandomPack varRandom;
        QString arg = arg_;
        {/*将 //@'^^^^^'@ 替换为 (*@\space*{\fill}@*)// */
            const QString r1 = QStringLiteral(R"===(//@'^^^^^'@)===");
            if (arg.indexOf(r1) > -1) {
                const QString r2 = argLeft + QStringLiteral(R"===(\ \zzDotfill{})===") +
                    QStringLiteral(R"==(\resizebox{1ex}{1ex}{\textcolor[RGB]{%1,%2,%3}{/}\textcolor[RGB]{%4,%5,%6}{/}})==")
                    .arg(varRandom.gen(), varRandom.gen(), varRandom.gen(), varRandom.gen(), varRandom.gen(), varRandom.gen())
                    + argRight;
                arg.replace(r1, r2);
            }
        }
        return __convertSourceString(arg, argLeft, argRight);
    }

}/**/
// 把他缩小到一行可以看的见的程度，就是不会超出去。
// \resizebox{1\linewidth}{!}{}
