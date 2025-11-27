#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupTableView();
    void populateTestData();

private slots:
    void onDeleteRequested(int row);
    void onNameChanged(int row, const QString &newName);
    void onAddRowClicked();

private:
    QTableView *m_tableView;
    QStandardItemModel *m_model;
    QPushButton *m_addButton;
};

#endif // MAINWINDOW_H
