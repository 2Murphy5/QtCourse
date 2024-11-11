#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QMessageBox>
#include <QRadioButton>
#include <QCheckBox>
#include "codeeditor.h" // Include CodeEditor header

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = nullptr, CodeEditor *editor = nullptr); // Use CodeEditor pointer
    ~SearchDialog();

private slots:
    void on_pushButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::SearchDialog *ui;
    CodeEditor *pTextEdit;  // Use CodeEditor pointer instead of QTextEdit
    QRadioButton *rbUp;
    QRadioButton *rbDown;
    QCheckBox *cbCaseSensitive;
};

#endif // SEARCHDIALOG_H
