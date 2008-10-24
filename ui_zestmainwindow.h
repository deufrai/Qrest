/********************************************************************************
** Form generated from reading ui file 'zestmainwindow.ui'
**
** Created: Fri Oct 24 21:20:56 2008
**      by: Qt User Interface Compiler version 4.3.4
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ZESTMAINWINDOW_H
#define UI_ZESTMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

class Ui_ZestMainWindowClass
{
public:
    QAction *actionAbout_Qt;
    QAction *actionQuit;
    QAction *actionAbout;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout1;
    QLabel *tempoLabel;
    QLineEdit *tempoEdit;
    QPushButton *tapButton;
    QLabel *steadyHint;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout2;
    QRadioButton *plainRadio;
    QRadioButton *dottedRadio;
    QRadioButton *tripletRadio;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout3;
    QGridLayout *gridLayout4;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *wholePeriodEdit;
    QLabel *label_3;
    QLineEdit *wholeLfoEdit;
    QLineEdit *halfPeriodEdit;
    QLabel *label;
    QLineEdit *halfLfoEdit;
    QLineEdit *quarterPeriodEdit;
    QLabel *label_2;
    QLineEdit *quarterLfoEdit;
    QLineEdit *eighthPeriodEdit;
    QLabel *label_6;
    QLineEdit *eighthLfoEdit;
    QLineEdit *sixteenthPeriodEdit;
    QLabel *label_5;
    QLineEdit *sixteenthLfoEdit;
    QLineEdit *thirtySecondPeriodEdit;
    QLabel *label_4;
    QLineEdit *thirtySecondLfoEdit;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ZestMainWindowClass)
    {
    if (ZestMainWindowClass->objectName().isEmpty())
        ZestMainWindowClass->setObjectName(QString::fromUtf8("ZestMainWindowClass"));
    ZestMainWindowClass->resize(322, 475);
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(ZestMainWindowClass->sizePolicy().hasHeightForWidth());
    ZestMainWindowClass->setSizePolicy(sizePolicy);
    QFont font;
    font.setPointSize(9);
    font.setKerning(true);
    ZestMainWindowClass->setFont(font);
    actionAbout_Qt = new QAction(ZestMainWindowClass);
    actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
    actionQuit = new QAction(ZestMainWindowClass);
    actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
    actionAbout = new QAction(ZestMainWindowClass);
    actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
    centralwidget = new QWidget(ZestMainWindowClass);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    centralwidget->setGeometry(QRect(0, 26, 322, 426));
    gridLayout = new QGridLayout(centralwidget);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    groupBox = new QGroupBox(centralwidget);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    gridLayout1 = new QGridLayout(groupBox);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    tempoLabel = new QLabel(groupBox);
    tempoLabel->setObjectName(QString::fromUtf8("tempoLabel"));

    gridLayout1->addWidget(tempoLabel, 0, 0, 1, 1);

    tempoEdit = new QLineEdit(groupBox);
    tempoEdit->setObjectName(QString::fromUtf8("tempoEdit"));
    tempoEdit->setMinimumSize(QSize(60, 28));
    tempoEdit->setBaseSize(QSize(60, 28));

    gridLayout1->addWidget(tempoEdit, 0, 1, 1, 1);

    tapButton = new QPushButton(groupBox);
    tapButton->setObjectName(QString::fromUtf8("tapButton"));

    gridLayout1->addWidget(tapButton, 0, 2, 1, 1);

    steadyHint = new QLabel(groupBox);
    steadyHint->setObjectName(QString::fromUtf8("steadyHint"));
    steadyHint->setMinimumSize(QSize(24, 0));

    gridLayout1->addWidget(steadyHint, 0, 3, 1, 1);


    gridLayout->addWidget(groupBox, 0, 0, 1, 1);

    groupBox_3 = new QGroupBox(centralwidget);
    groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
    gridLayout2 = new QGridLayout(groupBox_3);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    plainRadio = new QRadioButton(groupBox_3);
    plainRadio->setObjectName(QString::fromUtf8("plainRadio"));
    plainRadio->setChecked(true);

    gridLayout2->addWidget(plainRadio, 0, 0, 1, 1);

    dottedRadio = new QRadioButton(groupBox_3);
    dottedRadio->setObjectName(QString::fromUtf8("dottedRadio"));

    gridLayout2->addWidget(dottedRadio, 0, 1, 1, 1);

    tripletRadio = new QRadioButton(groupBox_3);
    tripletRadio->setObjectName(QString::fromUtf8("tripletRadio"));

    gridLayout2->addWidget(tripletRadio, 0, 2, 1, 1);


    gridLayout->addWidget(groupBox_3, 1, 0, 1, 1);

    groupBox_2 = new QGroupBox(centralwidget);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    gridLayout3 = new QGridLayout(groupBox_2);
    gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
    gridLayout4 = new QGridLayout();
    gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
    label_7 = new QLabel(groupBox_2);
    label_7->setObjectName(QString::fromUtf8("label_7"));
    label_7->setAlignment(Qt::AlignCenter);

    gridLayout4->addWidget(label_7, 0, 0, 1, 1);

    label_8 = new QLabel(groupBox_2);
    label_8->setObjectName(QString::fromUtf8("label_8"));
    label_8->setAlignment(Qt::AlignCenter);

    gridLayout4->addWidget(label_8, 0, 2, 1, 1);

    wholePeriodEdit = new QLineEdit(groupBox_2);
    wholePeriodEdit->setObjectName(QString::fromUtf8("wholePeriodEdit"));
    wholePeriodEdit->setMinimumSize(QSize(60, 28));
    wholePeriodEdit->setBaseSize(QSize(60, 28));
    wholePeriodEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    wholePeriodEdit->setReadOnly(true);

    gridLayout4->addWidget(wholePeriodEdit, 1, 0, 1, 1);

    label_3 = new QLabel(groupBox_2);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setPixmap(QPixmap(QString::fromUtf8(":/notes/pix/whole.svg")));
    label_3->setAlignment(Qt::AlignCenter);

    gridLayout4->addWidget(label_3, 1, 1, 1, 1);

    wholeLfoEdit = new QLineEdit(groupBox_2);
    wholeLfoEdit->setObjectName(QString::fromUtf8("wholeLfoEdit"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(wholeLfoEdit->sizePolicy().hasHeightForWidth());
    wholeLfoEdit->setSizePolicy(sizePolicy1);
    wholeLfoEdit->setMinimumSize(QSize(60, 28));
    wholeLfoEdit->setBaseSize(QSize(60, 28));
    wholeLfoEdit->setReadOnly(true);

    gridLayout4->addWidget(wholeLfoEdit, 1, 2, 1, 1);

    halfPeriodEdit = new QLineEdit(groupBox_2);
    halfPeriodEdit->setObjectName(QString::fromUtf8("halfPeriodEdit"));
    halfPeriodEdit->setMinimumSize(QSize(60, 28));
    halfPeriodEdit->setBaseSize(QSize(60, 28));
    halfPeriodEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    halfPeriodEdit->setReadOnly(true);

    gridLayout4->addWidget(halfPeriodEdit, 2, 0, 1, 1);

    label = new QLabel(groupBox_2);
    label->setObjectName(QString::fromUtf8("label"));
    label->setPixmap(QPixmap(QString::fromUtf8(":/notes/pix/half.svg")));
    label->setAlignment(Qt::AlignCenter);

    gridLayout4->addWidget(label, 2, 1, 1, 1);

    halfLfoEdit = new QLineEdit(groupBox_2);
    halfLfoEdit->setObjectName(QString::fromUtf8("halfLfoEdit"));
    halfLfoEdit->setMinimumSize(QSize(60, 28));
    halfLfoEdit->setBaseSize(QSize(60, 28));
    halfLfoEdit->setReadOnly(true);

    gridLayout4->addWidget(halfLfoEdit, 2, 2, 1, 1);

    quarterPeriodEdit = new QLineEdit(groupBox_2);
    quarterPeriodEdit->setObjectName(QString::fromUtf8("quarterPeriodEdit"));
    quarterPeriodEdit->setMinimumSize(QSize(60, 28));
    quarterPeriodEdit->setBaseSize(QSize(60, 28));
    quarterPeriodEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    quarterPeriodEdit->setReadOnly(true);

    gridLayout4->addWidget(quarterPeriodEdit, 3, 0, 1, 1);

    label_2 = new QLabel(groupBox_2);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setPixmap(QPixmap(QString::fromUtf8(":/notes/pix/quarter.svg")));
    label_2->setAlignment(Qt::AlignCenter);

    gridLayout4->addWidget(label_2, 3, 1, 1, 1);

    quarterLfoEdit = new QLineEdit(groupBox_2);
    quarterLfoEdit->setObjectName(QString::fromUtf8("quarterLfoEdit"));
    quarterLfoEdit->setMinimumSize(QSize(60, 28));
    quarterLfoEdit->setBaseSize(QSize(60, 28));
    quarterLfoEdit->setReadOnly(true);

    gridLayout4->addWidget(quarterLfoEdit, 3, 2, 1, 1);

    eighthPeriodEdit = new QLineEdit(groupBox_2);
    eighthPeriodEdit->setObjectName(QString::fromUtf8("eighthPeriodEdit"));
    eighthPeriodEdit->setMinimumSize(QSize(60, 28));
    eighthPeriodEdit->setBaseSize(QSize(60, 28));
    eighthPeriodEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    eighthPeriodEdit->setReadOnly(true);

    gridLayout4->addWidget(eighthPeriodEdit, 4, 0, 1, 1);

    label_6 = new QLabel(groupBox_2);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setPixmap(QPixmap(QString::fromUtf8(":/notes/pix/eighth.svg")));
    label_6->setAlignment(Qt::AlignCenter);

    gridLayout4->addWidget(label_6, 4, 1, 1, 1);

    eighthLfoEdit = new QLineEdit(groupBox_2);
    eighthLfoEdit->setObjectName(QString::fromUtf8("eighthLfoEdit"));
    eighthLfoEdit->setMinimumSize(QSize(60, 28));
    eighthLfoEdit->setBaseSize(QSize(60, 28));
    eighthLfoEdit->setReadOnly(true);

    gridLayout4->addWidget(eighthLfoEdit, 4, 2, 1, 1);

    sixteenthPeriodEdit = new QLineEdit(groupBox_2);
    sixteenthPeriodEdit->setObjectName(QString::fromUtf8("sixteenthPeriodEdit"));
    sixteenthPeriodEdit->setMinimumSize(QSize(60, 28));
    sixteenthPeriodEdit->setBaseSize(QSize(60, 28));
    sixteenthPeriodEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    sixteenthPeriodEdit->setReadOnly(true);

    gridLayout4->addWidget(sixteenthPeriodEdit, 5, 0, 1, 1);

    label_5 = new QLabel(groupBox_2);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setPixmap(QPixmap(QString::fromUtf8(":/notes/pix/sixteenth.svg")));
    label_5->setAlignment(Qt::AlignCenter);

    gridLayout4->addWidget(label_5, 5, 1, 1, 1);

    sixteenthLfoEdit = new QLineEdit(groupBox_2);
    sixteenthLfoEdit->setObjectName(QString::fromUtf8("sixteenthLfoEdit"));
    sixteenthLfoEdit->setMinimumSize(QSize(60, 28));
    sixteenthLfoEdit->setBaseSize(QSize(60, 28));
    sixteenthLfoEdit->setReadOnly(true);

    gridLayout4->addWidget(sixteenthLfoEdit, 5, 2, 1, 1);

    thirtySecondPeriodEdit = new QLineEdit(groupBox_2);
    thirtySecondPeriodEdit->setObjectName(QString::fromUtf8("thirtySecondPeriodEdit"));
    thirtySecondPeriodEdit->setMinimumSize(QSize(60, 28));
    thirtySecondPeriodEdit->setBaseSize(QSize(60, 28));
    thirtySecondPeriodEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    thirtySecondPeriodEdit->setReadOnly(true);

    gridLayout4->addWidget(thirtySecondPeriodEdit, 6, 0, 1, 1);

    label_4 = new QLabel(groupBox_2);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setPixmap(QPixmap(QString::fromUtf8(":/notes/pix/thirtysecond.svg")));
    label_4->setAlignment(Qt::AlignCenter);

    gridLayout4->addWidget(label_4, 6, 1, 1, 1);

    thirtySecondLfoEdit = new QLineEdit(groupBox_2);
    thirtySecondLfoEdit->setObjectName(QString::fromUtf8("thirtySecondLfoEdit"));
    thirtySecondLfoEdit->setMinimumSize(QSize(60, 28));
    thirtySecondLfoEdit->setBaseSize(QSize(60, 28));
    thirtySecondLfoEdit->setReadOnly(true);

    gridLayout4->addWidget(thirtySecondLfoEdit, 6, 2, 1, 1);


    gridLayout3->addLayout(gridLayout4, 0, 0, 1, 1);


    gridLayout->addWidget(groupBox_2, 2, 0, 1, 1);

    ZestMainWindowClass->setCentralWidget(centralwidget);
    menubar = new QMenuBar(ZestMainWindowClass);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 322, 26));
    menuHelp = new QMenu(menubar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    ZestMainWindowClass->setMenuBar(menubar);
    statusbar = new QStatusBar(ZestMainWindowClass);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    statusbar->setGeometry(QRect(0, 452, 322, 23));
    ZestMainWindowClass->setStatusBar(statusbar);
    tempoLabel->setBuddy(tempoEdit);
    QWidget::setTabOrder(tempoEdit, tapButton);
    QWidget::setTabOrder(tapButton, plainRadio);
    QWidget::setTabOrder(plainRadio, dottedRadio);
    QWidget::setTabOrder(dottedRadio, tripletRadio);
    QWidget::setTabOrder(tripletRadio, wholePeriodEdit);
    QWidget::setTabOrder(wholePeriodEdit, halfPeriodEdit);
    QWidget::setTabOrder(halfPeriodEdit, quarterPeriodEdit);
    QWidget::setTabOrder(quarterPeriodEdit, eighthPeriodEdit);
    QWidget::setTabOrder(eighthPeriodEdit, sixteenthPeriodEdit);
    QWidget::setTabOrder(sixteenthPeriodEdit, thirtySecondPeriodEdit);
    QWidget::setTabOrder(thirtySecondPeriodEdit, wholeLfoEdit);
    QWidget::setTabOrder(wholeLfoEdit, halfLfoEdit);
    QWidget::setTabOrder(halfLfoEdit, quarterLfoEdit);
    QWidget::setTabOrder(quarterLfoEdit, eighthLfoEdit);
    QWidget::setTabOrder(eighthLfoEdit, sixteenthLfoEdit);
    QWidget::setTabOrder(sixteenthLfoEdit, thirtySecondLfoEdit);

    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuHelp->menuAction());
    menuHelp->addAction(actionAbout);
    menuFile->addAction(actionQuit);

    retranslateUi(ZestMainWindowClass);

    QMetaObject::connectSlotsByName(ZestMainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *ZestMainWindowClass)
    {
    ZestMainWindowClass->setWindowTitle(QApplication::translate("ZestMainWindowClass", "ZEST", 0, QApplication::UnicodeUTF8));
    actionAbout_Qt->setText(QApplication::translate("ZestMainWindowClass", "About &Qt...", 0, QApplication::UnicodeUTF8));
    actionAbout_Qt->setStatusTip(QApplication::translate("ZestMainWindowClass", "About Qt", 0, QApplication::UnicodeUTF8));
    actionQuit->setText(QApplication::translate("ZestMainWindowClass", "&Quit", 0, QApplication::UnicodeUTF8));
    actionQuit->setStatusTip(QApplication::translate("ZestMainWindowClass", "Quit Zest", 0, QApplication::UnicodeUTF8));
    actionQuit->setShortcut(QApplication::translate("ZestMainWindowClass", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
    actionAbout->setText(QApplication::translate("ZestMainWindowClass", "About &Zest...", 0, QApplication::UnicodeUTF8));
    actionAbout->setStatusTip(QApplication::translate("ZestMainWindowClass", "About Zest", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("ZestMainWindowClass", "Tempo Input", 0, QApplication::UnicodeUTF8));
    tempoLabel->setText(QApplication::translate("ZestMainWindowClass", "Temp&o  : ", 0, QApplication::UnicodeUTF8));
    tempoEdit->setToolTip(QApplication::translate("ZestMainWindowClass", "Enter tempo in BPM and hit 'enter' or use mouse wheel", 0, QApplication::UnicodeUTF8));
    tapButton->setToolTip(QApplication::translate("ZestMainWindowClass", "Click me along tempo until you're told that you're tapping steadily", 0, QApplication::UnicodeUTF8));
    tapButton->setText(QApplication::translate("ZestMainWindowClass", "T&AP", 0, QApplication::UnicodeUTF8));
    steadyHint->setText(QString());
    groupBox_3->setTitle(QApplication::translate("ZestMainWindowClass", "Alteration", 0, QApplication::UnicodeUTF8));
    plainRadio->setText(QApplication::translate("ZestMainWindowClass", "&Plain", 0, QApplication::UnicodeUTF8));
    dottedRadio->setText(QApplication::translate("ZestMainWindowClass", "&Dotted", 0, QApplication::UnicodeUTF8));
    tripletRadio->setText(QApplication::translate("ZestMainWindowClass", "&Triplet", 0, QApplication::UnicodeUTF8));
    groupBox_2->setTitle(QApplication::translate("ZestMainWindowClass", "Delays and LFOs", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("ZestMainWindowClass", "ms", 0, QApplication::UnicodeUTF8));
    label_8->setText(QApplication::translate("ZestMainWindowClass", "Hz", 0, QApplication::UnicodeUTF8));
    label_3->setText(QString());
    label->setText(QString());
    label_2->setText(QString());
    label_6->setText(QString());
    label_5->setText(QString());
    label_4->setText(QString());
    menuHelp->setTitle(QApplication::translate("ZestMainWindowClass", "&Help", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("ZestMainWindowClass", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ZestMainWindowClass: public Ui_ZestMainWindowClass {};
} // namespace Ui

#endif // UI_ZESTMAINWINDOW_H
