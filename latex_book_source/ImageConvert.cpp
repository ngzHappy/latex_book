#include "ImageConvert.hpp"


bool ImageConvert::needConvert() const {

    if (input_image_full_path.endsWith(
        QStringLiteral(".pdf"),
        Qt::CaseInsensitive)) {
        return false;
    }

    if (input_image_full_path.endsWith(
        QStringLiteral(".eps"),
        Qt::CaseInsensitive)) {
        return false;
    }

    return true;
}

inline static void clipImage(
    QImage * arg1) {

    if (arg1->width() < 0) {
        return;
    }

    if (arg1->height() < 0) {
        return;
    }

    const auto varTmp =
        arg1->convertToFormat(QImage::Format_RGBA8888);

    *arg1 =
        varTmp.copy(1, 1,
            std::max(1, varTmp.width() - 2),
            std::max(1, varTmp.height() - 2));

}

extern std::atomic< std::size_t > & countConvertImageToPdf() {
    static std::atomic< std::size_t > varAns{ 0 };
    return varAns;
}

/*将图片转为pdf*/
/*#include <QtGui/QtGui>*/
static inline bool convert_image_to_pdf(
    const QImage & argImage,
    const QString argPdfFileName) {

    const auto varImage = argImage;

    if (varImage.height() < 1) {
        return false;
    }

    if (varImage.width() < 1) {
        return false;
    }

    /*打开写文件*/
    QFile varPDFFile{ argPdfFileName };
    if (false == varPDFFile.open(QIODevice::WriteOnly)) {
        return false;
    }

    QPdfWriter varWriter{ &varPDFFile };

    {
        varWriter.setMargins({ 0,0,0,0 });
        varWriter.setResolution(72);
        varWriter.setPageSize(QPageSize(
            QSize{ varImage.width(),varImage.height() },
            QPageSize::Point));
    }

    QPainter varPainter{ &varWriter };
    varPainter.setRenderHints(QPainter::NonCosmeticDefaultPen |
        QPainter::Antialiasing |
        QPainter::TextAntialiasing |
        QPainter::SmoothPixmapTransform |
        QPainter::HighQualityAntialiasing |
        QPainter::LosslessImageRendering);

    varPainter.drawImage(0, 0, varImage);

    return true;

}

namespace {
    class Run : public QRunnable {
        const QImage inputImage;
        const QString outputImagePath;
        volatile bool isDestory{ false };
    public:
        inline Run(const QImage & a, const QString & b) :
            inputImage(a),
            outputImagePath(b) {
            ++countConvertImageToPdf();
        }
        inline void run() override {
            convert_image_to_pdf(inputImage, outputImagePath);
            destory();
        }
        inline void destory() {
            if (isDestory) {
                return;
            }
            isDestory = true;
            --countConvertImageToPdf();
        }
        inline ~Run() {
            destory();
        }
    };
}/**/

bool ImageConvert::convert() {

    {
        /*打开输入图片*/
        QImage varImage{
            input_image_full_path
        };
        if (varImage.isNull()) {
            return false;
        }
        {
            output_image_relative_path =
                qsl("the_book_image/") +
                image_index +
                qsl(".bmp");
            output_image_full_path =
                getOutPutFileFullPath(
                    output_image_relative_path);
            input_image_full_path = output_image_full_path;
        }
        /*处理图片并保存*/
        clipImage(&varImage);
        varImage.save(output_image_full_path);
    }

    {
        output_image_relative_path =
            qsl("the_book_image/") +
            image_index +
            qsl(".pdf");
        output_image_full_path =
            getOutPutFileFullPath(
                output_image_relative_path);
    }

    /*将图片转为pdf*/
    QThreadPool::globalInstance()->start(
        new Run{ QImage(input_image_full_path), output_image_full_path });

    return true;

}
