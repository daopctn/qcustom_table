#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(int row, int buttonIndex, QWidget *parent = nullptr);

private:
    QLabel *m_titleLabel;
    QPushButton *m_closeButton;
    QLabel *m_infoLabel;
    QPushButton *m_okButton;
};

#endif // INFODIALOG_H
