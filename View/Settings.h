#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

class QVBoxLayout;

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
