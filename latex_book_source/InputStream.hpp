#pragma once

#include <QtCore/qtextstream.h>
#include <QtCore/qtextcodec.h>

class InputStream :
        public QTextStream{
public:

    inline InputStream(){
    }

    template<typename A0,typename ... Args>
    inline InputStream(A0&&a0,Args && ... args):
        QTextStream (std::forward<A0>(a0),std::forward<Args>(args)...){
#if defined (Q_OS_WIN)
        /*在Windows平台下强制使用UTF8编码读取*/
        auto varCodec = QTextCodec::codecForName(
                    QByteArrayLiteral("UTF-8"));
        if(this->codec()!=varCodec){
            this->setCodec(varCodec);
        }
#endif
    }

    InputStream(const InputStream&)=delete ;
    InputStream(InputStream&&)=delete;
    InputStream&operator=(const InputStream&)=delete ;
    InputStream&operator=(InputStream&&)=delete;

};
