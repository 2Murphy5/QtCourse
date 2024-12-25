#include "MedicineView.h"
#include "ui_medicineview.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError> // 确保包含此头文件
#include <QTableWidgetItem>
#include<QStringList>
MedicineView::MedicineView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MedicineView)
{
    ui->setupUi(this);
    initDatabase(); // 初始化数据库

    // 初始化药品数据模型
    medicineModel = new QSqlTableModel(this);
    medicineModel->setTable("medicines"); // 数据表名称
    medicineModel->select(); // 加载表格数据
    refreshMedicineTable(); // 刷新表格数据
}

MedicineView::~MedicineView() {
    delete ui; // 删除 UI
}

// 初始化数据库
void MedicineView::initDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // 按需选择数据库
    db.setDatabaseName("E:/Qt_project/QTtest3/test3.db"); // 数据库名称

    if (!db.open()) { // 打开数据库
        qDebug() << "数据库打开失败:" << db.lastError().text(); // 打印错误信息
        return;
    }
    qDebug() << "数据库打开成功";

    // 检查并创建表
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS medicines ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT NOT NULL, "
               "dosage TEXT NOT NULL, "
               "stock INTEGER NOT NULL)");
}

// 添加药品
void MedicineView::on_btnAdd_clicked() {
    QString name = ui->inputMedicineName->text().trimmed();
    QString dosage = ui->inputDosage->text().trimmed();
    QString stockStr = ui->inputStock->text().trimmed();

    if (name.isEmpty() || dosage.isEmpty() || stockStr.isEmpty()) {
        QMessageBox::warning(this, "警告", "所有字段都不能为空！");
        return;
    }

    bool ok;
    int stock = stockStr.toInt(&ok); // 转换库存数量为整数
    if (!ok || stock < 0) {
        QMessageBox::warning(this, "警告", "库存数量必须是非负整数！");
        return;
    }

    // 添加药品
    QSqlQuery query;
    query.prepare("INSERT INTO medicines (name, dosage, stock) VALUES (?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(dosage);
    query.addBindValue(stock);

    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "无法添加药品！");
    } else {
        refreshMedicineTable(); // 刷新表格数据
    }
}

// 删除药品
void MedicineView::on_btnDelete_clicked() {
    int currentRow = ui->tableWidgetMedicines->currentRow(); // 获取当前选中行
    if (currentRow >= 0) {
        medicineModel->removeRow(currentRow); // 从模型中移除
        medicineModel->submitAll(); // 提交更改
        refreshMedicineTable(); // 刷新表格数据
    } else {
        QMessageBox::warning(this, "提示", "请选择要删除的药品！");
    }
}

// 查询药品
void MedicineView::on_btnQuery_clicked() {
    QString name = ui->inputMedicineName->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入药品名称进行查询！");
        return;
    }

    medicineModel->setFilter("name LIKE '%" + name + "%'"); // 设置过滤器
    medicineModel->select(); // 查询
    refreshMedicineTable(); // 刷新表格以显示查询结果
}

// 导出药品信息
void MedicineView::on_btnExport_clicked() {
    // 检查药品信息是否存在
    if (medicineModel->rowCount() == 0) {
        QMessageBox::information(this, "导出", "没有药品信息可导出。");
        return;
    }

    QStringList infoList; // 存储药品信息的列表

    for (int i = 0; i < medicineModel->rowCount(); ++i) {
        // 获取药品的信息
        QString name = medicineModel->data(medicineModel->index(i, 1)).toString(); // 药品名称
        QString dosage = medicineModel->data(medicineModel->index(i, 2)).toString(); // 剂量
        int stock = medicineModel->data(medicineModel->index(i, 3)).toInt(); // 库存数量

        // 格式化信息
        QString info = QString("药品名称: %1, 剂量: %2, 库存: %3")
                           .arg(name)
                           .arg(dosage)
                           .arg(stock);
        infoList << info; // 添加到列表
    }

    // 将所有药品信息连接为一个字符串
    QString allMedicinesInfo = infoList.join("\n");

    // 显示药品信息的弹窗
    QMessageBox::information(this, "导出药品信息", allMedicinesInfo);
}

// 刷新药品数据表
void MedicineView::refreshMedicineTable() {
    medicineModel->select(); // 刷新数据模型
    ui->tableWidgetMedicines->setRowCount(medicineModel->rowCount()); // 更新表格行数

    // 填充表格数据
    for (int i = 0; i < medicineModel->rowCount(); ++i) {
        ui->tableWidgetMedicines->setItem(i, 0, new QTableWidgetItem(medicineModel->data(medicineModel->index(i, 1)).toString())); // 药品名称
        ui->tableWidgetMedicines->setItem(i, 1, new QTableWidgetItem(medicineModel->data(medicineModel->index(i, 2)).toString())); // 剂量
        ui->tableWidgetMedicines->setItem(i, 2, new QTableWidgetItem(QString::number(medicineModel->data(medicineModel->index(i, 3)).toInt()))); // 库存数量
    }
}
