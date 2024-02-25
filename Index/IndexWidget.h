#ifndef INDEXWIDGET_H
#define INDEXWIDGET_H

#include <QWidget>
#include <QPushButton>

class IndexWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IndexWidget(QWidget* parent);

private:
    void initUI();
    void initSettings();
    QWidget* initLeftWidget();
private:
    //按钮无背景
    const QString left_btn_no_background = ".QPushButton {color:rgb(255,255,255);font-size:15px;border:1px solid rgb(76,76,76); border-radius: 3px;padding: 2px;}\
                                               .QPushButton:hover {background-color: rgb(53,53,53);}\
        .QPushButton:focus{outline: none;}";
    //按钮无背景-选中
    const QString left_btn_no_background_selected = ".QPushButton {color:rgb(221,58,95);background-color: rgb(53,53,53);font-size:15px;border:1px solid rgb(76,76,76); border-radius: 3px;padding: 2px;}\
          .QPushButton:focus{outline: none;}";

    QPushButton* vnServerBtn;
    QPushButton* vnClientBtn;
    QPushButton* recordBtn;

};

#endif // INDEXWIDGET_H
