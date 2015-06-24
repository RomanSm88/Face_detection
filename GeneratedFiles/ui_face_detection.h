/********************************************************************************
** Form generated from reading UI file 'face_detection.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACE_DETECTION_H
#define UI_FACE_DETECTION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Face_detectionClass
{
public:
    QPushButton *knopka;
    QGroupBox *groupBox_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *SizeVideo_1;
    QLabel *FPS_1;
    QLabel *Size_Video_2;
    QLabel *FPS_2;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QToolButton *toolButton;
    QLineEdit *lineEdit;
    QGroupBox *groupBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QLabel *label;
    QLabel *label_10;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;

    void setupUi(QWidget *Face_detectionClass)
    {
        if (Face_detectionClass->objectName().isEmpty())
            Face_detectionClass->setObjectName(QString::fromUtf8("Face_detectionClass"));
        Face_detectionClass->setEnabled(true);
        Face_detectionClass->resize(1058, 504);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Face_detectionClass->sizePolicy().hasHeightForWidth());
        Face_detectionClass->setSizePolicy(sizePolicy);
        Face_detectionClass->setMinimumSize(QSize(1058, 504));
        Face_detectionClass->setMaximumSize(QSize(1058, 504));
        knopka = new QPushButton(Face_detectionClass);
        knopka->setObjectName(QString::fromUtf8("knopka"));
        knopka->setGeometry(QRect(770, 210, 121, 23));
        knopka->setMinimumSize(QSize(121, 23));
        knopka->setMaximumSize(QSize(121, 23));
        QFont font;
        font.setPointSize(12);
        knopka->setFont(font);
        groupBox_2 = new QGroupBox(Face_detectionClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(760, 280, 290, 221));
        groupBox_2->setMinimumSize(QSize(241, 111));
        groupBox_2->setMaximumSize(QSize(290, 230));
        groupBox_2->setFont(font);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 40, 191, 21));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 70, 171, 21));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 100, 171, 21));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 130, 141, 21));
        SizeVideo_1 = new QLabel(groupBox_2);
        SizeVideo_1->setObjectName(QString::fromUtf8("SizeVideo_1"));
        SizeVideo_1->setGeometry(QRect(190, 40, 91, 21));
        FPS_1 = new QLabel(groupBox_2);
        FPS_1->setObjectName(QString::fromUtf8("FPS_1"));
        FPS_1->setGeometry(QRect(190, 70, 91, 21));
        Size_Video_2 = new QLabel(groupBox_2);
        Size_Video_2->setObjectName(QString::fromUtf8("Size_Video_2"));
        Size_Video_2->setGeometry(QRect(170, 100, 121, 21));
        FPS_2 = new QLabel(groupBox_2);
        FPS_2->setObjectName(QString::fromUtf8("FPS_2"));
        FPS_2->setGeometry(QRect(160, 130, 121, 20));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 160, 141, 20));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(150, 160, 131, 21));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 190, 211, 20));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(220, 190, 51, 21));
        toolButton = new QToolButton(Face_detectionClass);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(1000, 170, 51, 20));
        toolButton->setMinimumSize(QSize(51, 20));
        toolButton->setMaximumSize(QSize(51, 20));
        QFont font1;
        font1.setPointSize(10);
        toolButton->setFont(font1);
        lineEdit = new QLineEdit(Face_detectionClass);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(770, 170, 211, 20));
        lineEdit->setMinimumSize(QSize(211, 20));
        lineEdit->setMaximumSize(QSize(211, 20));
        lineEdit->setFont(font);
        lineEdit->setLayoutDirection(Qt::RightToLeft);
        groupBox = new QGroupBox(Face_detectionClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(770, 10, 241, 111));
        groupBox->setMinimumSize(QSize(241, 111));
        groupBox->setMaximumSize(QSize(241, 111));
        groupBox->setFont(font);
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(30, 60, 181, 21));
        radioButton->setMinimumSize(QSize(181, 21));
        radioButton->setMaximumSize(QSize(181, 21));
        radioButton->setFont(font);
        radioButton->setLayoutDirection(Qt::RightToLeft);
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(30, 30, 181, 21));
        radioButton_2->setMinimumSize(QSize(181, 21));
        radioButton_2->setMaximumSize(QSize(181, 21));
        radioButton_2->setFont(font);
        radioButton_2->setLayoutDirection(Qt::RightToLeft);
        radioButton_2->setInputMethodHints(Qt::ImhNoAutoUppercase);
        label = new QLabel(Face_detectionClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 720, 480));
        label->setFont(font);
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("border-image: url(:/Face_detection/Resources/Fon_video.bmp);"));
        label->setFrameShape(QFrame::WinPanel);
        label->setFrameShadow(QFrame::Sunken);
        label->setLineWidth(20);
        label->setAlignment(Qt::AlignCenter);
        label_10 = new QLabel(Face_detectionClass);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(770, 140, 211, 20));
        label_10->setFont(font);
        checkBox = new QCheckBox(Face_detectionClass);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(910, 210, 151, 17));
        checkBox->setFont(font);
        checkBox_2 = new QCheckBox(Face_detectionClass);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(760, 250, 181, 17));
        checkBox_2->setFont(font);

        retranslateUi(Face_detectionClass);

        QMetaObject::connectSlotsByName(Face_detectionClass);
    } // setupUi

    void retranslateUi(QWidget *Face_detectionClass)
    {
        Face_detectionClass->setWindowTitle(QApplication::translate("Face_detectionClass", "Face_detection", 0, QApplication::UnicodeUTF8));
        knopka->setText(QApplication::translate("Face_detectionClass", "\320\222\320\276\321\201\320\277\321\200\320\276\320\270\320\267\320\262\320\265\321\201\321\202\320\270", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("Face_detectionClass", "\320\241\320\262\320\276\320\271\321\201\321\202\320\262\320\260 \320\262\320\270\320\264\320\265\320\276\320\277\320\276\321\202\320\276\320\272\320\260:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Face_detectionClass", "\320\230\321\201\321\205\320\276\320\264\320\275\320\276\320\265 \321\200\320\260\320\267\321\200\320\265\321\210\320\265\320\275\320\270\320\265:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Face_detectionClass", "\320\234\320\260\320\272\321\201\320\270\320\274\320\260\320\273\321\214\320\275\320\260\321\217 \321\207\320\260\321\201\321\202\320\276\321\202\320\260:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Face_detectionClass", "\320\242\320\265\320\272\321\203\321\211\320\265\320\265 \321\200\320\260\320\267\321\200\320\265\321\210\320\265\320\275\320\270\320\265:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Face_detectionClass", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 \320\272\320\260\320\264\321\200\320\276\320\262 ~", 0, QApplication::UnicodeUTF8));
        SizeVideo_1->setText(QString());
        FPS_1->setText(QString());
        Size_Video_2->setText(QString());
        FPS_2->setText(QString());
        label_6->setText(QApplication::translate("Face_detectionClass", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 \320\262\321\213\320\262\320\276\320\264\320\260:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QString());
        label_8->setText(QApplication::translate("Face_detectionClass", "\320\227\320\260\320\264\320\265\321\200\320\266\320\272\320\260 \320\276\321\202 \320\274\320\260\320\272\321\201. \321\207\320\260\321\201\321\202\320\276\321\202\321\213:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QString());
        toolButton->setText(QApplication::translate("Face_detectionClass", "\320\236\320\261\320\267\320\276\321\200", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Face_detectionClass", "\320\230\321\201\321\202\320\276\321\207\320\275\320\270\320\272:", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("Face_detectionClass", "\320\232\320\260\320\274\320\265\321\200\320\260", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("Face_detectionClass", "\320\244\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        label_10->setText(QApplication::translate("Face_detectionClass", "\320\277\321\203\321\202\321\214 \320\264\320\276  \320\262\320\270\320\264\320\265\320\276 \321\204\320\260\320\271\320\273\320\260:", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("Face_detectionClass", "\320\222\320\272\320\273. \320\276\320\261\321\200\320\260\320\261\320\276\321\202\320\272\321\203", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("Face_detectionClass", "\320\222\321\213\320\272\320\273. \320\276\320\277\321\202\320\270\320\274\320\270\320\267\320\260\321\206\320\270\321\216", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Face_detectionClass: public Ui_Face_detectionClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACE_DETECTION_H
