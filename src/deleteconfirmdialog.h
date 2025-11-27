#ifndef DELETECONFIRMDIALOG_H
#define DELETECONFIRMDIALOG_H

#include <QDialog>

class DeleteConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteConfirmDialog(const QString &itemName, QWidget *parent = nullptr);

    bool isConfirmed() const;

private:
    bool m_confirmed;
};

#endif // DELETECONFIRMDIALOG_H
