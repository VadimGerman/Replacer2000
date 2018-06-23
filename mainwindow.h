#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QMessageBox>


class MainWindow : public QMainWindow
{
    Q_OBJECT

    QLabel *lbNeedle;
    QLabel *lbReplacement;
    QLabel *lbDirs;         // Files and directories.
    QLabel *lbResult;
    QLabel *lbStatistic;

    QLineEdit *leNeedle;
    QLineEdit *leReplacement;

    QPushButton *pbSearch;
    QPushButton *pbReplace;
    QPushButton *pbAddDirectory;
    QPushButton *pbAddFile;
    QPushButton *pbRemoveFD;        // File or directory.

    QListView *lvDirs;
    QListView *lvResult;

    void initLayouts();

public slots:
    void searchClicked();
    void replaceClicked();
    void addDirClicked();
    void addFileClicked();
    void removeFDClicked();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
