#ifndef VISITRECORDVIEW_H
#define VISITRECORDVIEW_H

#include <QWidget>
#include "ui_visitrecordview.h"
#include <QList>

// 定义一个结构体用于存储就诊记录信息
struct VisitRecord {
    int patientId;  // 假设新增患者ID字段用于排序等操作
    QString patientName;
    QString doctorName;
    QDate visitDate;
    QString diagnosis;
    QString medicine;
};

class VisitRecordView : public QWidget
{
    Q_OBJECT

public:
    explicit VisitRecordView(QWidget *parent = nullptr);

private:
    Ui::VisitRecordView ui;
    QList<VisitRecord> records;  // 存储所有就诊记录的列表

private slots:
    void on_btnAddRecord_clicked();
    void on_btnModifyRecord_clicked();
    void on_btnDeleteRecord_clicked();
    void on_btnQuery_clicked();
    void on_btnSort_clicked();
    void on_btnFilter_clicked();
    void on_btnExport_clicked();
};

#endif // VISITRECORDVIEW_H
