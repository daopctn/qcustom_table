#include "actionbuttonsdelegate.h"
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QAbstractItemView>
#include <QDebug>

ActionButtonsDelegate::ActionButtonsDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
    , m_activeButton(-1)
    , m_hoverButton(-1)
{
    // Load icon resources
    m_icon1Normal = QIcon(":/instagram.png");
    m_icon1Active = QIcon(":/facebook.png");
    m_icon2Normal = QIcon(":/whatsapp.png");
    m_icon2Active = QIcon(":/twitter.png");
    m_icon3Normal = QIcon(":/youtube.png");
    m_icon3Active = QIcon(":/linkedin.png");
}

void ActionButtonsDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const
{
    // Paint default background
    QStyledItemDelegate::paint(painter, option, index);

    // Enable antialiasing for smoother rendering
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);

    // Draw the 3 buttons
    for (int i = 0; i < 3; ++i) {
        QRect buttonRect = getButtonRect(option, i);

        // Determine if this button is active or hovered
        bool isActive = (m_activeIndex.isValid() &&
                        m_activeIndex == index &&
                        m_activeButton == i);
        bool isHovered = (m_hoverIndex.isValid() &&
                         m_hoverIndex == index &&
                         m_hoverButton == i);

        // Get the appropriate icon
        QIcon icon = getIconForButton(i, isActive, isHovered);

        // Draw the icon
        QPixmap pixmap = icon.pixmap(QSize(BUTTON_SIZE, BUTTON_SIZE));
        painter->drawPixmap(buttonRect, pixmap);
    }
}

bool ActionButtonsDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index)
{
    if (!index.isValid()) {
        return QStyledItemDelegate::editorEvent(event, model, option, index);
    }

    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

    if (event->type() == QEvent::MouseMove) {
        // Update hover state
        int buttonIndex = getButtonAtPosition(option, mouseEvent->pos());

        if (buttonIndex != m_hoverButton || index != m_hoverIndex) {
            m_hoverIndex = index;
            m_hoverButton = buttonIndex;

            // Trigger repaint
            QAbstractItemView *view = qobject_cast<QAbstractItemView*>(
                const_cast<QWidget*>(option.widget));
            if (view) {
                view->update(index);
            }
        }
        return true;
    }
    else if (event->type() == QEvent::MouseButtonPress) {
        // Check if click is on a button
        int buttonIndex = getButtonAtPosition(option, mouseEvent->pos());

        if (buttonIndex >= 0) {
            // Set this button as active
            m_activeIndex = QPersistentModelIndex(index);
            m_activeButton = buttonIndex;

            // Trigger repaint
            QAbstractItemView *view = qobject_cast<QAbstractItemView*>(
                const_cast<QWidget*>(option.widget));
            if (view) {
                view->update(index);
            }

            // Emit signal
            emit buttonClicked(index.row(), buttonIndex);
            return true;
        }
    }
    else if (event->type() == QEvent::Leave) {
        // Clear hover state when mouse leaves
        if (m_hoverIndex == index) {
            m_hoverIndex = QModelIndex();
            m_hoverButton = -1;

            // Trigger repaint
            QAbstractItemView *view = qobject_cast<QAbstractItemView*>(
                const_cast<QWidget*>(option.widget));
            if (view) {
                view->update(index);
            }
        }
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

QSize ActionButtonsDelegate::sizeHint(const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    // Return appropriate height for buttons
    return QSize(0, ROW_HEIGHT);
}

void ActionButtonsDelegate::resetActiveState()
{
    m_activeIndex = QPersistentModelIndex();
    m_activeButton = -1;
}

QRect ActionButtonsDelegate::getButtonRect(const QStyleOptionViewItem &option, int buttonIndex) const
{
    // Calculate total width of all buttons
    int totalWidth = (BUTTON_SIZE * 3) + (BUTTON_SPACING * 2);

    // Calculate starting X position (centered)
    int startX = option.rect.x() + (option.rect.width() - totalWidth) / 2;

    // Calculate Y position (centered vertically)
    int startY = option.rect.y() + (option.rect.height() - BUTTON_SIZE) / 2;

    // Calculate X position for this button
    int x = startX + buttonIndex * (BUTTON_SIZE + BUTTON_SPACING);

    return QRect(x, startY, BUTTON_SIZE, BUTTON_SIZE);
}

QRect ActionButtonsDelegate::getButton1Rect(const QStyleOptionViewItem &option) const
{
    return getButtonRect(option, 0);
}

QRect ActionButtonsDelegate::getButton2Rect(const QStyleOptionViewItem &option) const
{
    return getButtonRect(option, 1);
}

QRect ActionButtonsDelegate::getButton3Rect(const QStyleOptionViewItem &option) const
{
    return getButtonRect(option, 2);
}

int ActionButtonsDelegate::getButtonAtPosition(const QStyleOptionViewItem &option, const QPoint &pos) const
{
    for (int i = 0; i < 3; ++i) {
        QRect buttonRect = getButtonRect(option, i);
        if (buttonRect.contains(pos)) {
            return i;
        }
    }
    return -1;  // No button at this position
}

QIcon ActionButtonsDelegate::getIconForButton(int buttonIndex, bool isActive, bool isHovered) const
{
    Q_UNUSED(isHovered);  // Don't change icon on hover, only when active

    // Only use active icon when button is actually active (clicked)
    switch (buttonIndex) {
        case 0:
            return isActive ? m_icon1Active : m_icon1Normal;
        case 1:
            return isActive ? m_icon2Active : m_icon2Normal;
        case 2:
            return isActive ? m_icon3Active : m_icon3Normal;
        default:
            return QIcon();
    }
}
