#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString styleSheet = R"(
        QMainWindow {
            background-color: #2e2e2e;
        }
        QLineEdit {
            background-color: #ffffff;
            font-size: 24px;
            padding: 10px;
            border: 2px solid #4d4d4d;
            border-radius: 5px;
        }
        QPushButton {
            background-color: #3c3c3c;
            color: #ffffff;
            font-size: 20px;
            padding: 15px;
            border: none;
            border-radius: 5px;
        }
        QPushButton:hover {
            background-color: #4d4d4d;
        }
        QPushButton:pressed {
            background-color: #5c5c5c;
        }
    )";

    setStyleSheet(styleSheet);
    //对应的按钮与槽函数关联起来
    connect(ui->percentButton, &QPushButton::clicked, this, &MainWindow::onPercentButtonClicked);
    connect(ui->clearEntryButton, &QPushButton::clicked, this, &MainWindow::onClearEntryButtonClicked);
    connect(ui->clearAllButton, &QPushButton::clicked, this, &MainWindow::onClearAllButtonClicked);
    connect(ui->inverseButton, &QPushButton::clicked, this, &MainWindow::onInverseButtonClicked);
    connect(ui->squareButton, &QPushButton::clicked, this, &MainWindow::onSquareButtonClicked);
    connect(ui->sqrtButton, &QPushButton::clicked, this, &MainWindow::onSqrtButtonClicked);
    connect(ui->divideButton, &QPushButton::clicked, this, &MainWindow::onDivideButtonClicked);
    connect(ui->sevenButton, &QPushButton::clicked, this, &MainWindow::onSevenButtonClicked);
    connect(ui->eightButton, &QPushButton::clicked, this, &MainWindow::onEightButtonClicked);
    connect(ui->nineButton, &QPushButton::clicked, this, &MainWindow::onNineButtonClicked);
    connect(ui->multiplyButton, &QPushButton::clicked, this, &MainWindow::onMultiplyButtonClicked);
    connect(ui->fourButton, &QPushButton::clicked, this, &MainWindow::onFourButtonClicked);
    connect(ui->fiveButton, &QPushButton::clicked, this, &MainWindow::onFiveButtonClicked);
    connect(ui->sixButton, &QPushButton::clicked, this, &MainWindow::onSixButtonClicked);
    connect(ui->minusButton, &QPushButton::clicked, this, &MainWindow::onMinusButtonClicked);
    connect(ui->oneButton, &QPushButton::clicked, this, &MainWindow::onOneButtonClicked);
    connect(ui->twoButton, &QPushButton::clicked, this, &MainWindow::onTwoButtonClicked);
    connect(ui->threeButton, &QPushButton::clicked, this, &MainWindow::onThreeButtonClicked);
    connect(ui->plusButton, &QPushButton::clicked, this, &MainWindow::onPlusButtonClicked);
    connect(ui->signChangeButton, &QPushButton::clicked, this, &MainWindow::onSignChangeButtonClicked);
    connect(ui->zeroButton, &QPushButton::clicked, this, &MainWindow::onZeroButtonClicked);
    connect(ui->decimalButton, &QPushButton::clicked, this, &MainWindow::onDecimalButtonClicked);
    connect(ui->equalButton, &QPushButton::clicked, this, &MainWindow::onEqualButtonClicked);
    connect(ui->delButton, &QPushButton::clicked, this, &MainWindow::onDelButtonClicked);
    // 初始化变量的状态
    currentExpression = "";
    previousExpression = "";
    currentOperator = "";
    previousOperand = 0.0;
    waitingForOperand = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_0: onZeroButtonClicked(); break;
    case Qt::Key_1: onOneButtonClicked(); break;
    case Qt::Key_2: onTwoButtonClicked(); break;
    case Qt::Key_3: onThreeButtonClicked(); break;
    case Qt::Key_4: onFourButtonClicked(); break;
    case Qt::Key_5: onFiveButtonClicked(); break;
    case Qt::Key_6: onSixButtonClicked(); break;
    case Qt::Key_7: onSevenButtonClicked(); break;
    case Qt::Key_8: onEightButtonClicked(); break;
    case Qt::Key_9: onNineButtonClicked(); break;
    case Qt::Key_Plus: onPlusButtonClicked(); break;
    case Qt::Key_Minus: onMinusButtonClicked(); break;
    case Qt::Key_Asterisk: onMultiplyButtonClicked(); break; // *键
    case Qt::Key_Slash: onDivideButtonClicked(); break; // /键
    case Qt::Key_Return: case Qt::Key_Equal: onEqualButtonClicked(); break; // Enter和=键
    case Qt::Key_Backspace: onDelButtonClicked(); break; // 删除键
    case Qt::Key_Percent: onPercentButtonClicked(); break; // %键
    case Qt::Key_Period: onDecimalButtonClicked(); break; // 小数点键
    case Qt::Key_Space: onClearAllButtonClicked(); break; // 空格键清除所有
    default: QMainWindow::keyPressEvent(event); // 其他按键
    }
}

// 百分号按钮的对应的逻辑操作
void MainWindow::onPercentButtonClicked()
{
    if (!currentExpression.isEmpty()) {
        double value = currentExpression.toDouble();
        value /= 100.0;
        currentExpression = QString::number(value);
        ui->display->setText(currentExpression);
    }
}

// 删除一个的操作的逻辑
void MainWindow::onClearEntryButtonClicked()
{
    currentExpression = "";
    ui->display->setText("0");
}

// 清除全部的操作的逻辑
void MainWindow::onClearAllButtonClicked()
{
    currentExpression = "";
    previousExpression = "";
    currentOperator = "";
    previousOperand = 0.0;
    waitingForOperand = true;
    ui->display->setText("0");
}

// 反转的函数被的逻辑
void MainWindow::onInverseButtonClicked()
{
    if (!currentExpression.isEmpty()) {
        double value = currentExpression.toDouble();
        if (value != 0.0) {
            value = 1.0 / value;
            currentExpression = QString::number(value);
            ui->display->setText(currentExpression);
        } else {
            ui->display->setText("Error: Divide by zero");
        }
    }
}
//删除的逻辑
void MainWindow::onDelButtonClicked()
{
    if (!currentExpression.isEmpty()) {
        currentExpression.chop(1);
        if (currentExpression.isEmpty()) {
            ui->display->setText("0");
        } else {
            ui->display->setText(currentExpression);
        }
    }
}
// 平方操作的逻辑
void MainWindow::onSquareButtonClicked()
{
    if (!currentExpression.isEmpty()) {
        double value = currentExpression.toDouble();
        value = value * value;
        currentExpression = QString::number(value);
        ui->display->setText(currentExpression);
    }
}

// 开根号操作的逻辑
void MainWindow::onSqrtButtonClicked()
{
    if (!currentExpression.isEmpty()) {
        double value = currentExpression.toDouble();
        if (value >= 0.0) {
            value = sqrt(value);
            currentExpression = QString::number(value);
            ui->display->setText(currentExpression);
        } else {
            ui->display->setText("Error: Negative sqrt");
        }
    }
}

// 符号改变操作的逻辑
void MainWindow::onSignChangeButtonClicked()
{
    if (!currentExpression.isEmpty()) {
        double value = currentExpression.toDouble();
        value = -value;
        currentExpression = QString::number(value);
        ui->display->setText(currentExpression);
    }
}

// 零按钮的操作的逻辑
void MainWindow::onZeroButtonClicked()
{
    addDigitToExpression("0");
}

//小数点操作的相关逻辑
void MainWindow::onDecimalButtonClicked()
{
    if (!currentExpression.contains('.'))
        addDigitToExpression(".");
}

// 等于操作的相关的逻辑
void MainWindow::onEqualButtonClicked()
{
    performOperation();
    waitingForOperand = true;
}
//加法操作的想过逻辑
void MainWindow::addDigitToExpression(const QString &digit)
{
    if (waitingForOperand) {
        currentExpression = digit;
        waitingForOperand = false;
    } else {
        currentExpression += digit;
    }
    ui->display->setText(currentExpression);
}
//定义运算的相关的法则
void MainWindow::performOperation()
{
    if (!currentExpression.isEmpty()) {
        double currentOperand = currentExpression.toDouble();
        if (!currentOperator.isEmpty()) {
            if (currentOperator == "+") {
                previousOperand += currentOperand;
            } else if (currentOperator == "-") {
                previousOperand -= currentOperand;
            } else if (currentOperator == "*") {
                previousOperand *= currentOperand;
            } else if (currentOperator == "/") {
                if (currentOperand != 0) {
                    previousOperand /= currentOperand;
                } else {
                    ui->display->setText("Error: Divide by zero");
                    return;
                }
            }
        } else {
            previousOperand = currentOperand;
        }
        currentExpression = QString::number(previousOperand);
        ui->display->setText(currentExpression);
    }
}

void MainWindow::onDivideButtonClicked()
{
    performOperation();
    currentOperator = "/";
    waitingForOperand = true;
}

void MainWindow::onMultiplyButtonClicked()
{
    performOperation();
    currentOperator = "*";
    waitingForOperand = true;
}

void MainWindow::onMinusButtonClicked()
{
    performOperation();
    currentOperator = "-";
    waitingForOperand = true;
}

void MainWindow::onPlusButtonClicked()
{
    performOperation();
    currentOperator = "+";
    waitingForOperand = true;
}

void MainWindow::onSevenButtonClicked()
{
    addDigitToExpression("7");
}

void MainWindow::onEightButtonClicked()
{
    addDigitToExpression("8");
}

void MainWindow::onNineButtonClicked()
{
    addDigitToExpression("9");
}

void MainWindow::onFourButtonClicked()
{
    addDigitToExpression("4");
}

void MainWindow::onFiveButtonClicked()
{
    addDigitToExpression("5");
}

void MainWindow::onSixButtonClicked()
{
    addDigitToExpression("6");
}

void MainWindow::onOneButtonClicked()
{
    addDigitToExpression("1");
}

void MainWindow::onTwoButtonClicked()
{
    addDigitToExpression("2");
}

void MainWindow::onThreeButtonClicked()
{
    addDigitToExpression("3");
}
