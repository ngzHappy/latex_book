#pragma once

#include <optional>
#include "the_book_global.hpp"

class CenterWidget;
class MainWindow : public QMainWindow {
    Q_OBJECT
private:
public:
    MainWindow();
    ~MainWindow();
    void setStartDir(const QString &);
public:
    void rebuild();
private:
    std::optional<QString> thisStartDir;
private:
    Q_SIGNAL void onSetStartDir(const QString &);
    friend class CenterWidget;
};
