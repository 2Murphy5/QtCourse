#include "doctorview.h"
#include <QVBoxLayout>

DoctorView::DoctorView(QWidget *parent)
    : QWidget(parent)
{
    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 创建医生信息表格部件
    doctorTableWidget = new QTableWidget(this);
    doctorTableWidget->setColumnCount(3);
    doctorTableWidget->setHorizontalHeaderLabels(QStringList() << "姓名" << "联系方式" << "所属科室");
    layout->addWidget(doctorTableWidget);

    // 创建医生姓名输入框
    doctorNameEdit = new QLineEdit(this);
    doctorNameEdit->setPlaceholderText("输入医生姓名");
    layout->addWidget(doctorNameEdit);

    // 创建医生联系方式输入框
    doctorContactEdit = new QLineEdit(this);
    doctorContactEdit->setPlaceholderText("输入医生联系方式");
    layout->addWidget(doctorContactEdit);

    // 创建所属科室下拉框
    departmentComboBox = new QComboBox(this);
    departmentComboBox->addItems(QStringList() << "内科" << "外科"); // 这里可以动态获取科室
    layout->addWidget(departmentComboBox);

    // 创建按钮并连接信号
    addDoctorButton = new QPushButton("添加医生", this);
    connect(addDoctorButton, &QPushButton::clicked, this, &DoctorView::on_addDoctorButton_clicked);
    layout->addWidget(addDoctorButton);

    deleteDoctorButton = new QPushButton("删除医生", this);
    connect(deleteDoctorButton, &QPushButton::clicked, this, &DoctorView::on_deleteDoctorButton_clicked);
    layout->addWidget(deleteDoctorButton);

    updateDoctorButton = new QPushButton("更新信息", this);
    connect(updateDoctorButton, &QPushButton::clicked, this, &DoctorView::on_updateDoctorButton_clicked);
    layout->addWidget(updateDoctorButton);

    // 连接表格项点击信号
    connect(doctorTableWidget, &QTableWidget::itemClicked, this, &DoctorView::on_doctorTableWidget_itemClicked);
    connect(departmentComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &DoctorView::on_departmentComboBox_currentIndexChanged);

    setLayout(layout);
}

DoctorView::~DoctorView()
{
}

void DoctorView::on_addDoctorButton_clicked()
{
    QString doctorName = doctorNameEdit->text().trimmed();
    QString doctorContact = doctorContactEdit->text().trimmed();
    QString department = departmentComboBox->currentText();

    if (doctorName.isEmpty() || doctorContact.isEmpty() || department.isEmpty()) {
        QMessageBox::warning(this, "警告", "所有字段都不能为空！");
        return;
    }

    // 检查是否存在相同姓名的医生
    for (const Doctor &doc : doctorList) {
        if (doc.name == doctorName && doc.department == department) {
            QMessageBox::warning(this, "警告", "该医生已存在于科室！");
            return;
        }
    }

    // 添加医生信息
    doctorList.append({doctorName, doctorContact, department});
    refreshDoctorTable();
    clearInputFields();
    QMessageBox::information(this, "成功", "医生添加成功！");
}

void DoctorView::on_deleteDoctorButton_clicked()
{
    int currentRow = doctorTableWidget->currentRow();
    if (currentRow >= 0) {
        doctorList.removeAt(currentRow);  // 从列表中移除
        refreshDoctorTable();
        clearInputFields();
        QMessageBox::information(this, "成功", "医生删除成功！");
    } else {
        QMessageBox::warning(this, "警告", "请先选择要删除的医生！");
    }
}

void DoctorView::on_updateDoctorButton_clicked()
{
    int currentRow = doctorTableWidget->currentRow();
    if (currentRow >= 0) {
        QString doctorName = doctorNameEdit->text().trimmed();
        QString doctorContact = doctorContactEdit->text().trimmed();
        QString department = departmentComboBox->currentText();

        if (doctorName.isEmpty() || doctorContact.isEmpty() || department.isEmpty()) {
            QMessageBox::warning(this, "警告", "所有字段都不能为空！");
            return;
        }

        // 更新医生信息
        doctorList[currentRow] = {doctorName, doctorContact, department};
        refreshDoctorTable();
        clearInputFields();
        QMessageBox::information(this, "成功", "医生信息更新成功！");
    } else {
        QMessageBox::warning(this, "警告", "请先选择要更新的医生！");
    }
}

void DoctorView::on_departmentComboBox_currentIndexChanged(int index)
{
    // 根据选择的科室过滤显示对应科室的医生信息
    qDebug() << "选择的科室变为: " << departmentComboBox->itemText(index);
}

void DoctorView::on_doctorTableWidget_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();
    if (row >= 0) {
        // 填充选择的医生信息到输入框
        doctorNameEdit->setText(doctorList[row].name);
        doctorContactEdit->setText(doctorList[row].contact);
        departmentComboBox->setCurrentText(doctorList[row].department);
    }
}

void DoctorView::refreshDoctorTable()
{
    doctorTableWidget->clearContents();
    doctorTableWidget->setRowCount(doctorList.size());

    for (int i = 0; i < doctorList.size(); ++i) {
        const Doctor &doc = doctorList[i];
        doctorTableWidget->setItem(i, 0, new QTableWidgetItem(doc.name));
        doctorTableWidget->setItem(i, 1, new QTableWidgetItem(doc.contact));
        doctorTableWidget->setItem(i, 2, new QTableWidgetItem(doc.department));
    }
}

void DoctorView::clearInputFields()
{
    doctorNameEdit->clear();
    doctorContactEdit->clear();
    departmentComboBox->setCurrentIndex(-1);
}
