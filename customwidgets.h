#ifndef CUSTOMWIDGETS_H
#define CUSTOMWIDGETS_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QString>
#include <QWidget>

#include "manager.h"

class Element : public QWidget {

    Q_OBJECT

public:
    Element();
    Element(QString&, QString&);
    ~Element() = default;

    void setName(QString&);
    QString getName();
    void setDescription(QString&);
    QString getDescription();

    void edit();
    void remove();

    void print();

private:
    QString name_;
    QString description_;

    QVBoxLayout* layout_;
    QHBoxLayout* buttonFieldLayout_;
    QWidget* buttonField_;

    QLabel* emptyLabel_;
    QLabel* nameLabel_;
    QLabel* descriptionLabel_;

    QPushButton* editButton_;
    QPushButton* removeButton_;

    void setStructure();

};

class ElementDialog : public QDialog {

    Q_OBJECT

public:
    ElementDialog();
    ~ElementDialog() = default;

protected:
    QString title_;
    QDialogButtonBox* buttonBox;

    QLineEdit* nameLineEdit_;
    QLineEdit* desriptionLineEdit_;

private:
    QLabel* nameLabel_;
    QLabel* desriptionLabel_;
};

class AddElementDialog : public ElementDialog {

    Q_OBJECT

public:
    AddElementDialog(QString&);
    ~AddElementDialog() = default;

private:
    void sendData();
};

class ResetElementDialog : public ElementDialog {

    Q_OBJECT

public:
    ResetElementDialog(QString&, Element*);
    ~ResetElementDialog() = default;

private:
    Element* element_;
    void sendData();
};

#endif // CUSTOMWIDGETS_H
