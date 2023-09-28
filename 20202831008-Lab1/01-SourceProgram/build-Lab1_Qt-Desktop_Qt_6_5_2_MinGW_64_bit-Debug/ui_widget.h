/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *infoLabel;
    QSpacerItem *horizontalSpacer_3;
    QLabel *openLabel;
    QPushButton *commitButton;
    QLabel *openLabel_2;
    QPushButton *cancelButton;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QTextEdit *InputTextEdit;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *OutputTextEdit;
    QPushButton *resetButton;
    QPushButton *openButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(673, 600);
        Widget->setAutoFillBackground(false);
        Widget->setStyleSheet(QString::fromUtf8("#Widget{background-image: url(:/17.jpg);}"));
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(130, 50, 391, 28));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        infoLabel = new QLabel(layoutWidget);
        infoLabel->setObjectName("infoLabel");
        QFont font;
        font.setPointSize(15);
        infoLabel->setFont(font);

        horizontalLayout_3->addWidget(infoLabel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        openLabel = new QLabel(Widget);
        openLabel->setObjectName("openLabel");
        openLabel->setGeometry(QRect(110, 100, 51, 23));
        QFont font1;
        font1.setPointSize(10);
        openLabel->setFont(font1);
        commitButton = new QPushButton(Widget);
        commitButton->setObjectName("commitButton");
        commitButton->setGeometry(QRect(280, 250, 91, 31));
        QFont font2;
        font2.setPointSize(12);
        commitButton->setFont(font2);
        openLabel_2 = new QLabel(Widget);
        openLabel_2->setObjectName("openLabel_2");
        openLabel_2->setGeometry(QRect(490, 100, 51, 23));
        openLabel_2->setFont(font1);
        cancelButton = new QPushButton(Widget);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setGeometry(QRect(520, 560, 141, 24));
        layoutWidget1 = new QWidget(Widget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(20, 130, 241, 311));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        InputTextEdit = new QTextEdit(layoutWidget1);
        InputTextEdit->setObjectName("InputTextEdit");
        InputTextEdit->setEnabled(true);
        InputTextEdit->setAutoFillBackground(true);

        verticalLayout->addWidget(InputTextEdit);

        layoutWidget2 = new QWidget(Widget);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(390, 130, 258, 401));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        OutputTextEdit = new QTextEdit(layoutWidget2);
        OutputTextEdit->setObjectName("OutputTextEdit");

        verticalLayout_2->addWidget(OutputTextEdit);

        resetButton = new QPushButton(Widget);
        resetButton->setObjectName("resetButton");
        resetButton->setGeometry(QRect(280, 300, 91, 31));
        resetButton->setFont(font2);
        openButton = new QPushButton(Widget);
        openButton->setObjectName("openButton");
        openButton->setEnabled(true);
        openButton->setGeometry(QRect(100, 460, 91, 31));
        openButton->setFont(font2);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        infoLabel->setText(QCoreApplication::translate("Widget", "\350\257\215\346\263\225\345\210\206\346\236\220\345\231\250", nullptr));
        openLabel->setText(QCoreApplication::translate("Widget", "\346\265\213\350\257\225\344\273\243\347\240\201\357\274\232", nullptr));
        commitButton->setText(QCoreApplication::translate("Widget", "\345\210\206\346\236\220", nullptr));
        openLabel_2->setText(QCoreApplication::translate("Widget", "\345\210\206\346\236\220\347\273\223\346\236\234", nullptr));
        cancelButton->setText(QCoreApplication::translate("Widget", "\351\200\200\345\207\272", nullptr));
        resetButton->setText(QCoreApplication::translate("Widget", "\351\207\215\347\275\256", nullptr));
        openButton->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
