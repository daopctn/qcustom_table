#include "mainwindow.h"
#include "actionbuttonswidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include <QFont>
#include <QBrush>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_tableView(new QTableView(this)), m_model(new QStandardItemModel(this)), m_addButton(new QPushButton("Add Row", this))
{
    setupTableView();
    populateTestData();

    // Create add button with styling
    m_addButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 8px 16px;"
        "    font-size: 12px;"
        "    font-weight: bold;"
        "    min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45A049;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #2E7D32;"
        "}");
    m_addButton->setCursor(Qt::PointingHandCursor);
    connect(m_addButton, &QPushButton::clicked, this, &MainWindow::onAddRowClicked);

    // Set central widget
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Add button at top
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_addButton);
    buttonLayout->addStretch();
    layout->addLayout(buttonLayout);

    // Add table
    layout->addWidget(m_tableView);
    setCentralWidget(centralWidget);

    setWindowTitle("Qt Custom Table with Button Delegate");
    resize(600, 400);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupTableView()
{
    // Setup model with 3 columns
    m_model->setColumnCount(3);

    // Setup table view
    m_tableView->setModel(m_model);

    // Hide horizontal header (we'll use row 0 as header)
    m_tableView->horizontalHeader()->setVisible(false);

    // Configure table appearance
    m_tableView->horizontalHeader()->setStretchLastSection(true);
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableView->verticalHeader()->setVisible(false);

    // Set column widths
    m_tableView->setColumnWidth(0, 80);  // STT column
    m_tableView->setColumnWidth(1, 200); // Tên column
}

void MainWindow::populateTestData()
{
    // Add header row (row 0)
    QList<QStandardItem *> headerItems;

    QFont headerFont;
    headerFont.setBold(true);
    headerFont.setPointSize(10);

    QBrush headerBrush(QColor(230, 230, 230));

    // Header: STT
    QStandardItem *headerSTT = new QStandardItem("STT");
    headerSTT->setTextAlignment(Qt::AlignCenter);
    headerSTT->setFont(headerFont);
    headerSTT->setBackground(headerBrush);
    headerSTT->setFlags(headerSTT->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
    headerItems.append(headerSTT);

    // Header: Tên
    QStandardItem *headerName = new QStandardItem("Tên");
    headerName->setFont(headerFont);
    headerName->setBackground(headerBrush);
    headerName->setFlags(headerName->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
    headerItems.append(headerName);

    // Header: Thao tác
    QStandardItem *headerAction = new QStandardItem("Thao tác");
    headerAction->setTextAlignment(Qt::AlignCenter);
    headerAction->setFont(headerFont);
    headerAction->setBackground(headerBrush);
    headerAction->setFlags(headerAction->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
    headerItems.append(headerAction);

    m_model->appendRow(headerItems);

    // Add 10 test data rows (rows 1-10)
    for (int i = 1; i <= 10; ++i)
    {
        QList<QStandardItem *> rowItems;

        // STT column
        QStandardItem *sttItem = new QStandardItem(QString::number(i));
        sttItem->setTextAlignment(Qt::AlignCenter);
        rowItems.append(sttItem);

        // Tên column
        QStandardItem *nameItem = new QStandardItem(QString("Item %1").arg(i));
        rowItems.append(nameItem);

        // Thao tác column
        QStandardItem *actionItem = new QStandardItem();
        actionItem->setFlags(actionItem->flags() & ~Qt::ItemIsEditable);
        rowItems.append(actionItem);

        m_model->appendRow(rowItems);

        // Create widget-based buttons with item name
        QString itemName = QString("Item %1").arg(i);
        ActionButtonsWidget *actionsWidget = new ActionButtonsWidget(i, itemName, this);
        connect(actionsWidget, &ActionButtonsWidget::deleteRequested,
                this, &MainWindow::onDeleteRequested);
        connect(actionsWidget, &ActionButtonsWidget::nameChanged,
                this, &MainWindow::onNameChanged);

        QModelIndex actionIndex = m_model->index(i, 2);
        m_tableView->setIndexWidget(actionIndex, actionsWidget);
    }
}

void MainWindow::onDeleteRequested(int row)
{
    // Get widget from last column (column 2) of the row to be deleted
    // QModelIndex actionIndex = m_model->index(row, 2);
    // QWidget *widgetToDelete = m_tableView->indexWidget(actionIndex);

    // qDebug() << "Widget at row" << row << "before delete:" << widgetToDelete;
    // delete widgetToDelete;
    // widgetToDelete = nullptr;

    m_model->removeRow(row);

    // Update row numbers and widgets for remaining rows
    for (int i = row; i < m_model->rowCount(); ++i)
    {
        // Update STT display
        m_model->item(i, 0)->setText(QString::number(i));

        QModelIndex actionIndex = m_model->index(i, 2);

        // Recreate widget with updated row number
        // Note: setIndexWidget() will automatically delete the old widget
        QString itemName = m_model->item(i, 1)->text();
        ActionButtonsWidget *newWidget = new ActionButtonsWidget(i, itemName, this);
        connect(newWidget, &ActionButtonsWidget::deleteRequested,
                this, &MainWindow::onDeleteRequested);
        connect(newWidget, &ActionButtonsWidget::nameChanged,
                this, &MainWindow::onNameChanged);
        m_tableView->setIndexWidget(actionIndex, newWidget);
    }

    qDebug() << "Row" << row << "deleted";
}

void MainWindow::onNameChanged(int row, const QString &newName)
{
    m_model->item(row, 1)->setText(newName);
    qDebug() << "Row" << row << "name changed to:" << newName;
}

void MainWindow::onAddRowClicked()
{
    int newRowIndex = m_model->rowCount();

    QList<QStandardItem *> rowItems;

    // STT column
    QStandardItem *sttItem = new QStandardItem(QString::number(newRowIndex));
    sttItem->setTextAlignment(Qt::AlignCenter);
    rowItems.append(sttItem);

    // Tên column
    QString itemName = QString("Item %1").arg(newRowIndex);
    QStandardItem *nameItem = new QStandardItem(itemName);
    rowItems.append(nameItem);

    // Thao tác column
    QStandardItem *actionItem = new QStandardItem();
    actionItem->setFlags(actionItem->flags() & ~Qt::ItemIsEditable);
    rowItems.append(actionItem);

    m_model->appendRow(rowItems);

    // Create widget-based buttons with item name
    ActionButtonsWidget *actionsWidget = new ActionButtonsWidget(newRowIndex, itemName, this);
    connect(actionsWidget, &ActionButtonsWidget::deleteRequested,
            this, &MainWindow::onDeleteRequested);
    connect(actionsWidget, &ActionButtonsWidget::nameChanged,
            this, &MainWindow::onNameChanged);

    QModelIndex actionIndex = m_model->index(newRowIndex, 2);
    m_tableView->setIndexWidget(actionIndex, actionsWidget);

    qDebug() << "New row added:" << newRowIndex;
}
