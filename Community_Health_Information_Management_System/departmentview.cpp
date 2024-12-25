#include "departmentview.h"
#include <QVBoxLayout>
#include <QDebug>

DepartmentView::DepartmentView(QWidget *parent)
    : QWidget(parent)
{
    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 创建科室列表部件
    departmentListWidget = new QListWidget(this);
    layout->addWidget(departmentListWidget);

    // 创建科室名称输入框
    departmentNameEdit = new QLineEdit(this);
    departmentNameEdit->setPlaceholderText("请输入科室名称");
    layout->addWidget(departmentNameEdit);

    // 创建添加科室按钮
    addDepartmentButton = new QPushButton("添加科室", this);
    connect(addDepartmentButton, &QPushButton::clicked, this, &DepartmentView::on_addDepartmentButton_clicked);
    layout->addWidget(addDepartmentButton);

    // 创建删除科室按钮
    deleteDepartmentButton = new QPushButton("删除科室", this);
    connect(deleteDepartmentButton, &QPushButton::clicked, this, &DepartmentView::on_deleteDepartmentButton_clicked);
    layout->addWidget(deleteDepartmentButton);

    // 连接列表项点击信号
    connect(departmentListWidget, &QListWidget::itemClicked, this, &DepartmentView::on_departmentListWidget_itemClicked);
    connect(departmentListWidget, &QListWidget::itemDoubleClicked, this, &DepartmentView::on_departmentListWidget_itemDoubleClicked);

    setLayout(layout);
    refreshDepartmentList();
}

DepartmentView::~DepartmentView()
{
    // 无需手动删除子控件，QWidget 会自动处理
}

// 添加科室按钮点击槽函数
void DepartmentView::on_addDepartmentButton_clicked()
{
    QString departmentName = departmentNameEdit->text().trimmed();
    if (!departmentName.isEmpty()) {
        if (!departmentList.contains(departmentName)) { // 检查是否已存在
            departmentList.append(departmentName);
            refreshDepartmentList();
            departmentNameEdit->clear();
            QMessageBox::information(this, "成功", "科室添加成功！");
        } else {
            QMessageBox::warning(this, "警告", "该科室已存在！");
        }
    } else {
        QMessageBox::warning(this, "警告", "科室名称不能为空！");
    }
}

// 删除科室按钮点击槽函数
void DepartmentView::on_deleteDepartmentButton_clicked()
{
    QListWidgetItem *selectedItem = departmentListWidget->currentItem();
    if (selectedItem) {
        QString name = selectedItem->text();
        departmentList.removeAll(name); // 从列表中移除
        refreshDepartmentList();
        QMessageBox::information(this, "成功", "科室删除成功！");
    } else {
        QMessageBox::warning(this, "警告", "请先选择要删除的科室！");
    }
}

// 科室列表项点击槽函数
void DepartmentView::on_departmentListWidget_itemClicked(QListWidgetItem *item)
{
    if (item) {
        departmentNameEdit->setText(item->text()); // 显示在输入框
    }
}

// 双击科室项进行编辑
void DepartmentView::on_departmentListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if (item) {
        departmentNameEdit->setText(item->text());
        on_deleteDepartmentButton_clicked(); // 删除选中的科室
        departmentNameEdit->setFocus(); // 聚焦到输入框
    }
}

// 刷新科室列表显示的函数
void DepartmentView::refreshDepartmentList()
{
    departmentListWidget->clear();
    for (const QString &name : departmentList) {
        departmentListWidget->addItem(name);
    }
}
