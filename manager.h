#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <QLayout>
#include <QObject>
#include "customwidgets.h"

class Element; // TODO remove

class Manager : public QObject {

    Q_OBJECT

public:
    static Manager* instance();

    void fillElements(QLayout*);
    void createElement(QString&, QString&);
    void resetElement(Element*);
    void removeElement(Element*);
    void setElement(Element*, QString&, QString&);

    ~Manager() = default;

    void printElements();

private:
    static Manager* instance_;

    Manager();

    std::vector<Element*> elements_;

public slots:
    void addElement();

};

#endif // MANAGER_H
