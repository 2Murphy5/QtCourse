#include "welcomeview.h"
#include "ui_welcomeview.h"
#include <QDebug>
WelcomeView::WelcomeView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WelcomeView)
{
    qDebug() << "create WelcomeView";
    ui->setupUi(this);
}

WelcomeView::~WelcomeView()
{
    qDebug() << "destroy WelcomeView";
    delete ui;
}

void WelcomeView::on_pushButton_clicked()
{
    emit goDepartmentView();
}


void WelcomeView::on_pushButton_2_clicked()
{
    emit goDoctorView();
}


void WelcomeView::on_pushButton_3_clicked()
{
    emit goPatientView();
}

