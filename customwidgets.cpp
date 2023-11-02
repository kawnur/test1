#include <QFormLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include "customwidgets.h"

Element::Element() {
    name_ = "defaultName";
    description_ = "defaultDescription";
    setStructure();
}

Element::Element(QString& name, QString& description) :
    name_(name), description_(description) {
    setStructure();
};

void Element::setName(QString& name) {
    this->name_ = name;
    this->nameLabel_->setText(this->name_);
}

QString Element::getName() {
    return this->name_;
}

void Element::setDescription(QString& description) {
    this->description_ = description;
    this->descriptionLabel_->setText(this->description_);
}

QString Element::getDescription() {
    return this->description_;
}

void Element::edit() {
    Manager* manager = Manager::instance();
    manager->resetElement(this);
}

void Element::remove() {
    Manager* manager = Manager::instance();
    manager->removeElement(this);
}

void Element::print() {
    std::cout << this->name_.toStdString() << " "
              << this->description_.toStdString() << std::endl;
}

void Element::setStructure() {
    layout_ = new QVBoxLayout(this);
    this->setLayout(layout_);

    emptyLabel_ = new QLabel("stub for red dot");  // imitation for red dot field
    nameLabel_ = new QLabel(this->name_);
    descriptionLabel_ = new QLabel(this->description_);

    buttonFieldLayout_ = new QHBoxLayout(this);
    buttonField_ = new QWidget();
    buttonField_->setLayout(buttonFieldLayout_);

    editButton_ = new QPushButton("Edit");
    connect(editButton_, &QPushButton::clicked, this, &Element::edit);
    removeButton_ = new QPushButton("Delete");
    connect(removeButton_, &QPushButton::clicked, this, &Element::remove);

    buttonFieldLayout_->addWidget(editButton_);
    buttonFieldLayout_->addWidget(removeButton_);

    layout_->addWidget(emptyLabel_);
    layout_->addWidget(nameLabel_);
    layout_->addWidget(descriptionLabel_);
    layout_->addWidget(buttonField_);
}

ElementDialog::ElementDialog() {
    setModal(true);

    auto layout = new QFormLayout(this);
    setLayout(layout);

    nameLabel_ = new QLabel("Name");
    desriptionLabel_ = new QLabel("Description");

    nameLineEdit_ = new QLineEdit();
    desriptionLineEdit_ = new QLineEdit();

    layout->addRow(nameLabel_, nameLineEdit_);
    layout->addRow(desriptionLabel_, desriptionLineEdit_);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    layout->addWidget(buttonBox);
}

AddElementDialog::AddElementDialog(QString& title) {
    title_ = title;
    setWindowTitle(title_);

    connect(this->buttonBox, &QDialogButtonBox::accepted, this, &AddElementDialog::sendData);
}

void AddElementDialog::sendData() {
    Manager* manager = Manager::instance();

    QString name = this->nameLineEdit_->text();
    QString description = this->desriptionLineEdit_->text();

    manager->createElement(name, description);
    this->close();
}

ResetElementDialog::ResetElementDialog(QString& title, Element* element) {
    title_ = title;
    setWindowTitle(title_);
    element_ = element;

    connect(this->buttonBox, &QDialogButtonBox::accepted, this, &ResetElementDialog::sendData);
}

void ResetElementDialog::sendData() {
    Manager* manager = Manager::instance();

    QString name = this->nameLineEdit_->text();
    QString description = this->desriptionLineEdit_->text();

    manager->setElement(element_, name, description);
    this->close();
}
