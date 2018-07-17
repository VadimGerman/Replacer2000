#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QRadioButton>

#include "settingsdata.h"

class Settings : public QDialog
{
    Q_OBJECT

    QVBoxLayout *vlMain;
    QHBoxLayout *hlButtons;
    QGroupBox *gbSearchSettings;
    QGroupBox *gbFileSettings;

    QPushButton *pbOk;
    QPushButton *pbCancle;

    QVBoxLayout *vlSearchGroup;
    QCheckBox *cbCaseSensetive;
    QCheckBox *cbIgnoreWhiteSpaces;
    QCheckBox *cbDoesntContain;
    QCheckBox *cbWholeWordsOnly;
    QCheckBox *cbUseRegExp;
    QCheckBox *cbIgnoreCommented;

    QHBoxLayout *hlCommentType;
    QLabel *lbCommentType;
    QLineEdit *leCommentType;


    QVBoxLayout *vlFilesSettingsGroup;
    QCheckBox *cbInSubDirectories;
    QCheckBox *cbInArchives;
    QCheckBox *cbCaseSensetiveForFiles;

    QHBoxLayout *hlUseOnlyOrIgnore;
    QRadioButton *rbIgnore;
    QRadioButton *rbUseOnly;

    QHBoxLayout *hlFileMask;
    QLabel *lbFileMask;
    QLineEdit *leFileMask;

    void initComponents();
    void initLayouts();

public:
    explicit Settings(QWidget *parent = nullptr);

    void setSettings(const AllSettings *settings_);
    AllSettings * getSettings() const;

signals:

public slots:
    void okClicked();
    void cancleClicked();

};

#endif // SETTINGS_H
