#include "svgmanager.h"
#include <QSvgRenderer>
#include <QPainter>
#include <QFile>
#include <QPalette>
#include <QIcon>
#include <QBuffer>
#include <QEvent>
#include <QDebug>

SvgIconManager::SvgIconManager(QObject *parent)
    : QObject(parent) {}

void SvgIconManager::addButton(QPushButton *button, QString *svgPath) {
    if (!button) return;

    m_buttonSvgMap[button] = svgPath;
    updateIcon(button);

    // Install event filter on the button to catch palette change events
    button->installEventFilter(this);
}

bool SvgIconManager::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::PaletteChange) {
        QPushButton *button = qobject_cast<QPushButton *>(watched);
        if (button && m_buttonSvgMap.contains(button)) {
            updateIcon(button);
        }
    }
    return QObject::eventFilter(watched, event);
}

void SvgIconManager::updateIcon(QPushButton *button) {
    QString svgPath = m_buttonSvgMap.value(button);
    if (svgPath.isEmpty()) return;

    QColor color = button->palette().color(QPalette::ButtonText);

    QByteArray svgData;
    QFile file(svgPath);
    if (file.open(QIODevice::ReadOnly)) {
        svgData = file.readAll();
        file.close();
    }

    QString svgContent(svgData);
    svgContent.replace("#000000", color.name(QColor::HexRgb));

    QSvgRenderer svgRenderer(svgContent.toUtf8());

    QSize iconSize = button->iconSize();
    QPixmap pixmap(iconSize);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    svgRenderer.render(&painter);

    button->setIcon(QIcon(pixmap));
}
