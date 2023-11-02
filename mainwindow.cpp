#include <QFile>
#include <QGridLayout>
#include <QPushButton>
#include "customwidgets.h"
#include "mainwindow.h"
#include "manager.h"
#include "./ui_mainwindow.h"

MainWindow* MainWindow::instance_ = nullptr;

MainWindow* MainWindow::instance() {
    if(instance_ == nullptr) {
        instance_ = new MainWindow();
    }
    return instance_;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
//    , ui(new Ui::MainWindow)
{
//    ui->setupUi(this);

    Manager* manager = Manager::instance();

    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    verticalLayout = new QVBoxLayout();
    topHorizontalLayout = new QHBoxLayout();
    topHorizontalLayout->setSpacing(5);
    bottomHorizontalLayout = new QHBoxLayout();
    bottomHorizontalLayout->setSpacing(5);

    mainWidget->setLayout(verticalLayout);

    buttons = new QWidget();
    buttons->setObjectName("buttons");
    buttons->setLayout(topHorizontalLayout);

    elements = new QWidget();
    elements->setObjectName("elements");
    elements->setLayout(bottomHorizontalLayout);

    verticalLayout->addWidget(buttons);
    verticalLayout->addWidget(elements);

    setButtons();
    setElements();

    // apply styles from .qss file
    QFile file("default.qss");

    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    setStyleSheet(styleSheet);
}

QHBoxLayout* MainWindow::getBottomHorizontalLayout() {
    return this->bottomHorizontalLayout;
}

void MainWindow::setButtons() {
    Manager* manager = Manager::instance();

    QPushButton* addButton = new QPushButton("Add");
    addButton->setObjectName("addButton");
    connect(addButton, &QPushButton::clicked, manager, &Manager::addElement);

    QPushButton* refreshButton = new QPushButton("Refresh");
    refreshButton->setObjectName("refreshButton");
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::refreshElements);

    topHorizontalLayout->addWidget(addButton);
    topHorizontalLayout->addWidget(refreshButton);
}

void MainWindow::setElements() {
    Manager* manager = Manager::instance();
    manager->fillElements(this->bottomHorizontalLayout);
}

void MainWindow::refreshElements() {  // TODO add call to modifying functions
    // bad solution
    auto oldElements = this->elements;

    this->elements = new QWidget;
    this->elements->setObjectName("elements");
    this->bottomHorizontalLayout = new QHBoxLayout;
    this->elements->setLayout(this->bottomHorizontalLayout);
    this->verticalLayout->addWidget(this->elements);

    this->setElements();

    delete oldElements;
}


MainWindow::~MainWindow()
{
//    delete ui;
}
