#include <QFont>
#include <QFormLayout>
#include <QPushButton>
#include <QStyle>
#include <Qt>
#include <QVBoxLayout>

#include "customwidgets.h"

Element::Element() {
    name_ = "LampovayaDefault";
    description_ = "ip: default";
    setStructure();
}

Element::Element(QString& name, QString& description) :
    name_(name), description_(description) {
    setStructure();
};

bool Element::readIsPressed() {
    return this->isPressedValue;
}

void Element::writeIsPressed(bool value) {
    this->isPressedValue = value;
    emit isPresseChanged(this->isPressedValue);
}

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
    setAttribute(Qt::WA_StyledBackground);
    this->writeIsPressed(false);

    layout_ = new QVBoxLayout(this);
    this->setLayout(layout_);

    emptyLabel_ = new QLabel("stub for red dot");  // imitation for red dot field
    emptyLabel_->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    nameLabel_ = new QLabel(this->name_);
    nameLabel_->setAlignment(Qt::AlignCenter);
    auto font = new QFont;
    font->setBold(true);
    font->setPointSize(15);
    nameLabel_->setFont(*font);
    nameLabel_->setObjectName("nameLabel");

    descriptionLabel_ = new QLabel(this->description_);
    descriptionLabel_->setAlignment(Qt::AlignCenter);

    buttonFieldLayout_ = new QHBoxLayout(this);
    buttonFieldLayout_->setAlignment(Qt::AlignRight | Qt::AlignTop);
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

void Element::mousePressEvent(QMouseEvent* event) {
    this->setProperty("isPressed", true);

    style()->unpolish(this);
    style()->polish(this);

    QWidget::mousePressEvent(event);
}

void Element::mouseReleaseEvent(QMouseEvent* event) {
    this->setProperty("isPressed", false);

    style()->unpolish(this);
    style()->polish(this);

    QWidget::mouseReleaseEvent(event);
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
