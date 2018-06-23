#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Visual components init.
    lbNeedle = new QLabel("Search:");
    lbReplacement = new QLabel("Replace to:");
    lbDirs = new QLabel("Directories and files:");         // Files and directories.
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
    QMessageBox::information(this, "Information", "add directory clicked");
}

void MainWindow::addFileClicked()
{
    QMessageBox::information(this, "Information", "add file clicked");
}

void MainWindow::removeFDClicked()
{
    QMessageBox::information(this, "Information", "remove clicked");
}
