#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "codeeditor.h"
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_new_file_triggered();
    void on_open_file_triggered();
    void on_save_file_triggered();
    void on_save_as_triggered();
    void on_copy_triggered();
    void on_paste_triggered();
    void on_cut_triggered();
    void on_italics_triggered(bool italics);
    void on_underline_triggered(bool underline);
    void on_bolder_triggered(bool bolder);
    void on_undo_triggered();
    void on_redo_triggered();
    void on_font_triggered();
    void on_print_triggered();
    void on_about_triggered();
    void on_exit_triggered();
    void on_clear_history_triggered();
    void on_actionsearch_triggered();
    void on_Searchaction_triggered();
    void on_actionreplace_triggered();
    void on_actiontoolbar_triggered();
    void on_actionstatusbar_triggered();
    void on_open_rencent_file();

private:
    void initMenu();
    CodeEditor *codeEditor;
    Ui::MainWindow *ui;
    QLabel statusLabel;
    QLabel statusCursorLabel;
    QString currentFile;
};

#endif // MAINWINDOW_H
