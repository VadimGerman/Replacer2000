#include "settings.h"

Settings::Settings(QWidget *parent) : QDialog(parent)
{
    initComponents();
    initLayouts();
}

void Settings::initComponents()
{
    gbSearchSettings = new QGroupBox("Search");
    gbFileSettings = new QGroupBox("Files");

    pbOk = new QPushButton("Ok");
    connect(pbOk, &QPushButton::clicked, this,
            &Settings::okClicked);

    pbCancle = new QPushButton("Cancle");
    connect(pbCancle, &QPushButton::clicked, this,
            &Settings::cancleClicked);

    cbCaseSensetive = new QCheckBox("Case sensetive");
    cbIgnoreWhiteSpaces = new QCheckBox("Ignore white spaces");
    cbDoesntContain = new QCheckBox("Doesn't contain");
    cbWholeWordsOnly = new QCheckBox("Whole words only");
    cbUseRegExp = new QCheckBox("Use regular expressions");
    cbIgnoreCommented = new QCheckBox("Ignore commented");

    lbCommentType = new QLabel("Comment type:");
    leCommentType = new QLineEdit;

    cbInSubDirectories = new QCheckBox("Search in sub directories");
    cbInArchives = new QCheckBox("Search in archives");
    cbUseRegExpForFiles = new QCheckBox("Use regular expressions");

    rbIgnore = new QRadioButton("Ignore");
    rbUseOnly = new QRadioButton("Use only");

    lbFileMask = new QLabel("File mask:");
    leFileMask = new QLineEdit;
}

void Settings::initLayouts()
{
    vlMain = new QVBoxLayout;

    // Search settings.
    vlSearchGroup = new QVBoxLayout;
    hlButtons = new QHBoxLayout;
    hlCommentType = new QHBoxLayout;

    // File settings.
    vlFilesSettingsGroup = new QVBoxLayout;
    hlUseOnlyOrIgnore = new QHBoxLayout;
    hlFileMask = new QHBoxLayout;

    // Main layout.
    vlMain->addWidget(gbSearchSettings);
    gbSearchSettings->setLayout(vlSearchGroup);
    vlMain->addWidget(gbFileSettings);
    gbFileSettings->setLayout(vlFilesSettingsGroup);
    vlMain->addLayout(hlButtons);

    // горизонтальная линия с лейблом и текстовым полем для ввода
    // типа коммента.
    hlCommentType->addWidget(lbCommentType);
    hlCommentType->addWidget(leCommentType);

    // Group box "Search"
    vlSearchGroup->addWidget(cbCaseSensetive);
    vlSearchGroup->addWidget(cbIgnoreWhiteSpaces);
    vlSearchGroup->addWidget(cbDoesntContain);
    vlSearchGroup->addWidget(cbWholeWordsOnly);
    vlSearchGroup->addWidget(cbUseRegExp);
    vlSearchGroup->addWidget(cbIgnoreCommented);
    vlSearchGroup->addLayout(hlCommentType);

    vlFilesSettingsGroup->addWidget(cbInSubDirectories);
    vlFilesSettingsGroup->addWidget(cbInArchives);
    vlFilesSettingsGroup->addWidget(cbUseRegExpForFiles);
    vlFilesSettingsGroup->addLayout(hlUseOnlyOrIgnore);
    vlFilesSettingsGroup->addLayout(hlFileMask);

    hlUseOnlyOrIgnore->addWidget(rbIgnore);
    hlUseOnlyOrIgnore->addWidget(rbUseOnly);
    rbIgnore->setChecked(true);
    hlFileMask->addWidget(lbFileMask);
    hlFileMask->addWidget(leFileMask);

    hlButtons->addWidget(pbOk);
    hlButtons->addWidget(pbCancle);

    this->setLayout(vlMain);
}

void Settings::setSettings(const AllSettings*settings_)
{
    cbCaseSensetive->setChecked(settings_->caseSensetive);
    cbIgnoreWhiteSpaces->setChecked(settings_->ignoreWhiteSpaces);
    cbDoesntContain->setChecked(settings_->doesntContain);
    cbWholeWordsOnly->setChecked(settings_->wholeWordsOnly);
    cbUseRegExp->setChecked(settings_->useRegExp);
    cbIgnoreCommented->setChecked(settings_->ignoreCommented);
    leCommentType->setText(settings_->commentType);
    cbInSubDirectories->setChecked(settings_->searchInSubDirectories);
    cbInArchives->setChecked(settings_->searchInArchives);
    cbUseRegExpForFiles->setChecked(settings_->useRegExpForFiles);
    rbIgnore->setChecked(settings_->maskType ==
                            FileFilterMaskType::IgnoreLikeThis);
    leFileMask->setText(settings_->fileMask);
}

AllSettings * Settings::getSettings() const
{
    AllSettings *settings = new AllSettings;

    settings->caseSensetive = cbCaseSensetive->isChecked();
    settings->ignoreWhiteSpaces = cbIgnoreWhiteSpaces->isChecked();
    settings->doesntContain = cbDoesntContain->isChecked();
    settings->wholeWordsOnly = cbWholeWordsOnly->isChecked();
    settings->useRegExp = cbUseRegExp->isChecked();
    settings->ignoreCommented = cbIgnoreCommented->isChecked();
    settings->commentType = leCommentType->text();
    settings->searchInSubDirectories = cbInSubDirectories->isChecked();
    settings->searchInArchives = cbInArchives->isChecked();
    settings->useRegExpForFiles = cbUseRegExpForFiles->isChecked();
    settings->maskType = (rbIgnore->isChecked() ?
              FileFilterMaskType::IgnoreLikeThis :
              FileFilterMaskType::UseOnlyLikeThis);
    settings->fileMask = leFileMask->text();

    return settings;
}

void Settings::okClicked()
{
    emit this->accept();
}

void Settings::cancleClicked()
{
    emit this->reject();
}
