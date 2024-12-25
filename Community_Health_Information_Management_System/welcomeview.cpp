#include "welcomeview.h"
#include "ui_welcomeview.h"
#include <QDebug>
#include <QStackedWidget>
#include "departmentview.h"
#include "doctorview.h"
#include "patientview.h"
#include "medicinerview.h"
#include "visitrecordview.h"
WelcomeView::WelcomeView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WelcomeView)
    , stackedWidget(new QStackedWidget(this))
{
    qDebug() << "create WelcomeView";
    ui->setupUi(this);


    ui->verticalLayout->addWidget(stackedWidget);
}

WelcomeView::~WelcomeView()
{
    qDebug() << "destroy WelcomeView";
    delete ui;
}



void WelcomeView::on_btnDepartmentManagement_clicked()
{
    DepartmentView *departmentView = new DepartmentView(); // 创建科室管理界面实例
    // 将科室管理界面添加到QStackedWidget中
    stackedWidget->addWidget(departmentView);
    // 设置科室管理界面为当前显示的界面
    stackedWidget->setCurrentWidget(departmentView);

}


void WelcomeView::on_btnDoctorManagement_clicked()
{
    DoctorView *doctorView = new DoctorView(); // 创建医生管理界面实例
    // 将医生管理界面添加到QStackedWidget中
    stackedWidget->addWidget(doctorView);
    // 设置医生管理界面为当前显示的界面
    stackedWidget->setCurrentWidget(doctorView);
}


void WelcomeView::on_btnPatientManagement_clicked()
{
    PatientView *patientView = new PatientView(); // 创建病人管理界面实例
    stackedWidget->addWidget(patientView); // 添加到QStackedWidget中
    stackedWidget->setCurrentWidget(patientView); // 设置当前显示的界面
}


void WelcomeView::on_btnMedicineManagement_clicked()
{

}


void WelcomeView::on_btnVisitRecordManagement_clicked()
{

}

