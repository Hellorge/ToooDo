#pragma once

#include <QObject>
#include <QPushButton>
#include <QMap>
#include <QString>

class SvgIconManager : public QObject {
    Q_OBJECT

public:
    SvgIconManager(QObject *parent = nullptr);

    void addButton(QPushButton *button, QString *svgPath);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void updateIcon(QPushButton *button);

    QMap<QPushButton *, QString> m_buttonSvgMap;
};
