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
    Q_PROPERTY(bool isPressed READ readIsPressed WRITE writeIsPressed NOTIFY isPresseChanged)

signals:
    void isPresseChanged(bool);

public:
    Element();
    Element(QString&, QString&);
    ~Element() = default;

    bool readIsPressed() const;
    void writeIsPressed(bool);

    void setName(QString&);
    QString getName() const;
    void setDescription(QString&);
    QString getDescription() const;

    void edit();
    void remove();

    void print() const;

private:
    bool isPressedValue;

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
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

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
