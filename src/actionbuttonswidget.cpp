#include "actionbuttonswidget.h"
#include <QDebug>
#include <QEvent>

// HoverButton implementation
HoverButton::HoverButton(const QIcon &normalIcon, const QIcon &hoverIcon, QWidget *parent)
    : QPushButton(parent)
    , m_normalIcon(normalIcon)
    , m_hoverIcon(hoverIcon)
{
    setIcon(m_normalIcon);
    setFixedSize(24, 24);
    setIconSize(QSize(24, 24));
    setFlat(true);
}

void HoverButton::enterEvent(QEvent *event)
{
    setIcon(m_hoverIcon);
    QPushButton::enterEvent(event);
}

void HoverButton::leaveEvent(QEvent *event)
{
    setIcon(m_normalIcon);
    QPushButton::leaveEvent(event);
}

// ActionButtonsWidget implementation
ActionButtonsWidget::ActionButtonsWidget(int row, QWidget *parent)
    : QWidget(parent)
    , m_row(row)
{
    // Create horizontal layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(8, 4, 8, 4);
    layout->setSpacing(8);

    // Create 3 hover buttons with normal and hover icons
    // Button 1: Instagram (normal) → Facebook (hover)
    m_button1 = new HoverButton(QIcon(":/instagram.png"), QIcon(":/facebook.png"), this);

    // Button 2: WhatsApp (normal) → Twitter (hover)
    m_button2 = new HoverButton(QIcon(":/whatsapp.png"), QIcon(":/twitter.png"), this);

    // Button 3: YouTube (normal) → LinkedIn (hover)
    m_button3 = new HoverButton(QIcon(":/youtube.png"), QIcon(":/linkedin.png"), this);

    // Add buttons to layout with stretch to center them
    layout->addStretch();
    layout->addWidget(m_button1);
    layout->addWidget(m_button2);
    layout->addWidget(m_button3);
    layout->addStretch();

    // Connect signals
    connect(m_button1, &QPushButton::clicked, this, &ActionButtonsWidget::onButton1Clicked);
    connect(m_button2, &QPushButton::clicked, this, &ActionButtonsWidget::onButton2Clicked);
    connect(m_button3, &QPushButton::clicked, this, &ActionButtonsWidget::onButton3Clicked);
}

void ActionButtonsWidget::onButton1Clicked()
{
    qDebug() << "Row" << m_row << "- Button 0";
    emit buttonClicked(m_row, 0);
}

void ActionButtonsWidget::onButton2Clicked()
{
    qDebug() << "Row" << m_row << "- Button 1";
    emit buttonClicked(m_row, 1);
}

void ActionButtonsWidget::onButton3Clicked()
{
    qDebug() << "Row" << m_row << "- Button 2";
    emit buttonClicked(m_row, 2);
}
