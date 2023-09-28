#ifndef WIDGET_H
#define WIDGET_H

#include<QWidget>
#include<QProcess>
#include<QMessageBox>
#include<QScrollBar>
#include<analyse_1.h>
#include<QDebug>
#include<QPushButton>

#include<QFileDialog>
#include<QTextStream>
#include<QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();



private slots:
    void on_commitButton_clicked();
    void on_cancelButton_clicked();
    void on_resetButton_clicked();
    void openButton_clicked();

private:
    Ui::Widget *ui;
    Analyse_1 aa;
};
#endif // WIDGET_H
