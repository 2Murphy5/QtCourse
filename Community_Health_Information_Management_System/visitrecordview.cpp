#include "visitrecordview.h"
#include <QMessageBox>
#include <QDate>
#include <algorithm>

VisitRecordView::VisitRecordView(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    // 连接各个按钮的点击信号到对应的槽函数
    connect(ui.btnAddRecord, &QPushButton::clicked, this, &VisitRecordView::on_btnAddRecord_clicked);
    connect(ui.btnModifyRecord, &QPushButton::clicked, this, &VisitRecordView::on_btnModifyRecord_clicked);
    connect(ui.btnDeleteRecord, &QPushButton::clicked, this, &VisitRecordView::on_btnDeleteRecord_clicked);
    connect(ui.btnQuery, &QPushButton::clicked, this, &VisitRecordView::on_btnQuery_clicked);
    connect(ui.btnSort, &QPushButton::clicked, this, &VisitRecordView::on_btnSort_clicked);
    connect(ui.btnFilter, &QPushButton::clicked, this, &VisitRecordView::on_btnFilter_clicked);
    connect(ui.btnExport, &QPushButton::clicked, this, &VisitRecordView::on_btnExport_clicked);
}

// 添加记录按钮点击槽函数实现
void VisitRecordView::on_btnAddRecord_clicked()
{
    QString patientName = ui.editPatientName->text();
    QString doctorName = ui.editDoctorName->text();
    QDate visitDate = ui.editVisitDate->date();
    QString diagnosis = ui.editDiagnosis->toPlainText();
    QString medicine = ui.editMedicine->toPlainText();

    // 简单验证输入是否为空（实际可更严格验证）
    if (patientName.isEmpty() || doctorName.isEmpty() || diagnosis.isEmpty() || medicine.isEmpty())
    {
        QMessageBox::warning(this, "提示", "请填写完整信息");
        return;
    }

    // 检查是否存在相同记录
    VisitRecord newRecord;
    newRecord.patientId = 0; // 这里先设置为0，因为还不确定是否添加
    newRecord.patientName = patientName;
    newRecord.doctorName = doctorName;
    newRecord.visitDate = visitDate;
    newRecord.diagnosis = diagnosis;
    newRecord.medicine = medicine;

    bool recordExists = false;
    for (const VisitRecord& record : records)
    {
        if (record.patientName == patientName &&
            record.doctorName == doctorName &&
            record.visitDate == visitDate &&
            record.diagnosis == diagnosis &&
            record.medicine == medicine)
        {
            recordExists = true;
            break;
        }
    }

    if (recordExists)
    {
        QMessageBox::warning(this, "提示", "该记录已存在，不能添加");
        return;
    }

    static int currentPatientId = 1;
    newRecord.patientId = currentPatientId++;
    records.append(newRecord);

    int row = ui.tableWidgetRecords->rowCount();
    ui.tableWidgetRecords->insertRow(row);
    ui.tableWidgetRecords->setItem(row, 0, new QTableWidgetItem(patientName));
    ui.tableWidgetRecords->setItem(row, 1, new QTableWidgetItem(doctorName));
    ui.tableWidgetRecords->setItem(row, 2, new QTableWidgetItem(visitDate.toString("yyyy - MM - dd")));
    ui.tableWidgetRecords->setItem(row, 3, new QTableWidgetItem(diagnosis));
    ui.tableWidgetRecords->setItem(row, 4, new QTableWidgetItem(medicine));
}

// 修改记录按钮点击槽函数实现
void VisitRecordView::on_btnModifyRecord_clicked()
{
    int selectedRow = ui.tableWidgetRecords->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "提示", "请先选中要修改的记录");
        return;
    }

    QString newPatientName = ui.editPatientName->text();
    QString newDoctorName = ui.editDoctorName->text();
    QDate newVisitDate = ui.editVisitDate->date();
    QString newDiagnosis = ui.editDiagnosis->toPlainText();
    QString newMedicine = ui.editMedicine->toPlainText();

    if (newPatientName.isEmpty() || newDoctorName.isEmpty() || newDiagnosis.isEmpty() || newMedicine.isEmpty()) {
        QMessageBox::warning(this, "提示", "请填写完整修改信息");
        return;
    }

    // 更新对应记录信息
    records[selectedRow].patientName = newPatientName;
    records[selectedRow].doctorName = newDoctorName;
    records[selectedRow].visitDate = newVisitDate;
    records[selectedRow].diagnosis = newDiagnosis;
    records[selectedRow].medicine = newMedicine;

    // 更新表格显示
    ui.tableWidgetRecords->setItem(selectedRow, 0, new QTableWidgetItem(newPatientName));
    ui.tableWidgetRecords->setItem(selectedRow, 1, new QTableWidgetItem(newDoctorName));
    ui.tableWidgetRecords->setItem(selectedRow, 2, new QTableWidgetItem(newVisitDate.toString("yyyy-MM-dd")));
    ui.tableWidgetRecords->setItem(selectedRow, 3, new QTableWidgetItem(newDiagnosis));
    ui.tableWidgetRecords->setItem(selectedRow, 4, new QTableWidgetItem(newMedicine));
}

// 删除记录按钮点击槽函数实现
void VisitRecordView::on_btnDeleteRecord_clicked()
{
    int selectedRow = ui.tableWidgetRecords->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "提示", "请先选中要删除的记录");
        return;
    }

    // 从数据列表中删除记录
    records.removeAt(selectedRow);

    // 从表格中删除对应行
    ui.tableWidgetRecords->removeRow(selectedRow);
}

// 查询按钮点击槽函数实现（按照患者名字查询）
void VisitRecordView::on_btnQuery_clicked()
{
    QString queryName = ui.editPatientName->text();
    ui.tableWidgetRecords->setRowCount(0);  // 先清空表格

    for (const VisitRecord &record : records) {
        if (record.patientName.contains(queryName, Qt::CaseInsensitive)) {
            int row = ui.tableWidgetRecords->rowCount();
            ui.tableWidgetRecords->insertRow(row);
            ui.tableWidgetRecords->setItem(row, 0, new QTableWidgetItem(record.patientName));
            ui.tableWidgetRecords->setItem(row, 1, new QTableWidgetItem(record.doctorName));
            ui.tableWidgetRecords->setItem(row, 2, new QTableWidgetItem(record.visitDate.toString("yyyy-MM-dd")));
            ui.tableWidgetRecords->setItem(row, 3, new QTableWidgetItem(record.diagnosis));
            ui.tableWidgetRecords->setItem(row, 4, new QTableWidgetItem(record.medicine));
        }
    }
}

// 排序按钮点击槽函数实现（按照患者的ID排序）
void VisitRecordView::on_btnSort_clicked()
{
    std::sort(records.begin(), records.end(), [](const VisitRecord &a, const VisitRecord &b) {
        return a.patientId < b.patientId;
    });

    // 重新刷新表格显示
    ui.tableWidgetRecords->setRowCount(0);
    for (const VisitRecord &record : records) {
        int row = ui.tableWidgetRecords->rowCount();
        ui.tableWidgetRecords->insertRow(row);
        ui.tableWidgetRecords->setItem(row, 0, new QTableWidgetItem(record.patientName));
        ui.tableWidgetRecords->setItem(row, 1, new QTableWidgetItem(record.doctorName));
        ui.tableWidgetRecords->setItem(row, 2, new QTableWidgetItem(record.visitDate.toString("yyyy-MM-dd")));
        ui.tableWidgetRecords->setItem(row, 3, new QTableWidgetItem(record.diagnosis));
        ui.tableWidgetRecords->setItem(row, 4, new QTableWidgetItem(record.medicine));
    }
}

// 过滤按钮点击槽函数实现（按照诊断结果过滤）
void VisitRecordView::on_btnFilter_clicked()
{
    QString filterDiagnosis = ui.editDiagnosis->toPlainText();
    ui.tableWidgetRecords->setRowCount(0);

    for (const VisitRecord &record : records) {
        if (record.diagnosis.contains(filterDiagnosis, Qt::CaseInsensitive)) {
            int row = ui.tableWidgetRecords->rowCount();
            ui.tableWidgetRecords->insertRow(row);
            ui.tableWidgetRecords->setItem(row, 0, new QTableWidgetItem(record.patientName));
            ui.tableWidgetRecords->setItem(row, 1, new QTableWidgetItem(record.doctorName));
            ui.tableWidgetRecords->setItem(row, 2, new QTableWidgetItem(record.visitDate.toString("yyyy-MM-dd")));
            ui.tableWidgetRecords->setItem(row, 3, new QTableWidgetItem(record.diagnosis));
            ui.tableWidgetRecords->setItem(row, 4, new QTableWidgetItem(record.medicine));
        }
    }
}

// 导出按钮点击槽函数实现（弹窗打印出所有记录，实际可导出为文件等更实用方式）
void VisitRecordView::on_btnExport_clicked()
{
    QString allRecords;
    for (const VisitRecord &record : records) {
        allRecords += QString("患者ID: %1, 患者姓名: %2, 医生姓名: %3, 就诊日期: %4, 诊断结果: %5, 开具药品: %6\n")
                          .arg(record.patientId)
                          .arg(record.patientName)
                          .arg(record.doctorName)
                          .arg(record.visitDate.toString("yyyy-MM-dd"))
                          .arg(record.diagnosis)
                          .arg(record.medicine);
    }
    QMessageBox::information(this, "导出记录", allRecords);
}
