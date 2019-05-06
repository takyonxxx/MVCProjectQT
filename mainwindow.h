#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtGui>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void populateDataItem();

public slots:
    void addnew();
    void remove();
    void save();

private:

    QSqlTableModel *model;
    QSqlDatabase db;

    bool initDatabase();
    void closeDatabase();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
