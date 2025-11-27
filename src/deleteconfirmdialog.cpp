#include "deleteconfirmdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

DeleteConfirmDialog::DeleteConfirmDialog(const QString &itemName, QWidget *parent)
    : QDialog(parent)
    , m_confirmed(false)
{
    setWindowTitle("Xác nhận xóa");
    setModal(true);
    setFixedSize(350, 120);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Message label
    QLabel *messageLabel = new QLabel(QString("Bạn có chắc chắn muốn xóa '%1' không?").arg(itemName), this);
    messageLabel->setWordWrap(true);
    mainLayout->addWidget(messageLabel);

    // Buttons layout
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);

    QPushButton *yesButton = new QPushButton("Có", this);
    QPushButton *noButton = new QPushButton("Không", this);

    yesButton->setMinimumWidth(80);
    noButton->setMinimumWidth(80);

    buttonLayout->addStretch();
    buttonLayout->addWidget(noButton);
    buttonLayout->addWidget(yesButton);

    mainLayout->addLayout(buttonLayout);

    connect(yesButton, &QPushButton::clicked, this, [this]() {
        m_confirmed = true;
        accept();
    });

    connect(noButton, &QPushButton::clicked, this, [this]() {
        m_confirmed = false;
        reject();
    });
}

bool DeleteConfirmDialog::isConfirmed() const
{
    return m_confirmed;
}
