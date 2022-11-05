#ifndef USERONLINE_H
#define USERONLINE_H

#include <QWidget>
#include <QListWidget>
#include <QMouseEvent>
#include <QAction>

namespace Ui {
class UserOnline;
}

class UserOnline : public QWidget
{
    Q_OBJECT

public:
    explicit UserOnline(QWidget *parent = nullptr);
    explicit UserOnline(QObject *controller);
    QListWidget *getListWidget();
    void Initialise();
    ~UserOnline();

protected:
    QPoint mousePoint;
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::UserOnline *ui;
    QTimer *timer;
    bool mouseOff;

};

#endif // USERONLINE_H
