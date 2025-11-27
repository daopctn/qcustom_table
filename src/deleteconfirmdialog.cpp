#include "deleteconfirmdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

DeleteConfirmDialog::DeleteConfirmDialog(const QString &itemName, QWidget *parent)
    : QDialog(parent)
    , m_confirmed(false)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setModal(true);
    setFixedSize(350, 150);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Title bar with close button
    QWidget *titleBar = new QWidget(this);
    titleBar->setFixedHeight(35);
    titleBar->setStyleSheet("background-color: #f0f0f0; border-bottom: 1px solid #ccc;");

    QHBoxLayout *titleLayout = new QHBoxLayout(titleBar);
    titleLayout->setContentsMargins(10, 0, 5, 0);

    titleLayout->addStretch();

    // Close button (X)
    QPushButton *closeButton = new QPushButton("×", titleBar);
    closeButton->setFixedSize(25, 25);
    closeButton->setStyleSheet(
        "QPushButton {"
        "   background-color: transparent;"
        "   color: #666;"
        "   font-size: 18px;"
        "   font-weight: bold;"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "   background-color: #e81123;"
        "   color: white;"
        "}"
    );
    titleLayout->addWidget(closeButton);

    mainLayout->addWidget(titleBar);

    // Content area
    QWidget *contentWidget = new QWidget(this);
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setSpacing(15);
    contentLayout->setContentsMargins(20, 20, 20, 20);

    // Message label
    QLabel *messageLabel = new QLabel(QString("Bạn có chắc chắn muốn xóa '%1' không?").arg(itemName), contentWidget);
    messageLabel->setWordWrap(true);
    contentLayout->addWidget(messageLabel);

    // Buttons layout
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);

    QPushButton *yesButton = new QPushButton("Có", contentWidget);
    QPushButton *noButton = new QPushButton("Không", contentWidget);

    yesButton->setMinimumWidth(80);
    yesButton->setMinimumHeight(32);
    yesButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #DC143C;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-size: 12px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #C41230;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #A01020;"
        "}"
    );

    noButton->setMinimumWidth(80);
    noButton->setMinimumHeight(32);
    noButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #6c757d;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-size: 12px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #5a6268;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #4e555b;"
        "}"
    );

    buttonLayout->addStretch();
    buttonLayout->addWidget(noButton);
    buttonLayout->addWidget(yesButton);
    buttonLayout->addStretch();

    contentLayout->addLayout(buttonLayout);
    mainLayout->addWidget(contentWidget);

    connect(closeButton, &QPushButton::clicked, this, [this]() {
        m_confirmed = false;
        reject();
    });

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
