#ifndef CLIENTDIALOG_H
#define CLIENTDIALOG_H

#include <QDialog>

class ClientDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ClientDialog(QWidget* parent);
    ~ClientDialog();

private:
    void initUI();

protected:
    void closeEvent(QCloseEvent* event) override;

};

#endif // CLIENTDIALOG_H
