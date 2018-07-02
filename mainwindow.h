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
#include <QAction>
#include <QMenuBar>
#include <QDir>

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

    // Actions.
    QAction *aSetBackupDir;         // Backup.
    QAction *aRevertFromBackup;

    QAction *aCaseSensetive;        // Settings.
    QAction *aIgnoreWhiteSpaces;
    QAction *aDoesntContaint;
    QAction *aWholeWordsOnly;
    QAction *aSettings;
    QAction *aCleanAll;

    QAction *aHelp;                 // About.
    QAction *aAbout;

    // Data models.
    QStandardItemModel *m_dirsAndFilesModel;
    QStandardItemModel *m_resultModel;

    Engine *m_engine;

    void initLayouts();
    void createActions();
    void createMenus();

    void findAllFiles(const QDir &dir);
    bool isChildFolder(const QString &root, const QString &child) const;

public slots:

    // Actions.
    void setBackupDir();
    void revertFromBackup();
    void changeCS();
    void changeIgnoreWS();
    void changeDoesntContain();
    void changeWWO();
    void showSettings();
    void cleanAll();
    void showHelp();
    void showAllSettings();

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
