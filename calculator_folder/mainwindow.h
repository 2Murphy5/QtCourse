#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *event) override; // 确保这个声明存在
private slots:
    void onPercentButtonClicked();
    void onClearEntryButtonClicked();
    void onClearAllButtonClicked();
    void onInverseButtonClicked();
    void onSquareButtonClicked();
    void onSqrtButtonClicked();
    void onDivideButtonClicked();
    void onSevenButtonClicked();
    void onEightButtonClicked();
    void onNineButtonClicked();
    void onMultiplyButtonClicked();
    void onFourButtonClicked();
    void onFiveButtonClicked();
    void onSixButtonClicked();
    void onMinusButtonClicked();
    void onOneButtonClicked();
    void onTwoButtonClicked();
    void onThreeButtonClicked();
    void onPlusButtonClicked();
    void onSignChangeButtonClicked();
    void onZeroButtonClicked();
    void onDecimalButtonClicked();
    void onEqualButtonClicked();
    void onDelButtonClicked();

private:
    Ui::MainWindow *ui;
    QString currentExpression;
    QString previousExpression;
    QString currentOperator;
    double previousOperand;
    bool waitingForOperand;
private:
    void addDigitToExpression(const QString &digit);
    void performOperation();
};

#endif // MAINWINDOW_H
