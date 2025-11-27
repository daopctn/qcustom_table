#include "editsavedialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

EditSaveDialog::EditSaveDialog(const QString &currentName, QWidget *parent)
    : QDialog(parent)
    , m_saved(false)
{
    setWindowTitle("Chỉnh sửa tên");
    setModal(true);
    setFixedSize(400, 140);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Prompt label
    QLabel *promptLabel = new QLabel(QString("Nhập tên mới cho '%1':").arg(currentName), this);
    mainLayout->addWidget(promptLabel);

    // Name input
    m_nameEdit = new QLineEdit(currentName, this);
    m_nameEdit->selectAll();
    mainLayout->addWidget(m_nameEdit);

    // Buttons layout
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);

    QPushButton *okButton = new QPushButton("OK", this);
    QPushButton *cancelButton = new QPushButton("Hủy", this);

    okButton->setMinimumWidth(80);
    cancelButton->setMinimumWidth(80);

    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(okButton);

    mainLayout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, [this, currentName]() {
        QString newName = m_nameEdit->text().trimmed();

        if (newName.isEmpty()) {
            reject();
            return;
        }

        if (newName == currentName) {
            reject();
            return;
        }

        // Save directly without confirmation
        m_newName = newName;
        m_saved = true;
        accept();
    });

    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString EditSaveDialog::getNewName() const
{
    return m_newName;
}

bool EditSaveDialog::isSaved() const
{
    return m_saved;
}
