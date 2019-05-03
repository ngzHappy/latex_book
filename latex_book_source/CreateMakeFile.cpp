#include "CreateMakeFile.hpp"
#include "OutPutStream.hpp"
#include "InputStream.hpp"
#include <set>
#include <list>
#include <vector>

namespace this_file {

    class CreateMakeFileState {
    public:

        class Duty {
        public:
            QString filePath;
        };

        class Ans {
        public:
            QFileInfo data;

            inline Ans(QFileInfo v)
                :data(std::move(v)) {
            }

        };

        using DutysType = std::list< std::shared_ptr< Duty > >;
        DutysType dutys;
        std::list< Ans > ans;
        std::set< QString > insert;

        inline static std::shared_ptr<Duty> createADuty(const QString & arg) {
            auto varAns = std::make_shared<Duty>();
            {
                const auto varOutPutDir = getOutPutFileDir();
                const auto varRootPath =
                    varOutPutDir.absoluteFilePath(arg);
                varAns->filePath = varRootPath;
            }
            return std::move(varAns);
        }

    };
}/*namespace this_fiel*/

class CreateMakeFilePrivate {
public:

    std::shared_ptr< const CreateMakeFileConstruct > args;

    inline CreateMakeFilePrivate(std::shared_ptr< const CreateMakeFileConstruct > && v) :
        args(std::move(v)) {
    }

    inline bool createMakeFile(this_file::CreateMakeFileState * arg) {

        {
            arg->dutys.push_front(
                this_file::CreateMakeFileState::createADuty(args->rootFileName));
        }

        while (arg->dutys.empty() == false) {
            auto varDuty = std::move(arg->dutys.front());
            arg->dutys.pop_front();

            QFileInfo varInfo{ varDuty->filePath };
            {
                if (varInfo.exists() == false) {/*忽略不存在的file...*/
                    continue;
                }
                if (varInfo.isFile() == false) {/*忽略文件夹...*/
                    continue;
                }
                if (!(varInfo.suffix().toLower() == QStringLiteral("txt"))) {/*只编译txt...*/
                    continue;
                }
                arg->ans.emplace_back(std::move(varInfo));
            }

            QFile varReadFile{ varInfo.absoluteFilePath() };
            if (false == varReadFile.open(QIODevice::ReadOnly)) {
                continue;
            }

            this_file::CreateMakeFileState::DutysType varThisFileDutys;

            {/*寻找符合\input{???} 的语句*/
                InputStream varStream{ &varReadFile };
                const static QRegularExpression varR_{ QStringLiteral(
                    R"(^(?::tex_raw:\[[=]*\[)?\s*\\input\s*\{([^}]+)\}.*)") };

                /*寻找符合 %the_book_insert{???} 的语句*/
                const static QRegularExpression varR_Insert{ QStringLiteral(
                    R"(^(?::tex_raw:\[[=]*\[)?\s*%the_book_insert\s*\{([^}]+)\}.*)") };

                const auto & varR = varR_;

                while (false == varStream.atEnd()) {
                    const auto varLine =
                        varStream.readLine().trimmed();
                    if (varLine.size() < 6/*\input*/) {
                        continue;
                    }

                    {
                        const auto varMatched =
                            varR.match(varLine);
                        if (varMatched.hasMatch()) {
                            auto varFile = varMatched.captured(1).trimmed();
                            if (varFile.endsWith(QStringLiteral(".tex"), Qt::CaseInsensitive)) {
                                varFile.chop(2);
                                varFile += QStringLiteral("xt");
                                varThisFileDutys.push_back(
                                    this_file::CreateMakeFileState::createADuty(varFile)
                                );
                            }
                            continue;
                        }
                    }

                    {
                        const auto varMatched =
                            varR_Insert.match(varLine);
                        if (varMatched.hasMatch()) {
                            const auto varInsert = varMatched.captured(1).trimmed();
                            arg->insert.insert(varInsert);
                        }
                    }

                }
            }

            arg->dutys.splice(
                arg->dutys.cbegin(),
                std::move(varThisFileDutys));

        }

        {
            QFile varFile{ getOutPutFileFullPath(
                QStringLiteral("MakeFile.txt"))
            };

            if (false == varFile.open(QIODevice::WriteOnly)) {
                return false;
            }

            OutPutFileStream varOutPut{ &varFile };

            for (const auto & varAns : arg->ans) {
                varOutPut <<
                    getOutPutFileDir().relativeFilePath(
                        varAns.data.canonicalFilePath());
                varOutPut << endl;
            }
        }

        do {

            std::list<QString> varLines;
            std::set<QString> varInsertLines;
            {
                QFile varFile{ getOutPutFileFullPath(
                    QStringLiteral("the_book_constexpr.txt"))
                };

                if (false == varFile.open(QIODevice::ReadOnly)) {
                    return false;
                }

                InputStream varRead{ &varFile };
                while (varRead.atEnd() == false) {
                    auto varLine = varRead.readLine().trimmed();
                    if (varLine == QStringLiteral("####start_insert####")) {
                        break;
                    }
                    varLines.push_back(varLine);
                }
                while (varRead.atEnd() == false) {
                    auto varLine = varRead.readLine().trimmed();
                    varInsertLines.insert(varLine);
                }
            }

            arg->insert.erase(QString{});
            varInsertLines.erase(QString{});

            {
                if (arg->insert == varInsertLines) {
                    break;
                }
            }

            {
                QFile varFile{ getOutPutFileFullPath(
                   QStringLiteral("the_book_constexpr.txt"))
                };

                if (false == varFile.open(QIODevice::WriteOnly)) {
                    return false;
                }

                QTextStream varOut{ &varFile };
                varOut.setCodec( QTextCodec::codecForName("UTF-8") );
                varOut.setGenerateByteOrderMark(true);

                while (!varLines.empty()) {
                    if (varLines.back().isEmpty()) {
                        varLines.pop_back();
                    } else {
                        break;
                    }
                }

                for (const auto & varI : varLines) {
                    varOut << varI << endl;
                }

                varOut << endl << QStringLiteral("####start_insert####") << endl;

                for (const auto & varI : arg->insert) {
                    varOut << varI << endl;
                }

            }

        } while (false);

        return true;
    }

};

CreateMakeFile::CreateMakeFile(std::shared_ptr<const CreateMakeFileConstruct> arg)
    :thisp(std::make_shared<CreateMakeFilePrivate>(std::move(arg))) {

}

bool CreateMakeFile::createMakeFile() {

    if (!(thisp && (thisp->args) && (thisp->args->rootFileName.isEmpty() == false))) {
        return false;
    }

    auto varState = std::make_shared<this_file::CreateMakeFileState>();
    const auto varAns = thisp->createMakeFile(varState.get());
    return varAns;
}
