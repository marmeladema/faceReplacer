#include "qframelistwidget.h"

#include <iostream>
#include <QDebug>
#include <QList>
#include <QUrl>

QFrameListWidget::QFrameListWidget(QWidget *parent) :
    QListWidget(parent)
{
}

void QFrameListWidget::dropEvent(QDropEvent *event) {
    qDebug() << "--- dropEvent ---";
    event->acceptProposedAction();
}

void QFrameListWidget::dragEnterEvent(QDragEnterEvent *event) {
    qDebug() << "--- dragEnterEvent ---";
    qDebug() << "acceptDrops: " << this->acceptDrops();
    qDebug() << "defaultDropAction: " << this->defaultDropAction();
    qDebug() << "dragDropMode: " << this->dragDropMode();
    qDebug() << "dragDropOverwriteMode: " << this->dragDropOverwriteMode();
    qDebug() << "dragEnabled: " << this->dragEnabled();

    if(event->mimeData()->hasUrls()) {
        QList<QUrl> urls = event->mimeData()->urls();
        for(unsigned int i = 0; i < urls.length(); i++) {
            qDebug() << urls[i];
        }
    }
    event->acceptProposedAction();
}
