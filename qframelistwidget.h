#ifndef QFRAMELISTWIDGET_H
#define QFRAMELISTWIDGET_H

#include <QListWidget>
#include <QDragEnterEvent>
#include <QDropEvent>

class QFrameListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit QFrameListWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
};

#endif // QFRAMELISTWIDGET_H
