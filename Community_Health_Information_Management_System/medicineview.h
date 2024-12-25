#ifndef MEDICINEVIEW_H
#define MEDICINEVIEW_H

#include <QWidget>
#include <QSqlTableModel>
#include <QList>

namespace Ui {
class MedicineView;
}

class Medicine {
public:
    Medicine(const QString &name, const QString &dosage, int stock)
        : name(name), dosage(dosage), stock(stock) {}

    QString getName() const { return name; }
    QString getDosage() const { return dosage; }
    int getStock() const { return stock; }

private:
    QString name;
    QString dosage;
    int stock;
};

class MedicineView : public QWidget
{
    Q_OBJECT

public:
    explicit MedicineView(QWidget *parent = nullptr);
    ~MedicineView();

private slots:
    void on_btnAdd_clicked();    // 添加药品按钮点击
    void on_btnDelete_clicked(); // 删除药品按钮点击
    void on_btnQuery_clicked();  // 查询药品按钮点击
    void on_btnExport_clicked(); // 导出药品信息按钮点击

private:
    Ui::MedicineView *ui; // UI 指针
    QSqlTableModel *medicineModel; // 药品数据表模型
    void initDatabase(); // 初始化数据库的方法
    void refreshMedicineTable(); // 刷新药品数据表的方法
};

#endif // MEDICINEVIEW_H
