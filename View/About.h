#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

class QVBoxLayout;

class About : public QDialog
{
    Q_OBJECT
public:
    explicit About(QWidget *parent);

private:
    QVBoxLayout *mainVLayout;

    void initTopUi();
    void initBottomUi();
};

#endif // ABOUT_H
