#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
QT_END_NAMESPACE

class Settings : public QDialog
{
    Q_OBJECT
public:
    explicit Settings(QWidget* parent);

private:
    void initBottomUI();

private:
    QVBoxLayout* mainVLayout;
};

#endif // SETTINGS_H
