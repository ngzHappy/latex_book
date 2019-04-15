
#include <QtCore/QtCore>

extern QDir & \uacf1theBookRootDir(){
    static QDir varAns=QDir::current();
    return varAns;
}
