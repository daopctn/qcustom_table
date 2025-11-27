#ifndef ACTIONBUTTONSWIDGET_H
#define ACTIONBUTTONSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class ActionButtonsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ActionButtonsWidget(int row, const QString &itemName, QWidget *parent = nullptr);
    ~ActionButtonsWidget();

signals:
    void deleteRequested(int row);
    void nameChanged(int row, const QString &newName);

private slots:
    void onInfoButtonClicked();
    void onDeleteButtonClicked();
    void onEditButtonClicked();

private:
    int m_row;
    QString m_itemName;
    QPushButton *m_button1;
    QPushButton *m_button2;
    QPushButton *m_button3;
};

#endif // ACTIONBUTTONSWIDGET_H
