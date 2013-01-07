#ifndef QFRAMELISTWIDGET_H
#define QFRAMELISTWIDGET_H

#include <QListWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QStringList>
#include <magic.h>

class FrameListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit FrameListWidget(QWidget *parent = 0);
    ~FrameListWidget();
signals:
    
public slots:
    
protected:
//    void dragEnterEvent(QDragEnterEvent *event);
//    void dropEvent(QDropEvent *event);
//    void dragMoveEvent(QDragMoveEvent *event);
    bool dropMimeData(int index, const QMimeData *data, Qt::DropAction action);
    QStringList mimeTypes() const;
    Qt::DropActions supportedDropActions() const;

private:
    magic_t magicMimePredictor;
};

#endif // QFRAMELISTWIDGET_H
