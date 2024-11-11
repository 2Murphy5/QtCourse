#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDialog>
#include <QSettings>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include "aboutdialog.h"
#include "searchdialog.h"
#include "replacedialog.h"

QSettings *mSettings;

// Function to get history
QList<QString> getHistory();
// Function to save history
void saveHistory(QString path);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , codeEditor(new CodeEditor(this))
{
    ui->setupUi(this);
    setCentralWidget(codeEditor);

    // Update status bar with cursor position
    connect(codeEditor, &QPlainTextEdit::cursorPositionChanged, this, [this]() {
        QTextCursor cursor = codeEditor->textCursor();
        statusCursorLabel.setText("LN: " + QString::number(cursor.blockNumber() + 1) + " Col: " + QString::number(cursor.columnNumber() + 1));
    });

    // Initialize status bar widgets
    statusLabel.setMaximumHeight(150);
    statusLabel.setText("length: 0 lines: 1");
    ui->statusbar->addPermanentWidget(&statusLabel);

    statusCursorLabel.setMaximumHeight(150);
    statusCursorLabel.setText("LN: 1 Col: 1");
    ui->statusbar->addPermanentWidget(&statusCursorLabel);

    QLabel *author = new QLabel(ui->statusbar);
    author->setText(tr("yuanweimin"));
    ui->statusbar->addPermanentWidget(author);

    // Initialize settings
    if (mSettings == nullptr) {
        mSettings = new QSettings("settings.ini", QSettings::IniFormat);
    }

    initMenu();

#if !QT_CONFIG(printer)
    ui->print->setEnabled(false);
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMenu()
{
    QMenu *recent = this->findChild<QMenu *>("recent");
    recent->clear();

    QList<QString> lists = getHistory();
    for (int i = lists.size() - 1; i >= 0; i--) {
        recent->addAction(lists[i], this, &MainWindow::on_open_rencent_file);
    }

    if (!lists.isEmpty()) {
        recent->addAction("清除历史记录", this, &MainWindow::on_clear_history_triggered, QKeySequence("Ctrl+Alt+Shift+C"));
    }
}

QList<QString> getHistory()
{
    int size = mSettings->beginReadArray("history");
    QList<QString> lists;
    for (int i = 0; i < size; i++) {
        mSettings->setArrayIndex(i);
        lists.append(mSettings->value("path").toString());
    }
    mSettings->endArray();
    return lists;
}

void saveHistory(QString path)
{
    QList<QString> lists = getHistory();
    if (lists.contains(path)) {
        lists.removeAll(path);
    }
    lists.append(path);
    mSettings->beginWriteArray("history");
    for (int i = 0; i < lists.size(); i++) {
        mSettings->setArrayIndex(i);
        mSettings->setValue("path", lists[i]);
    }
    mSettings->endArray();
}

void MainWindow::on_new_file_triggered()
{
    currentFile.clear();
    codeEditor->clear();
}

void MainWindow::on_open_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "警告", "无法打开此文件:" + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream in(&file);
    codeEditor->setPlainText(in.readAll());
    file.close();
    saveHistory(currentFile);
    initMenu();
}

void MainWindow::on_open_rencent_file()
{
    QAction *action = (QAction *)sender();
    QString fileName = action->text();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "警告", "无法打开此文件:" + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream in(&file);
    codeEditor->setPlainText(in.readAll());
    file.close();
    saveHistory(currentFile);
    initMenu();
}

void MainWindow::on_save_file_triggered()
{
    QString fileName;
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "保存文件");
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "警告", "无法保存文件:" + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    out << codeEditor->toPlainText();
    file.close();
    saveHistory(currentFile);
    initMenu();
}

void MainWindow::on_save_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "另存文件");
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "警告", "无法保存文件:" + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    out << codeEditor->toPlainText();
    file.close();
    saveHistory(currentFile);
    initMenu();
}

void MainWindow::on_copy_triggered()
{
    codeEditor->copy();
}

void MainWindow::on_paste_triggered()
{
    codeEditor->paste();
}

void MainWindow::on_cut_triggered()
{
    codeEditor->cut();
}

void MainWindow::on_italics_triggered(bool italics)
{
    QTextCharFormat format;
    format.setFontItalic(italics);
    codeEditor->mergeCurrentCharFormat(format);
}

void MainWindow::on_underline_triggered(bool underline)
{
    QTextCharFormat format;
    format.setFontUnderline(underline);
    codeEditor->mergeCurrentCharFormat(format);
}

void MainWindow::on_bolder_triggered(bool bolder)
{
    QTextCharFormat format;
    format.setFontWeight(bolder ? QFont::Bold : QFont::Normal);
    codeEditor->mergeCurrentCharFormat(format);
}

void MainWindow::on_undo_triggered()
{
    codeEditor->undo();
}

void MainWindow::on_redo_triggered()
{
    codeEditor->redo();
}

void MainWindow::on_font_triggered()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected) {
        codeEditor->setFont(font);
    }
}

void MainWindow::on_print_triggered()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printDev;
#if QT_CONFIG(printdialog)
    QPrintDialog dialog(&printDev, this);
    if (dialog.exec() == QDialog::Rejected)
        return;
#endif
    codeEditor->print(&printDev);
#endif
}

void MainWindow::on_about_triggered()
{
    AboutDialog dlg;
    dlg.exec();
}

void MainWindow::on_exit_triggered()
{
    QCoreApplication::exit();
}

void MainWindow::on_clear_history_triggered()
{
    mSettings->remove("history");
    initMenu();
}

void MainWindow::on_actionsearch_triggered()
{
    SearchDialog dlg(this, codeEditor);
    dlg.exec();
}

void MainWindow::on_Searchaction_triggered()
{
    SearchDialog dlg(this, codeEditor);
    dlg.exec();
}

void MainWindow::on_actionreplace_triggered()
{
    ReplaceDialog dlg(this, codeEditor);
    dlg.exec();
}

void MainWindow::on_actiontoolbar_triggered()
{
    bool visible = ui->toolBar->isVisible();
    ui->toolBar->setVisible(!visible);
    ui->actiontoolbar->setCheckable(!visible);
}

void MainWindow::on_actionstatusbar_triggered()
{
    bool visible = ui->statusbar->isVisible();
    ui->statusbar->setVisible(!visible);
    ui->actionstatusbar->setCheckable(!visible);
}
