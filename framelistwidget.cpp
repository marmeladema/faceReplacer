#include "framelistwidget.h"

#include <iostream>
#include <QDebug>
#include <QList>
#include <QUrl>
#include <QFileInfo>
#include <QDir>

FrameListWidget::FrameListWidget(QWidget *parent) :
    QListWidget(parent)
{
    this->setDragEnabled(true);
    this->setAcceptDrops(true);
    this->setDropIndicatorShown(true);
    this->setDefaultDropAction(Qt::MoveAction);

    this->magicMimePredictor = magic_open(MAGIC_MIME_TYPE); // Open predictor
    if (!this->magicMimePredictor) {
        qDebug() << "libmagic: Unable to initialize magic library";
    } else if (magic_load(magicMimePredictor, 0)) { // if not 0 - error
        qDebug() << "libmagic: Can't load magic database - " + QString(magic_error(magicMimePredictor));
        magic_close(magicMimePredictor); // Close predictor
    }
}

FrameListWidget::~FrameListWidget() {
    qDebug() << "~FrameListWidget";
    magic_close(this->magicMimePredictor); // Close predictor
}

//void QFrameListWidget::dropEvent(QDropEvent *event) {
//    qDebug() << "--- dropEvent ---";
//    qDebug() << "proposedAction: " << event->proposedAction();
//    if(event && event->mimeData()->hasUrls() && event->proposedAction() & Qt::CopyAction) {
//        qDebug() << "Qt::CopyAction";
//        event->acceptProposedAction();
//        for(int i = 0; i < event->mimeData()->urls().length(); i++) {
//            qDebug() << event->mimeData()->urls()[i].toLocalFile();
//            this->insertItem(this->dropIndicatorPosition(), event->mimeData()->urls()[i].toLocalFile());
//        }
//    }
//    else {
//        QListWidget::dropEvent(event);
//    }
//}

//void QFrameListWidget::dragEnterEvent(QDragEnterEvent *event) {
//    qDebug() << "--- dragEnterEvent ---";
//    qDebug() << "proposedAction: " << event->proposedAction();
//    qDebug() << "acceptDrops: " << this->acceptDrops();
//    qDebug() << "defaultDropAction: " << this->defaultDropAction();
//    qDebug() << "dragDropMode: " << this->dragDropMode();
//    qDebug() << "dragDropOverwriteMode: " << this->dragDropOverwriteMode();
//    qDebug() << "dragEnabled: " << this->dragEnabled();
//    qDebug() << "topLevelItemCount: " << this->count();
//    qDebug() << event->mimeData()->formats();

//    if(event && event->mimeData()->hasUrls()) {
//        event->acceptProposedAction();
//    } else {
//        QListWidget::dragEnterEvent(event);
//    }
//    qDebug() << "dropIndicatorPosition: " << this->dropIndicatorPosition();
//    qDebug() << "showDropIndicator:" << this->showDropIndicator();
//    //QListWidget::dragEnterEvent(event);
//    //event->acceptProposedAction();
//}

//void QFrameListWidget::dragMoveEvent(QDragMoveEvent *event) {
//    qDebug() << "--- dragMoveEvent ---";
//    qDebug() << "dropIndicatorPosition: " << this->dropIndicatorPosition();
//    qDebug() << "proposedAction: " << event->proposedAction();
//    qDebug() << "showDropIndicator" << this->showDropIndicator();

//    if(event && event->mimeData()->hasUrls()) {
//        event->acceptProposedAction();
//    } else {
//        QListWidget::dragMoveEvent(event);
//    }
//}

bool FrameListWidget::dropMimeData(int index, const QMimeData *data, Qt::DropAction action) {
    qDebug() << "dropMimeData";
    const char * mime = NULL;
    if (data && data->hasUrls()) {
        foreach (const QUrl& url, data->urls()) {
            mime = magic_file(this->magicMimePredictor, url.toLocalFile().toLocal8Bit().constData());
            qDebug() << mime;
            if(mime) {
                QString result = QString(mime);
                qDebug() << result;
                if(result == "inode/directory") {
                    QDir dir(url.toLocalFile());
                    dir.setFilter(QDir::Files|QDir::Readable);
                    foreach(const QString& file, dir.entryList()) {
                        mime = magic_file(this->magicMimePredictor, dir.absoluteFilePath(file).toLocal8Bit().constData());
                        if(mime) {
                            result = QString(mime);
                            if(result.startsWith("image/") || result.startsWith("video/")) {
                                insertItem(index++, dir.absoluteFilePath(file));
                            }
                        }
                    }
                } else if(result.startsWith("image/") || result.startsWith("video/")) {
                    insertItem(index++, url.toLocalFile());
                }
            }
        }
        return true;
    }
    else
        return QListWidget::dropMimeData(index, data, action);
}

QStringList FrameListWidget::mimeTypes() const {
    QStringList qstrList = QListWidget::mimeTypes();
    qstrList << QLatin1String("text/uri-list");
    return qstrList;
}

Qt::DropActions FrameListWidget::supportedDropActions() const {
    return Qt::CopyAction | Qt::MoveAction | Qt::LinkAction;
}
