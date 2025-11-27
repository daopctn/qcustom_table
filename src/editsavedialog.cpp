#include "editsavedialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

EditSaveDialog::EditSaveDialog(const QString &currentName, QWidget *parent)
    : QDialog(parent)
    , m_saved(false)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setModal(true);
    setFixedSize(400, 170);

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

    // Prompt label
    QLabel *promptLabel = new QLabel(QString("Nhập tên mới cho '%1':").arg(currentName), contentWidget);
    contentLayout->addWidget(promptLabel);

    // Name input
    m_nameEdit = new QLineEdit(currentName, contentWidget);
    m_nameEdit->selectAll();
    contentLayout->addWidget(m_nameEdit);

    // Buttons layout
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);

    QPushButton *okButton = new QPushButton("OK", contentWidget);
    QPushButton *cancelButton = new QPushButton("Hủy", contentWidget);

    okButton->setMinimumWidth(80);
    okButton->setMinimumHeight(32);
    okButton->setStyleSheet(
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

    cancelButton->setMinimumWidth(80);
    cancelButton->setMinimumHeight(32);
    cancelButton->setStyleSheet(
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
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(okButton);
    buttonLayout->addStretch();

    contentLayout->addLayout(buttonLayout);
    mainLayout->addWidget(contentWidget);

    connect(closeButton, &QPushButton::clicked, this, &QDialog::reject);

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
