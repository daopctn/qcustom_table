#include "actionbuttonswidget.h"
#include "infodialog.h"
#include "deleteconfirmdialog.h"
#include "editsavedialog.h"
#include <QDebug>

ActionButtonsWidget::ActionButtonsWidget(int row, const QString &itemName, QWidget *parent)
    : QWidget(parent)
    , m_row(row)
    , m_itemName(itemName)
{
    qDebug() << "[MEMORY] ActionButtonsWidget CREATED - Row:" << row << "Name:" << itemName;

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(8, 4, 8, 4);
    layout->setSpacing(8);

    // Create buttons
    m_button1 = new QPushButton("Info", this);
    m_button2 = new QPushButton("Delete", this);
    m_button3 = new QPushButton("Edit", this);

    // Apply inline stylesheet - Info button (Blue)
    m_button1->setStyleSheet(
        "QPushButton {"
        "    background-color: #2196F3;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 6px 12px;"
        "    font-size: 11px;"
        "    font-weight: bold;"
        "    min-width: 60px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #1976D2;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #0D47A1;"
        "}"
    );

    // Apply inline stylesheet - Delete button (Red)
    m_button2->setStyleSheet(
        "QPushButton {"
        "    background-color: #DC143C;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 6px 12px;"
        "    font-size: 11px;"
        "    font-weight: bold;"
        "    min-width: 60px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #C41230;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #A01020;"
        "}"
    );

    // Apply inline stylesheet - Edit button (Green)
    m_button3->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 6px 12px;"
        "    font-size: 11px;"
        "    font-weight: bold;"
        "    min-width: 60px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45A049;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #2E7D32;"
        "}"
    );

    m_button1->setCursor(Qt::PointingHandCursor);
    m_button2->setCursor(Qt::PointingHandCursor);
    m_button3->setCursor(Qt::PointingHandCursor);

    layout->addStretch();
    layout->addWidget(m_button1);
    layout->addWidget(m_button2);
    layout->addWidget(m_button3);
    layout->addStretch();

    connect(m_button1, &QPushButton::clicked, this, &ActionButtonsWidget::onInfoButtonClicked);
    connect(m_button2, &QPushButton::clicked, this, &ActionButtonsWidget::onDeleteButtonClicked);
    connect(m_button3, &QPushButton::clicked, this, &ActionButtonsWidget::onEditButtonClicked);
}

ActionButtonsWidget::~ActionButtonsWidget()
{
    qDebug() << "[MEMORY] ActionButtonsWidget DESTROYED - Row:" << m_row << "Name:" << m_itemName;
}

void ActionButtonsWidget::onInfoButtonClicked()
{
    InfoDialog *dialog = new InfoDialog(m_row, 0, this);
    dialog->exec();
    delete dialog;
}

void ActionButtonsWidget::onDeleteButtonClicked()
{
    DeleteConfirmDialog *dialog = new DeleteConfirmDialog(m_itemName, this);
    dialog->exec();

    bool confirmed = dialog->isConfirmed();
    delete dialog;  // Delete dialog BEFORE emitting signal
    dialog = nullptr;  // Prevent dangling pointer

    if (confirmed) {
        emit deleteRequested(m_row);  // This schedules THIS widget for deletion
        // WARNING: Don't access any member variables after this point!
    }
}

void ActionButtonsWidget::onEditButtonClicked()
{
    EditSaveDialog *dialog = new EditSaveDialog(m_itemName, this);
    dialog->exec();

    bool saved = dialog->isSaved();
    QString newName;
    if (saved) {
        newName = dialog->getNewName();
    }
    delete dialog;  // Delete dialog BEFORE emitting signal
    dialog = nullptr;  // Prevent dangling pointer

    if (saved) {
        m_itemName = newName;  // Update local copy
        emit nameChanged(m_row, newName);
    }
}
