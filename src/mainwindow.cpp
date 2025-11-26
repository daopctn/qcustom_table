#include "mainwindow.h"
#include "actionbuttonsdelegate.h"
#include "infodialog.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include <QFont>
#include <QBrush>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_tableView(new QTableView(this))
    , m_model(new QStandardItemModel(this))
{
    setupTableView();
    populateTestData();

    // Set central widget
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
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

    // NEW APPROACH - Using delegate for action buttons
    // Create and set delegate for action buttons column
    m_delegate = new ActionButtonsDelegate(this);
    m_tableView->setItemDelegateForColumn(2, m_delegate);

    // OLD APPROACH - Used setIndexWidget (see populateTestData for old code)

    // Connect delegate's buttonClicked signal
    connect(m_delegate, &ActionButtonsDelegate::buttonClicked,
            this, &MainWindow::onButtonClicked);

    // Enable mouse tracking for hover effects
    m_tableView->setMouseTracking(true);

    // Configure table appearance
    m_tableView->horizontalHeader()->setStretchLastSection(true);
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableView->verticalHeader()->setVisible(false);

    // Set column widths
    m_tableView->setColumnWidth(0, 80);   // STT column
    m_tableView->setColumnWidth(1, 200);  // Tên column
}

void MainWindow::populateTestData()
{
    // Add header row (row 0)
    QList<QStandardItem*> headerItems;

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
    for (int i = 1; i <= 10; ++i) {
        QList<QStandardItem*> rowItems;

        // STT column
        QStandardItem *sttItem = new QStandardItem(QString::number(i));
        sttItem->setTextAlignment(Qt::AlignCenter);
        rowItems.append(sttItem);

        // Tên column
        QStandardItem *nameItem = new QStandardItem(QString("Item %1").arg(i));
        rowItems.append(nameItem);

        // Thao tác column (empty, delegate will handle rendering)
        QStandardItem *actionItem = new QStandardItem();
        actionItem->setFlags(actionItem->flags() & ~Qt::ItemIsEditable);
        rowItems.append(actionItem);

        m_model->appendRow(rowItems);

        // The delegate will handle rendering the buttons for this row

        // OLD APPROACH - Using setIndexWidget (kept for reference):
        // Create and set action buttons widget for this row
        // Row index in model = i (since row 0 is header)
        // ActionButtonsWidget *actionsWidget = new ActionButtonsWidget(i);
        // connect(actionsWidget, &ActionButtonsWidget::buttonClicked,
        //         this, &MainWindow::onButtonClicked);
        //
        // QModelIndex actionIndex = m_model->index(i, 2);
        // m_tableView->setIndexWidget(actionIndex, actionsWidget);
    }
}

void MainWindow::onButtonClicked(int row, int buttonIndex)
{
    // Row 0 is header, skip it
    if (row == 0) {
        return;
    }

    QString itemName = m_model->item(row, 1)->text();
    int dataRow = row - 1; // Adjust for header row
    qDebug() << "Button clicked on" << itemName << "- Data Row" << dataRow << "- Button" << buttonIndex;

    // Create and show modal dialog
    InfoDialog *dialog = new InfoDialog(row, buttonIndex, this);

    // Show modal dialog (blocks interaction until closed)
    dialog->exec();

    // When dialog closes (after exec returns), reset button state
    m_delegate->resetActiveState();
    m_tableView->update(m_model->index(row, 2));

    delete dialog;
}
