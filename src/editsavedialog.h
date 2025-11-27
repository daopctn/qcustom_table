#ifndef EDITSAVEDIALOG_H
#define EDITSAVEDIALOG_H

#include <QDialog>
#include <QLineEdit>

class EditSaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditSaveDialog(const QString &currentName, QWidget *parent = nullptr);

    QString getNewName() const;
    bool isSaved() const;

private:
    QLineEdit *m_nameEdit;
    QString m_newName;
    bool m_saved;
};

#endif // EDITSAVEDIALOG_H
