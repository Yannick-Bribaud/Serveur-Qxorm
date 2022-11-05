#include "UserOnline.h"
#include "ui_UserOnline.h"
#include <QTimer>


UserOnline::UserOnline(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserOnline)
{
    ui->setupUi(this);

}

UserOnline::UserOnline(QObject *controller):
    ui(new Ui::UserOnline)
{
    ui->setupUi(this);
    Initialise();

    timer=new QTimer();
    connect(ui->Update_Button,SIGNAL(clicked()),controller,SLOT(actualise()));
    connect(ui->minimized_Button,SIGNAL(clicked()),controller,SLOT(minimized()));
    connect(ui->Close_Button,SIGNAL(clicked()),controller,SLOT(closeOnlineUi()));
    connect(timer,SIGNAL(timeout()),controller,SLOT(actualise()));
    timer->start(300);

}

QListWidget *UserOnline::getListWidget(){
    return ui->listWidget;
}

void UserOnline::Initialise(){
    this->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    ui->Update_Button->setIcon(QIcon(":/icon/update_left_rotation_96px.png"));
    ui->Close_Button->setIcon(QIcon(":/icon/close_window48_48px.png"));
    ui->minimized_Button->setIcon(QIcon(":/icon/minimize_window_48px.png"));
}

UserOnline::~UserOnline(){
    delete ui;
}

void UserOnline::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton) {
        mouseOff=true;
   }
}

void UserOnline::mouseReleaseEvent(QMouseEvent *event){
    if(event->Close){
        mouseOff=false;
    }
}

void UserOnline::mouseMoveEvent(QMouseEvent *event){
    mousePoint=event->globalPos();
    move(mousePoint);
}
