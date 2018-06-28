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
#include <QFileDialog>
#include <QStandardItem>

#include "engine.h"


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

    // List of directories and files for search.
    QListView *lvDirs;

    // Search or replace result list.
    QListView *lvResult;

    // Data models.
    QStandardItemModel *m_dirsAndFilesModel;
    QStandardItemModel *m_resultModel;

    Engine *m_engine;

    void initLayouts();

public slots:
    void searchClicked();
    void replaceClicked();

    // Add directory to lvDirs list.
    void addDirClicked();
    //
    void addFileClicked();

    // Get selected indexes(from lvDirs) and remove it.
    void removeFDClicked();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
