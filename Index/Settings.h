#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QStackedWidget;
QT_END_NAMESPACE

class Settings : public QDialog
{
    Q_OBJECT
public:
    explicit Settings(QWidget* parent);

private:
    void initUI();
    QWidget* initLeftWidget();
    QWidget* initRightWidget();

    void initCommonWidget();

private:
    QStackedWidget* rightStackedWidget;
};

#endif // SETTINGS_H
