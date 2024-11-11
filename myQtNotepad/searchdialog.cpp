#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QMessageBox>
#include "codeeditor.h"  // Include CodeEditor header

SearchDialog::SearchDialog(QWidget *parent, CodeEditor *editor)
    : QDialog(parent),
    ui(new Ui::SearchDialog),
    pTextEdit(editor)  // Initialize with the CodeEditor pointer
{
    ui->setupUi(this);

    // Initialize member pointers with UI elements
    rbUp = ui->rbUp;
    rbDown = ui->rbDown;
    cbCaseSensitive = ui->cbCaseSensetive;

    if (!pTextEdit) {
        QMessageBox::critical(this, tr("Error"), tr("Text editor not properly initialized"));
        close();
        return;
    }

    ui->rbDown->setChecked(true);
    connect(ui->pushButton, &QPushButton::clicked, this, &SearchDialog::on_pushButton_clicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &SearchDialog::on_cancelButton_clicked);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_cancelButton_clicked()
{
    reject();
}

void SearchDialog::on_pushButton_clicked()
{
    if (pTextEdit == nullptr) {
        QMessageBox::critical(this, tr("Error"), tr("Text editor not properly initialized"));
        return;
    }

    QString target = ui->searchText->text();
    if (target.isEmpty()) {
        QMessageBox::information(this, tr("Search"), tr("Please enter text to search"));
        return;
    }

    QTextCursor cursor = pTextEdit->textCursor();
    QTextDocument *doc = pTextEdit->document();
    QTextDocument::FindFlags flags = cbCaseSensitive->isChecked() ? QTextDocument::FindCaseSensitively : QTextDocument::FindFlag(0);

    if (rbDown->isChecked()) {
        cursor = doc->find(target, cursor.position(), flags);
    } else if (rbUp->isChecked()) {
        cursor = doc->find(target, cursor.position(), flags | QTextDocument::FindBackward);
    }

    if (!cursor.isNull()) {
        pTextEdit->setTextCursor(cursor);
    } else {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("Notepad"));
        msgBox.setText(QString(tr("Cannot find \"%1\"")).arg(target));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}
