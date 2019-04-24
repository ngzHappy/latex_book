#include "MainWindow.hpp"
#include "output_main_index.hpp"

class CenterWidget :
    public QWidget {
    MainWindow * const super;
    QPushButton * button;
    QLineEdit * text;
public:
    inline CenterWidget(MainWindow * arg) :
        super(arg) {
        auto varButton = new QPushButton;
        button = varButton;
        auto varLayout = new QVBoxLayout;
        this->setLayout(varLayout);
        varButton->setMinimumHeight(64);
        {
            varLayout->addSpacerItem(new QSpacerItem(1, 0,
                QSizePolicy::Minimum, QSizePolicy::Expanding));
        }
        {
            auto varHLayout = new QHBoxLayout;
            auto varTextInput = new QLineEdit;
            varHLayout->addWidget(varTextInput);
            auto varSelectFileButton = new QPushButton;
            varHLayout->addWidget(varSelectFileButton);
            varSelectFileButton->setText(trUtf8(u8R"(选择目录)"));
            QObject::connect(varSelectFileButton, &QPushButton::clicked,
                varSelectFileButton, [this]() {
                auto varAns = QFileDialog::getExistingDirectory(nullptr,
                    trUtf8(u8"选择包含 main_index.txt 和 the_book_constexpr.txt 的目录"),
                    this->text->text());
                if (varAns.isEmpty()) {
                    return;
                }
                this->text->setText(varAns);
            });
            varLayout->addLayout(varHLayout);
            const auto varStarupFile = []() {
                QDir varDir{ qApp->applicationDirPath() };
                return varDir.absoluteFilePath("app_startup/path.txt");
            }();
            if (QFileInfo::exists(varStarupFile)) {
                QFile varFile{ varStarupFile };
                varFile.open(QIODevice::ReadOnly);
                QTextStream varStream{ &varFile };
                varTextInput->setText(varStream.readAll().trimmed());
            } else {
                qWarning() << "can not find : " << varStarupFile;
                varTextInput->setText(QDir::currentPath());
            }
            text = varTextInput;
        }
        {
            auto varHLayout = new QHBoxLayout;
            varHLayout->addWidget(varButton);
            varLayout->addLayout(varHLayout);
        }
        {
            varLayout->addSpacerItem(new QSpacerItem(1, 0,
                QSizePolicy::Minimum, QSizePolicy::Expanding));
        }
        connect(
            varButton, &QPushButton::clicked,
            this, [this]() {rebuild(); });
        varButton->setText(trUtf8(u8R"(重新构建)"));
    }

    inline void rebuild() {
        button->setEnabled(false);
        _rebuild();
        button->setEnabled(true);
    }

    inline void _rebuild() try {

        output_main_index(text->text());

    } catch (...) {

    }

};

void MainWindow::rebuild() {
    static_cast<CenterWidget *>(
        this->centralWidget())
        ->rebuild();
}

MainWindow::MainWindow() {
    this->setMinimumSize({ 512,512 });
    this->setCentralWidget(new CenterWidget{ this });
}

MainWindow::~MainWindow() {

}
