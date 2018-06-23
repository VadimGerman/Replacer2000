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

    QObject::connect(pbSearch, SIGNAL(clicked()), this, SLOT(searchClicked()));
    QObject::connect(pbReplace, SIGNAL(clicked()), this, SLOT(replaceClicked()));
    QObject::connect(pbAddDirectory, SIGNAL(clicked()), this, SLOT(addDirClicked()));
    QObject::connect(pbAddFile, SIGNAL(clicked()), this, SLOT(addFileClicked()));
    QObject::connect(pbRemoveFD, SIGNAL(clicked()), this, SLOT(removeFDClicked()));
}

MainWindow::~MainWindow()
{

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

void MainWindow::searchClicked()
{
    QMessageBox::information(this, "Information", "search clicked");
}

void MainWindow::replaceClicked()
{
    QMessageBox::information(this, "Information", "replace clicked");
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

// TODO: Remove a few selected items.
void MainWindow::removeFDClicked()
{
    QModelIndex index = lvDirs->currentIndex();

    if (index.isValid())
    {
        m_dirsAndFilesModel->removeRow(lvDirs->currentIndex().row());
    }
}
