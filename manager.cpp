#include "customwidgets.h"
#include "mainwindow.h"
#include "manager.h"

Manager* Manager::instance_ = nullptr;

Manager* Manager::instance() {
    if(instance_ == nullptr) {
        instance_ = new Manager();
    }
    return instance_;
}

Manager::Manager() {
    auto element = new Element();
    elements_.push_back(element);
    elements_.back()->setObjectName("element");
}

void Manager::fillElements(QLayout* layout) {
    for(auto& element : this->elements_) {
        element->print();
        layout->addWidget(element);
    }
    this->printElements();
}

void Manager::createElement(QString& name, QString& description) {
    elements_.push_back(new Element(name, description));
    elements_.back()->setObjectName("element");
    this->printElements();
}

void Manager::resetElement(Element* element) {
    QString title {"Reset element"};
    auto dialog = new ResetElementDialog(title, element);

    dialog->show();
}

void Manager::removeElement(Element* element) {
    // search for element in elements_
    for(auto it = this->elements_.begin(); it != this->elements_.end(); it++) {
        if(*it == element) {
            this->elements_.erase(it);
            return;
        }
    }
    // raise exception if element was not found
}

void Manager::setElement(Element* element, QString& name, QString& description) {
    // search for element in elements_
    for(auto& e : this->elements_) {
        if(e == element) {
            e->setName(name);
            e->setDescription(description);
            return;
        }
    }
    // raise exception if element was not found
}

void Manager::addElement() {
    QString title {"Add element"};
    auto dialog = new AddElementDialog(title);

    dialog->show();
}

void Manager::printElements() {
    for(auto& element : this->elements_) {
        element->print();
    }
}
