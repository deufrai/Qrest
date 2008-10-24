/********************************************************************************
** Form generated from reading ui file 'zestaboutdialog.ui'
**
** Created: Fri Oct 24 21:20:56 2008
**      by: Qt User Interface Compiler version 4.3.4
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ZESTABOUTDIALOG_H
#define UI_ZESTABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

class Ui_ZestAboutDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *aboutLabel;
    QGridLayout *gridLayout1;
    QSpacerItem *spacerItem;
    QPushButton *pushButton;

    void setupUi(QDialog *ZestAboutDialog)
    {
    if (ZestAboutDialog->objectName().isEmpty())
        ZestAboutDialog->setObjectName(QString::fromUtf8("ZestAboutDialog"));
    ZestAboutDialog->setWindowModality(Qt::WindowModal);
    ZestAboutDialog->resize(181, 179);
    gridLayout = new QGridLayout(ZestAboutDialog);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    aboutLabel = new QLabel(ZestAboutDialog);
    aboutLabel->setObjectName(QString::fromUtf8("aboutLabel"));
    aboutLabel->setFrameShape(QFrame::NoFrame);
    aboutLabel->setAlignment(Qt::AlignCenter);
    aboutLabel->setOpenExternalLinks(true);

    gridLayout->addWidget(aboutLabel, 0, 0, 1, 1);

    gridLayout1 = new QGridLayout();
    gridLayout1->setSpacing(6);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    spacerItem = new QSpacerItem(298, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout1->addItem(spacerItem, 0, 0, 1, 1);

    pushButton = new QPushButton(ZestAboutDialog);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    gridLayout1->addWidget(pushButton, 0, 1, 1, 1);


    gridLayout->addLayout(gridLayout1, 1, 0, 1, 1);


    retranslateUi(ZestAboutDialog);
    QObject::connect(pushButton, SIGNAL(clicked()), ZestAboutDialog, SLOT(accept()));

    QMetaObject::connectSlotsByName(ZestAboutDialog);
    } // setupUi

    void retranslateUi(QDialog *ZestAboutDialog)
    {
    ZestAboutDialog->setWindowTitle(QApplication::translate("ZestAboutDialog", "About Zest", 0, QApplication::UnicodeUTF8));
    aboutLabel->setText(QApplication::translate("ZestAboutDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("ZestAboutDialog", "OK", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ZestAboutDialog);
    } // retranslateUi

};

namespace Ui {
    class ZestAboutDialog: public Ui_ZestAboutDialog {};
} // namespace Ui

#endif // UI_ZESTABOUTDIALOG_H
