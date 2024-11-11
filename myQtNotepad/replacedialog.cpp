#include "replacedialog.h"
#include "ui_replacedialog.h"
#include <QMessageBox>
#include <QTextDocument>
#include <QTextCursor>

ReplaceDialog::ReplaceDialog(QWidget *parent, CodeEditor *editor)
    : QDialog(parent), ui(new Ui::ReplaceDialog), textEdit(editor)  // Use CodeEditor pointer
{
    ui->setupUi(this);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &ReplaceDialog::on_pushButton_4_clicked);
}

ReplaceDialog::~ReplaceDialog() {
    delete ui;
}

void ReplaceDialog::on_pushButton_clicked() {
    QString search = ui->lineEdit->text();
    if (search.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("Search term cannot be empty."));
        return;
    }

    QTextCursor cursor = textEdit->textCursor();
    cursor = textEdit->document()->find(search, cursor);

    if (!cursor.isNull()) {
        textEdit->setTextCursor(cursor);
        textEdit->ensureCursorVisible();
    } else {
        QMessageBox::information(this, tr("Find"), tr("No more occurrences found."));
    }
}

void ReplaceDialog::on_pushButton_2_clicked() {
    QString search = ui->lineEdit->text();
    QString replace = ui->lineEdit_2->text();
    if (search.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("Search term cannot be empty."));
        return;
    }

    QTextCursor cursor = textEdit->textCursor();
    cursor = textEdit->document()->find(search, cursor);

    if (!cursor.isNull()) {
        cursor.insertText(replace);
        textEdit->setTextCursor(cursor);
        textEdit->ensureCursorVisible();
    } else {
        QMessageBox::information(this, tr("Replace"), tr("No occurrence found to replace."));
    }
}

void ReplaceDialog::on_pushButton_3_clicked() {
    QString search = ui->lineEdit->text();
    QString replace = ui->lineEdit_2->text();
    if (search.isEmpty()) {
        QMessageBox::warning(this, tr("Warning"), tr("Search term cannot be empty."));
        return;
    }

    QTextCursor cursor = textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start);

    int replaceCount = 0;
    while (!(cursor = textEdit->document()->find(search, cursor)).isNull()) {
        cursor.insertText(replace);
        replaceCount++;
    }

    QMessageBox::information(this, tr("Replace All"), tr("%1 occurrences replaced.").arg(replaceCount));
}

void ReplaceDialog::on_pushButton_4_clicked() {
    this->reject();
}
