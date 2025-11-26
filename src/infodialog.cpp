#include "infodialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>

InfoDialog::InfoDialog(int row, int buttonIndex, QWidget *parent)
    : QDialog(parent)
{
    // Make dialog frameless and modal
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, false);
    setModal(true);
    setFixedSize(400, 250);

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Custom title bar with red background
    QWidget *titleBar = new QWidget(this);
    titleBar->setObjectName("titleBar");
    titleBar->setFixedHeight(40);
    titleBar->setStyleSheet(
        "#titleBar {"
        "   background-color: #DC143C;"
        "}"
    );
    titleBar->setAutoFillBackground(true);

    QHBoxLayout *titleLayout = new QHBoxLayout(titleBar);
    titleLayout->setContentsMargins(10, 0, 10, 0);

    // Title label
    m_titleLabel = new QLabel("Button Click Info", titleBar);
    m_titleLabel->setStyleSheet("color: white; font-weight: bold; font-size: 14px;");

    // Close button (X)
    m_closeButton = new QPushButton("×", titleBar);
    m_closeButton->setFixedSize(30, 30);
    m_closeButton->setStyleSheet(
        "QPushButton {"
        "   background-color: transparent;"
        "   color: white;"
        "   font-size: 20px;"
        "   font-weight: bold;"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(255, 255, 255, 0.2);"
        "}"
        "QPushButton:pressed {"
        "   background-color: rgba(255, 255, 255, 0.3);"
        "}"
    );

    titleLayout->addWidget(m_titleLabel);
    titleLayout->addStretch();
    titleLayout->addWidget(m_closeButton);

    // Content area
    QWidget *contentWidget = new QWidget(this);
    contentWidget->setObjectName("contentArea");
    contentWidget->setStyleSheet(
        "#contentArea {"
        "   background-color: white;"
        "}"
    );
    contentWidget->setAutoFillBackground(true);
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(20, 30, 20, 30);

    // Create info label with button click information
    QString infoText = QString("Row %1 - Button %2 clicked")
                           .arg(row)
                           .arg(buttonIndex);

    m_infoLabel = new QLabel(infoText, contentWidget);
    m_infoLabel->setAlignment(Qt::AlignCenter);

    // Style the info label
    QFont font = m_infoLabel->font();
    font.setPointSize(12);
    m_infoLabel->setFont(font);

    // Create OK button
    m_okButton = new QPushButton("OK", contentWidget);
    m_okButton->setDefault(true);
    m_okButton->setMinimumWidth(100);
    m_okButton->setMinimumHeight(35);
    m_okButton->setStyleSheet(
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

    // Add widgets to content layout
    contentLayout->addWidget(m_infoLabel);
    contentLayout->addSpacing(20);
    contentLayout->addWidget(m_okButton, 0, Qt::AlignCenter);

    // Add title bar and content to main layout
    mainLayout->addWidget(titleBar);
    mainLayout->addWidget(contentWidget);

    // Connect buttons
    connect(m_closeButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(m_okButton, &QPushButton::clicked, this, &QDialog::accept);
}
