#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QMainWindow>
#include <QVBoxLayout>

//QT_BEGIN_NAMESPACE
//namespace Ui { class MainWindow; }
//QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow* instance();

    QHBoxLayout* getBottomHorizontalLayout() const;

    void refreshElements();

    ~MainWindow();

private:
//    Ui::MainWindow *ui;
    static MainWindow* instance_;

    QWidget* mainWidget;
    QWidget* buttons;
    QWidget* elements;

    QVBoxLayout* verticalLayout;
    QHBoxLayout* topHorizontalLayout;
    QHBoxLayout* bottomHorizontalLayout;

    MainWindow(QWidget *parent = nullptr);

    void set();

    void setButtons();
    void setElements();

};

#endif // MAINWINDOW_H
