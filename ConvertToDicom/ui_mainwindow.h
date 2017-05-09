/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *sourceDirLineEdit;
    QPushButton *sourceDirChooseushButton;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *destDirLineEdit;
    QPushButton *destDirChooseBushButton;
    QCheckBox *overWriteCheckBox;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QPushButton *editDicomAttributesPushButton;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *menuConvert_To_Dicom;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(599, 365);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(-1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        sourceDirLineEdit = new QLineEdit(groupBox);
        sourceDirLineEdit->setObjectName(QStringLiteral("sourceDirLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sourceDirLineEdit->sizePolicy().hasHeightForWidth());
        sourceDirLineEdit->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(sourceDirLineEdit);

        sourceDirChooseushButton = new QPushButton(groupBox);
        sourceDirChooseushButton->setObjectName(QStringLiteral("sourceDirChooseushButton"));

        horizontalLayout->addWidget(sourceDirChooseushButton);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);


        horizontalLayout_3->addWidget(groupBox);


        verticalLayout_4->addLayout(horizontalLayout_3);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(-1);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        destDirLineEdit = new QLineEdit(groupBox_2);
        destDirLineEdit->setObjectName(QStringLiteral("destDirLineEdit"));
        sizePolicy.setHeightForWidth(destDirLineEdit->sizePolicy().hasHeightForWidth());
        destDirLineEdit->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(destDirLineEdit);

        destDirChooseBushButton = new QPushButton(groupBox_2);
        destDirChooseBushButton->setObjectName(QStringLiteral("destDirChooseBushButton"));

        horizontalLayout_5->addWidget(destDirChooseBushButton);


        verticalLayout_2->addLayout(horizontalLayout_5);


        verticalLayout_3->addLayout(verticalLayout_2);

        overWriteCheckBox = new QCheckBox(groupBox_2);
        overWriteCheckBox->setObjectName(QStringLiteral("overWriteCheckBox"));

        verticalLayout_3->addWidget(overWriteCheckBox);


        verticalLayout_4->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        horizontalLayout_6 = new QHBoxLayout(groupBox_3);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_4->addWidget(label);

        editDicomAttributesPushButton = new QPushButton(groupBox_3);
        editDicomAttributesPushButton->setObjectName(QStringLiteral("editDicomAttributesPushButton"));

        horizontalLayout_4->addWidget(editDicomAttributesPushButton);


        horizontalLayout_6->addLayout(horizontalLayout_4);

        horizontalSpacer = new QSpacerItem(350, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);


        verticalLayout_4->addWidget(groupBox_3);

        verticalSpacer = new QSpacerItem(17, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 599, 22));
        menuConvert_To_Dicom = new QMenu(menuBar);
        menuConvert_To_Dicom->setObjectName(QStringLiteral("menuConvert_To_Dicom"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
#ifndef QT_NO_SHORTCUT
        label->setBuddy(editDicomAttributesPushButton);
#endif // QT_NO_SHORTCUT

        menuBar->addAction(menuConvert_To_Dicom->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuHelp->menuAction());

        retranslateUi(MainWindow);
        QObject::connect(sourceDirLineEdit, SIGNAL(editingFinished()), MainWindow, SLOT(sourceDirEdited()));
        QObject::connect(sourceDirChooseushButton, SIGNAL(clicked()), MainWindow, SLOT(sourceDirChooseButtonClicked()));
        QObject::connect(destDirLineEdit, SIGNAL(editingFinished()), MainWindow, SLOT(destDirEdited()));
        QObject::connect(destDirChooseBushButton, SIGNAL(clicked()), MainWindow, SLOT(destDirChooseButtonClicked()));
        QObject::connect(overWriteCheckBox, SIGNAL(stateChanged(int)), MainWindow, SLOT(overwriteCheckBoxChanged(int)));
        QObject::connect(editDicomAttributesPushButton, SIGNAL(clicked()), MainWindow, SLOT(dicomAttributesEditButtonClicked()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Source Directory", Q_NULLPTR));
        sourceDirChooseushButton->setText(QApplication::translate("MainWindow", "Choose", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Destination Directory", Q_NULLPTR));
        destDirChooseBushButton->setText(QApplication::translate("MainWindow", "Choose", Q_NULLPTR));
        overWriteCheckBox->setText(QApplication::translate("MainWindow", "Overwrite", Q_NULLPTR));
        groupBox_3->setTitle(QString());
        label->setText(QApplication::translate("MainWindow", "DICOM Attributes", Q_NULLPTR));
        editDicomAttributesPushButton->setText(QApplication::translate("MainWindow", "Edit", Q_NULLPTR));
        menuConvert_To_Dicom->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
