#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Visual components init.
    lbNeedle = new QLabel("Search:");
    lbReplacement = new QLabel("Replace to:");
    lbDirs = new QLabel("Directories and files:");
    lbResult = new QLabel("Result:");
    lbStatistic = new QLabel("*Statistic string*");
    pbSearch = new QPushButton("Search");
    pbReplace = new QPushButton("Replace");
    pbAddDirectory = new QPushButton("Add directory");
    pbAddFile = new QPushButton("Add files");
    pbRemoveFD = new QPushButton("Remove");
    leNeedle = new QLineEdit;
    leReplacement = new QLineEdit;
    lvDirs = new QListView;
    lvResult = new QListView;
    m_dirsAndFilesModel = new QStandardItemModel;
    m_resultModel = new QStandardItemModel;

    // Init lv.
    lvDirs->setModel(m_dirsAndFilesModel);
    lvResult->setModel(m_resultModel);

    initLayouts();
    createActions();
    createMenus();

    QObject::connect(pbSearch, SIGNAL(clicked()), this, SLOT(searchClicked()));
    QObject::connect(pbReplace, SIGNAL(clicked()), this, SLOT(replaceClicked()));
    QObject::connect(pbAddDirectory, SIGNAL(clicked()), this, SLOT(addDirClicked()));
    QObject::connect(pbAddFile, SIGNAL(clicked()), this, SLOT(addFileClicked()));
    QObject::connect(pbRemoveFD, SIGNAL(clicked()), this, SLOT(removeFDClicked()));

    m_engine = new Engine;
    m_baseSettings = new BaseSettings;

    cleanAll();
}

MainWindow::~MainWindow()
{
    delete m_engine;
}

void MainWindow::initLayouts()
{
    QVBoxLayout *main = new QVBoxLayout;
    QHBoxLayout *needle = new QHBoxLayout;
    QHBoxLayout *replacement = new QHBoxLayout;
    QHBoxLayout *dirs = new QHBoxLayout;
    QVBoxLayout *dirsButtons = new QVBoxLayout;

    QWidget *window = new QWidget;


    // Needle line.
    needle->addWidget(lbNeedle);
    needle->addWidget(leNeedle);
    needle->addWidget(pbSearch);

    // Replacement line.
    replacement->addWidget(lbReplacement);
    replacement->addWidget(leReplacement);
    replacement->addWidget(pbReplace);

    // Directories line.
    dirsButtons->addWidget(pbAddDirectory);
    dirsButtons->addWidget(pbAddFile);
    dirsButtons->addWidget(pbRemoveFD);
    dirsButtons->setAlignment(Qt::AlignTop);
    dirs->addWidget(lvDirs);
    dirs->addLayout(dirsButtons);

    main->addLayout(needle);
    main->addLayout(replacement);
    main->addLayout(dirs);
    // Result lines.
    main->addWidget(lbResult);
    main->addWidget(lvResult);
    main->addWidget(lbStatistic);

    window->setLayout(main);
    this->setCentralWidget(window);
}

void MainWindow::createActions()
{
    aSetBackupDir = new QAction(tr("Set backup directory..."), this);
    connect(aSetBackupDir, &QAction::triggered, this,
            &MainWindow::setBackupDir);

    aRevertFromBackup = new QAction(tr("Revert from backup..."), this);
    connect(aRevertFromBackup, &QAction::triggered, this,
            &MainWindow::revertFromBackup);

    aCaseSensetive = new QAction(tr("Case sensetive"), this);
    aCaseSensetive->setCheckable(true);
//    aCaseSensetive->setChecked(true);                                         /// TODO: Uncomment.
    connect(aCaseSensetive, &QAction::changed, this,
            &MainWindow::changeCS);

    aIgnoreWhiteSpaces = new QAction(tr("Ignore white spaces"), this);
    aIgnoreWhiteSpaces->setCheckable(true);
    connect(aIgnoreWhiteSpaces, &QAction::changed, this,
            &MainWindow::changeIgnoreWS);

    aDoesntContain = new QAction(tr("Doesn't contain"), this);
    aDoesntContain->setCheckable(true);
    connect(aDoesntContain, &QAction::changed, this,
            &MainWindow::changeDoesntContain);

    aUseRegExp = new QAction(tr("Use regular expressions"), this);
    aUseRegExp->setCheckable(true);
    connect(aUseRegExp, &QAction::changed, this,
            &MainWindow::changeUseRegExp);

    aWholeWordsOnly = new QAction(tr("Whole words only"), this);
    aWholeWordsOnly->setCheckable(true);
    connect(aWholeWordsOnly, &QAction::changed, this,
            &MainWindow::changeWWO);

    aIgnoreCommented = new QAction(tr("Ignore commented"), this);
    aIgnoreCommented->setCheckable(true);
    connect(aIgnoreCommented, &QAction::changed, this,
            &MainWindow::changeIgnoreCommented);

    aSettings = new QAction(tr("Settings"), this);
    connect(aSettings, &QAction::triggered, this,
            &MainWindow::showAllSettings);

    aCleanAll = new QAction(tr("Clean all"), this);
    aCleanAll->setStatusTip(tr("All will be like was when you started."));          /// TODO: Remove later.
    connect(aCleanAll, &QAction::triggered, this,
            &MainWindow::cleanAll);

    aHelp = new QAction(tr("Help"), this);
    connect(aHelp, &QAction::triggered, this,
            &MainWindow::showHelp);

    aAbout = new QAction(tr("About"), this);
    connect(aAbout, &QAction::triggered, this,
            &MainWindow::showAbout);
}

void MainWindow::createMenus()
{
    QMenu *backup = menuBar()->addMenu("Backup");
    QMenu *settings = menuBar()->addMenu("Settings");
    QMenu *about = menuBar()->addMenu("About");

    backup->addAction(aSetBackupDir);
    backup->addAction(aRevertFromBackup);

    settings->addAction(aCaseSensetive);
    settings->addAction(aIgnoreWhiteSpaces);
    settings->addAction(aDoesntContain);
    settings->addAction(aUseRegExp);
    settings->addAction(aWholeWordsOnly);
    settings->addAction(aIgnoreCommented);
    settings->addSeparator();
    settings->addAction(aSettings);
    settings->addSeparator();
    settings->addAction(aCleanAll);

    about->addAction(aHelp);
    about->addSeparator();
    about->addAction(aAbout);
}

void MainWindow::findAllFiles(const QDir &dir)
{
    QFileInfoList eList = dir.entryInfoList();

    for (auto &elem : eList)
    {
        /// TODO: isChildFolder() - Must have standart solution.
        bool isChild = isChildFolder(dir.path(), elem.absoluteFilePath());
        if (elem.isFile() || elem.isSymLink())
        {
            m_engine->addFile(elem.absoluteFilePath());
        }
        else if (elem.isDir() && isChild)
        {
            QDir subDir(elem.absoluteFilePath());
            findAllFiles(subDir);
        }
    }
}

bool MainWindow::isChildFolder(const QString &root,
                               const QString &child) const
{
//    if (m_searchInSubdir == false)
//    {
//        return false;
//    }

    return root.length() < child.length();
}

AllSettings *MainWindow::getSettings() const
{
    AllSettings *settings = new AllSettings;
    settings->caseSensetive = aCaseSensetive->isChecked();
    settings->ignoreWhiteSpaces = aIgnoreWhiteSpaces->isChecked();
    settings->doesntContain = aDoesntContain->isChecked();
    settings->wholeWordsOnly = aWholeWordsOnly->isChecked();
    settings->useRegExp = aUseRegExp->isChecked();
    settings->ignoreCommented = aIgnoreWhiteSpaces->isChecked();

    settings->commentType = m_baseSettings->commentType;

    // Directories an files.
    settings->searchInSubDirectories = m_baseSettings->searchInSubDirectories;
    settings->useRegExpForFiles = m_baseSettings->useRegExpForFiles;
    settings->searchInArchives = m_baseSettings->searchInArchives;
    settings->maskType = m_baseSettings->maskType;

    return settings;
}

void MainWindow::setSettings(const AllSettings *settings_)
{
    // Forma.
    aCaseSensetive->setChecked(settings_->caseSensetive);
    aIgnoreWhiteSpaces->setChecked(settings_->ignoreWhiteSpaces);
    aDoesntContain->setChecked(settings_->doesntContain);
    aWholeWordsOnly->setChecked(settings_->wholeWordsOnly);
    aUseRegExp->setChecked(settings_->useRegExp);
    aIgnoreCommented->setChecked(settings_->ignoreCommented);

    // Data.
    m_baseSettings->commentType = settings_->commentType;
    m_baseSettings->searchInSubDirectories = settings_->searchInSubDirectories;
    m_baseSettings->useRegExpForFiles = settings_->useRegExpForFiles;
    m_baseSettings->searchInArchives = settings_->searchInArchives;
    m_baseSettings->maskType = settings_->maskType;
}

void MainWindow::setBackupDir()
{

}

void MainWindow::revertFromBackup()
{

}

void MainWindow::changeCS()
{
    m_engine->m_caseSensetive = aCaseSensetive->isChecked();
}

void MainWindow::changeIgnoreWS()
{
    m_engine->m_ignoreWhiteSpaces = aIgnoreWhiteSpaces->isChecked();
}

void MainWindow::changeDoesntContain()
{
    m_engine->m_doesntContain = aDoesntContain->isChecked();
}

void MainWindow::changeWWO()
{
    m_engine->m_wholeWordsOnly = aWholeWordsOnly->isChecked();
}

void MainWindow::changeIgnoreCommented()
{
    m_engine->m_ignoreCommented= aIgnoreCommented->isChecked();
}

void MainWindow::searchClicked()
{
    m_engine->setNeedle(leNeedle->text());
    m_engine->setReplacement(leReplacement->text());

    // Add files in engine.
    for (int i = 0; i < m_dirsAndFilesModel->rowCount(); ++i)
    {
        QModelIndex index = m_dirsAndFilesModel->index(i, 0);
        QString path = index.data(Qt::DisplayRole).toString();

        QFileInfo fileChecker(path);
        if (fileChecker.isFile() || fileChecker.isSymLink())
            m_engine->addFile(path);
        else
            findAllFiles(path);
    }

    m_engine->search(); // if (...) getSimpleResult; else getRXResult();

    auto result = m_engine->getSimpleResult();
    for (auto it = result->begin(); it != result->end(); ++it)
    {
        char buffer[12] = "";
        itoa(it.value()->size(), buffer, 10);
        QStandardItem *item = new QStandardItem(it.key() + "(" + buffer + ")");
        m_resultModel->appendRow(item);
    }
}

void MainWindow::replaceClicked()
{
    m_engine->setReplacement(leReplacement->text());
    m_engine->replace();
}

void MainWindow::addDirClicked()
{
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setOption(QFileDialog::ShowDirsOnly, true);
    fileDialog.setViewMode(QFileDialog::Detail);

    QStringList files;
    if (!fileDialog.exec())
    {
        return;
    }

    // Add files in model.
    for (auto &file : fileDialog.selectedFiles())
    {
        QStandardItem *item = new QStandardItem(file);

        // Directory must be unique.
        if (m_dirsAndFilesModel->indexFromItem(item).isValid())
        {
            delete item;
            continue;
        }
        m_dirsAndFilesModel->appendRow(item);
    }
}

void MainWindow::addFileClicked()
{
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    fileDialog.setViewMode(QFileDialog::Detail);

    if (!fileDialog.exec())
    {
        return;
    }

    // Add files in model.
    for (auto &file : fileDialog.selectedFiles())
    {
        QStandardItem *item = new QStandardItem(file);

        // File must be unique.
        if (m_dirsAndFilesModel->indexFromItem(item).isValid())
        {
            delete item;
            continue;
        }
        m_dirsAndFilesModel->appendRow(item);
    }
}

/// TODO: Remove a few selected items.
void MainWindow::removeFDClicked()
{
    QModelIndex index = lvDirs->currentIndex();

    if (index.isValid())
    {
        m_dirsAndFilesModel->removeRow(lvDirs->currentIndex().row());
    }
}

void MainWindow::cleanAll()
{

}

void MainWindow::showHelp()
{

}

void MainWindow::showAbout()
{

}

void MainWindow::showAllSettings()
{
    Settings settings(this);
    settings.setModal(true);
    AllSettings *settingsData = this->getSettings();
    settings.setSettings(settingsData);

    if (settings.exec() == QDialog::Accepted)
    {
        AllSettings *allData = settings.getSettings();
        this->setSettings(allData);
        delete allData;
    }

    delete settingsData;
}

void MainWindow::changeUseRegExp()
{
    m_engine->m_useRegExp = aUseRegExp->isChecked();
}
