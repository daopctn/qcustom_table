#ifndef ACTIONBUTTONSWIDGET_H
#define ACTIONBUTTONSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QIcon>

class HoverButton : public QPushButton
{
    Q_OBJECT

public:
    explicit HoverButton(const QIcon &normalIcon, const QIcon &hoverIcon, QWidget *parent = nullptr);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    QIcon m_normalIcon;
    QIcon m_hoverIcon;
};

class ActionButtonsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ActionButtonsWidget(int row, QWidget *parent = nullptr);

signals:
    void buttonClicked(int row, int buttonIndex);

private slots:
    void onButton1Clicked();
    void onButton2Clicked();
    void onButton3Clicked();

private:
    int m_row;
    HoverButton *m_button1;
    HoverButton *m_button2;
    HoverButton *m_button3;
};

#endif // ACTIONBUTTONSWIDGET_H
