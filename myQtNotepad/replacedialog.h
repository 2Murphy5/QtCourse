#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include "codeeditor.h" // Include CodeEditor header

namespace Ui {
class ReplaceDialog;
}

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceDialog(QWidget *parent = nullptr, CodeEditor *editor = nullptr);  // Use CodeEditor pointer
    ~ReplaceDialog();

private slots:
    void on_pushButton_clicked();      // Find Next
    void on_pushButton_2_clicked();    // Replace
    void on_pushButton_3_clicked();    // Replace All
    void on_pushButton_4_clicked();    // Cancel

private:
    Ui::ReplaceDialog *ui;
    CodeEditor *textEdit;          // Change to CodeEditor pointer
};

#endif // REPLACEDIALOG_H
