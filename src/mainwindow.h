#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>

class ActionButtonsDelegate;

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
    void onButtonClicked(int row, int buttonIndex);

private:
    QTableView *m_tableView;
    QStandardItemModel *m_model;
    ActionButtonsDelegate *m_delegate;
};

#endif // MAINWINDOW_H
