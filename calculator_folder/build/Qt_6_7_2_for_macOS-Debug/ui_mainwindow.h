/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *display;
    QGridLayout *buttonLayout;
    QPushButton *percentButton;
    QPushButton *clearEntryButton;
    QPushButton *clearAllButton;
    QPushButton *delButton;
    QPushButton *inverseButton;
    QPushButton *squareButton;
    QPushButton *sqrtButton;
    QPushButton *divideButton;
    QPushButton *sevenButton;
    QPushButton *eightButton;
    QPushButton *nineButton;
    QPushButton *multiplyButton;
    QPushButton *fourButton;
    QPushButton *fiveButton;
    QPushButton *sixButton;
    QPushButton *minusButton;
    QPushButton *oneButton;
    QPushButton *twoButton;
    QPushButton *threeButton;
    QPushButton *plusButton;
    QPushButton *signChangeButton;
    QPushButton *zeroButton;
    QPushButton *decimalButton;
    QPushButton *equalButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        display = new QLineEdit(centralwidget);
        display->setObjectName("display");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(display->sizePolicy().hasHeightForWidth());
        display->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(display);

        buttonLayout = new QGridLayout();
        buttonLayout->setObjectName("buttonLayout");
        percentButton = new QPushButton(centralwidget);
        percentButton->setObjectName("percentButton");
        sizePolicy.setHeightForWidth(percentButton->sizePolicy().hasHeightForWidth());
        percentButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(percentButton, 0, 0, 1, 1);

        clearEntryButton = new QPushButton(centralwidget);
        clearEntryButton->setObjectName("clearEntryButton");
        sizePolicy.setHeightForWidth(clearEntryButton->sizePolicy().hasHeightForWidth());
        clearEntryButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(clearEntryButton, 0, 1, 1, 1);

        clearAllButton = new QPushButton(centralwidget);
        clearAllButton->setObjectName("clearAllButton");
        sizePolicy.setHeightForWidth(clearAllButton->sizePolicy().hasHeightForWidth());
        clearAllButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(clearAllButton, 0, 2, 1, 1);

        delButton = new QPushButton(centralwidget);
        delButton->setObjectName("delButton");
        sizePolicy.setHeightForWidth(delButton->sizePolicy().hasHeightForWidth());
        delButton->setSizePolicy(sizePolicy);
        delButton->setMinimumSize(QSize(50, 30));
        delButton->setMaximumSize(QSize(80, 40));

        buttonLayout->addWidget(delButton, 0, 3, 1, 1);

        inverseButton = new QPushButton(centralwidget);
        inverseButton->setObjectName("inverseButton");
        sizePolicy.setHeightForWidth(inverseButton->sizePolicy().hasHeightForWidth());
        inverseButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(inverseButton, 1, 0, 1, 1);

        squareButton = new QPushButton(centralwidget);
        squareButton->setObjectName("squareButton");
        sizePolicy.setHeightForWidth(squareButton->sizePolicy().hasHeightForWidth());
        squareButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(squareButton, 1, 1, 1, 1);

        sqrtButton = new QPushButton(centralwidget);
        sqrtButton->setObjectName("sqrtButton");
        sizePolicy.setHeightForWidth(sqrtButton->sizePolicy().hasHeightForWidth());
        sqrtButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(sqrtButton, 1, 2, 1, 1);

        divideButton = new QPushButton(centralwidget);
        divideButton->setObjectName("divideButton");
        sizePolicy.setHeightForWidth(divideButton->sizePolicy().hasHeightForWidth());
        divideButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(divideButton, 1, 3, 1, 1);

        sevenButton = new QPushButton(centralwidget);
        sevenButton->setObjectName("sevenButton");
        sizePolicy.setHeightForWidth(sevenButton->sizePolicy().hasHeightForWidth());
        sevenButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(sevenButton, 2, 0, 1, 1);

        eightButton = new QPushButton(centralwidget);
        eightButton->setObjectName("eightButton");
        sizePolicy.setHeightForWidth(eightButton->sizePolicy().hasHeightForWidth());
        eightButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(eightButton, 2, 1, 1, 1);

        nineButton = new QPushButton(centralwidget);
        nineButton->setObjectName("nineButton");
        sizePolicy.setHeightForWidth(nineButton->sizePolicy().hasHeightForWidth());
        nineButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(nineButton, 2, 2, 1, 1);

        multiplyButton = new QPushButton(centralwidget);
        multiplyButton->setObjectName("multiplyButton");
        sizePolicy.setHeightForWidth(multiplyButton->sizePolicy().hasHeightForWidth());
        multiplyButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(multiplyButton, 2, 3, 1, 1);

        fourButton = new QPushButton(centralwidget);
        fourButton->setObjectName("fourButton");
        sizePolicy.setHeightForWidth(fourButton->sizePolicy().hasHeightForWidth());
        fourButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(fourButton, 3, 0, 1, 1);

        fiveButton = new QPushButton(centralwidget);
        fiveButton->setObjectName("fiveButton");
        sizePolicy.setHeightForWidth(fiveButton->sizePolicy().hasHeightForWidth());
        fiveButton->setSizePolicy(sizePolicy);
        fiveButton->setMaximumSize(QSize(400, 800));

        buttonLayout->addWidget(fiveButton, 3, 1, 1, 1);

        sixButton = new QPushButton(centralwidget);
        sixButton->setObjectName("sixButton");
        sizePolicy.setHeightForWidth(sixButton->sizePolicy().hasHeightForWidth());
        sixButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(sixButton, 3, 2, 1, 1);

        minusButton = new QPushButton(centralwidget);
        minusButton->setObjectName("minusButton");
        sizePolicy.setHeightForWidth(minusButton->sizePolicy().hasHeightForWidth());
        minusButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(minusButton, 3, 3, 1, 1);

        oneButton = new QPushButton(centralwidget);
        oneButton->setObjectName("oneButton");
        sizePolicy.setHeightForWidth(oneButton->sizePolicy().hasHeightForWidth());
        oneButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(oneButton, 4, 0, 1, 1);

        twoButton = new QPushButton(centralwidget);
        twoButton->setObjectName("twoButton");
        sizePolicy.setHeightForWidth(twoButton->sizePolicy().hasHeightForWidth());
        twoButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(twoButton, 4, 1, 1, 1);

        threeButton = new QPushButton(centralwidget);
        threeButton->setObjectName("threeButton");
        sizePolicy.setHeightForWidth(threeButton->sizePolicy().hasHeightForWidth());
        threeButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(threeButton, 4, 2, 1, 1);

        plusButton = new QPushButton(centralwidget);
        plusButton->setObjectName("plusButton");
        sizePolicy.setHeightForWidth(plusButton->sizePolicy().hasHeightForWidth());
        plusButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(plusButton, 4, 3, 1, 1);

        signChangeButton = new QPushButton(centralwidget);
        signChangeButton->setObjectName("signChangeButton");
        sizePolicy.setHeightForWidth(signChangeButton->sizePolicy().hasHeightForWidth());
        signChangeButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(signChangeButton, 5, 0, 1, 1);

        zeroButton = new QPushButton(centralwidget);
        zeroButton->setObjectName("zeroButton");
        sizePolicy.setHeightForWidth(zeroButton->sizePolicy().hasHeightForWidth());
        zeroButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(zeroButton, 5, 1, 1, 1);

        decimalButton = new QPushButton(centralwidget);
        decimalButton->setObjectName("decimalButton");
        sizePolicy.setHeightForWidth(decimalButton->sizePolicy().hasHeightForWidth());
        decimalButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(decimalButton, 5, 2, 1, 1);

        equalButton = new QPushButton(centralwidget);
        equalButton->setObjectName("equalButton");
        sizePolicy.setHeightForWidth(equalButton->sizePolicy().hasHeightForWidth());
        equalButton->setSizePolicy(sizePolicy);

        buttonLayout->addWidget(equalButton, 5, 3, 1, 1);


        verticalLayout->addLayout(buttonLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Calculator", nullptr));
        percentButton->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        clearEntryButton->setText(QCoreApplication::translate("MainWindow", "CE", nullptr));
        clearAllButton->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        delButton->setText(QCoreApplication::translate("MainWindow", "del", nullptr));
        inverseButton->setText(QCoreApplication::translate("MainWindow", "1/x", nullptr));
        squareButton->setText(QCoreApplication::translate("MainWindow", "x\302\262", nullptr));
        sqrtButton->setText(QCoreApplication::translate("MainWindow", "\342\210\232x", nullptr));
        divideButton->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        sevenButton->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        eightButton->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        nineButton->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        multiplyButton->setText(QCoreApplication::translate("MainWindow", "\303\227", nullptr));
        fourButton->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        fiveButton->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        sixButton->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        minusButton->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        oneButton->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        twoButton->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        threeButton->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        plusButton->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        signChangeButton->setText(QCoreApplication::translate("MainWindow", "+/-", nullptr));
        zeroButton->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        decimalButton->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        equalButton->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
