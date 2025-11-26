#ifndef ACTIONBUTTONSDELEGATE_H
#define ACTIONBUTTONSDELEGATE_H

#include <QStyledItemDelegate>
#include <QIcon>
#include <QPersistentModelIndex>
#include <QModelIndex>

class ActionButtonsDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ActionButtonsDelegate(QObject *parent = nullptr);

    // Override painting
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    // Override event handling
    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) override;

    // Size hint for proper row height
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

    // Public method to reset active state (called from MainWindow after dialog closes)
    void resetActiveState();

signals:
    void buttonClicked(int row, int buttonIndex);

private:
    // Helper methods to calculate button rectangles
    QRect getButtonRect(const QStyleOptionViewItem &option, int buttonIndex) const;
    QRect getButton1Rect(const QStyleOptionViewItem &option) const;
    QRect getButton2Rect(const QStyleOptionViewItem &option) const;
    QRect getButton3Rect(const QStyleOptionViewItem &option) const;

    // Determine which button (if any) is at a given position
    int getButtonAtPosition(const QStyleOptionViewItem &option, const QPoint &pos) const;

    // Get the appropriate icon for a button based on its state
    QIcon getIconForButton(int buttonIndex, bool isActive, bool isHovered) const;

private:
    // Button state tracking
    QPersistentModelIndex m_activeIndex;  // Which cell has the active button
    int m_activeButton;                    // Which button (0-2) is active, -1 if none

    QModelIndex m_hoverIndex;              // Which cell is currently hovered
    int m_hoverButton;                     // Which button is hovered, -1 if none

    // Icon resources
    QIcon m_icon1Normal;   // Instagram
    QIcon m_icon1Active;   // Facebook
    QIcon m_icon2Normal;   // WhatsApp
    QIcon m_icon2Active;   // Twitter
    QIcon m_icon3Normal;   // YouTube
    QIcon m_icon3Active;   // LinkedIn

    // Layout constants
    static const int BUTTON_SIZE = 24;
    static const int BUTTON_SPACING = 8;
    static const int ROW_HEIGHT = 32;
};

#endif // ACTIONBUTTONSDELEGATE_H
