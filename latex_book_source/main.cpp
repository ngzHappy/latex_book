#include "the_book_global.hpp"
#include "MainWindow.hpp"
#include <QtCore/QtCore>
QString globalStartUpDir;

int main(int argc, char ** argv) try {
    QApplication varApplication{ argc,argv };

    if(argc>1){
        QString varStartDir = QString::fromLocal8Bit( argv[argc-1] );
        QDir varDir{ varStartDir };
        globalStartUpDir = varDir.canonicalPath();
    }

    MainWindow varMainWindow;
    if(!globalStartUpDir.isEmpty()){
        varMainWindow.setStartDir(globalStartUpDir);
    }
    varMainWindow.show();

    return varApplication.exec();

} catch (...) {
    return -1;
}
