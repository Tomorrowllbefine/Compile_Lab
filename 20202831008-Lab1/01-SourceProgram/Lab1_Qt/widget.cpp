#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(680,600);

    // 连接 取消按键后退出
    connect(ui->cancelButton, &QPushButton::clicked, this, &Widget::on_cancelButton_clicked);

    // 连接 重置按键后清空输入框
    connect(ui->resetButton, &QPushButton::clicked, this, &Widget::on_resetButton_clicked);

    // 连接按钮点击事件到槽函数
    connect(ui->openButton, &QPushButton::clicked, this, &Widget::openButton_clicked);

}

Widget::~Widget()
{
    delete ui;
}



/**
 * 提交按钮
 * @brief Widget::on_commitButton_clicked
 */
void Widget::on_commitButton_clicked()
{

    ui->OutputTextEdit->clear();
    // 获取InputTextEdit
    QString text =  ui->InputTextEdit->toPlainText();   // 第一种写法：在槽中获取信号

    // 分割
    QStringList lines = text.split("\n");

    // 遍历每一行并进行处理
    for(QString line : lines){
        qDebug().noquote() <<"原语句: " << line;

        // 词法分析
        std::string ans = aa.analyse(line.toStdString());
        qDebug()<<"词法分析后内容是: "<<ans;
        QString qstr = QString::fromStdString(ans);
        qDebug().noquote()<<"转换类型后内容是: "<<qstr;
        // 输出
        ui->OutputTextEdit->append(qstr);
    }
}

/**
 * 退出
 * @brief Widget::on_cancelButton_clicked
 */
void Widget::on_cancelButton_clicked()
{
    this->close();
}

/**
 * 清空输入框和输出框
 * @brief Widget::on_resetButton_clicked
 */
void Widget::on_resetButton_clicked()
{
    // 清空输入框
    ui->InputTextEdit->clear();
    // 清空输出框
    ui->OutputTextEdit->clear();
}


void Widget::openButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "选择文件", "", "Files (*.cpp *.txt)");

    if (!filePath.isEmpty()) {
        // 打开用户选择的CPP文件
        QFile file(filePath);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString fileContent;

            // 逐行读取文件内容
            while (!in.atEnd()) {
                QString line = in.readLine();
                fileContent += line + "\n"; // 添加换行符
            }

            // 将文件内容显示在文本框中
            ui->InputTextEdit->setPlainText(fileContent);

            file.close();
        } else {
            ui->InputTextEdit->setPlainText("无法打开文件");
        }
    }
}
