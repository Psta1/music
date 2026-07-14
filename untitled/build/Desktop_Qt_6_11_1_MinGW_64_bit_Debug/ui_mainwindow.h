/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *mainContentLayout;
    QVBoxLayout *leftPanel;
    QSpacerItem *topSpacer1;
    QLabel *albumArtLabel;
    QLabel *currentSongLabel;
    QSpacerItem *bottomSpacer1;
    QListWidget *lyricListWidget;
    QWidget *bottomBar;
    QVBoxLayout *bottomLayout;
    QHBoxLayout *progressLayout;
    QLabel *timeLabel;
    QSlider *progressSlider;
    QHBoxLayout *controlLayout;
    QPushButton *modeBtn;
    QSpacerItem *leftControlSpacer;
    QPushButton *prevBtn;
    QPushButton *playPauseBtn;
    QPushButton *nextBtn;
    QSpacerItem *rightControlSpacer;
    QHBoxLayout *volumeLayout;
    QLabel *volumeIconLabel;
    QSlider *volumeSlider;
    QLabel *volumeValueLabel;
    QPushButton *openBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        mainContentLayout = new QHBoxLayout();
        mainContentLayout->setObjectName("mainContentLayout");
        leftPanel = new QVBoxLayout();
        leftPanel->setObjectName("leftPanel");
        topSpacer1 = new QSpacerItem(20, 30, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        leftPanel->addItem(topSpacer1);

        albumArtLabel = new QLabel(centralwidget);
        albumArtLabel->setObjectName("albumArtLabel");
        albumArtLabel->setMinimumSize(QSize(280, 280));
        albumArtLabel->setMaximumSize(QSize(280, 280));
        albumArtLabel->setAlignment(Qt::AlignCenter);

        leftPanel->addWidget(albumArtLabel);

        currentSongLabel = new QLabel(centralwidget);
        currentSongLabel->setObjectName("currentSongLabel");
        currentSongLabel->setAlignment(Qt::AlignCenter);

        leftPanel->addWidget(currentSongLabel);

        bottomSpacer1 = new QSpacerItem(20, 30, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        leftPanel->addItem(bottomSpacer1);


        mainContentLayout->addLayout(leftPanel);

        lyricListWidget = new QListWidget(centralwidget);
        lyricListWidget->setObjectName("lyricListWidget");
        lyricListWidget->setMinimumSize(QSize(400, 350));

        mainContentLayout->addWidget(lyricListWidget);


        verticalLayout->addLayout(mainContentLayout);

        bottomBar = new QWidget(centralwidget);
        bottomBar->setObjectName("bottomBar");
        bottomLayout = new QVBoxLayout(bottomBar);
        bottomLayout->setObjectName("bottomLayout");
        bottomLayout->setContentsMargins(0, 0, 0, 0);
        progressLayout = new QHBoxLayout();
        progressLayout->setObjectName("progressLayout");
        timeLabel = new QLabel(bottomBar);
        timeLabel->setObjectName("timeLabel");

        progressLayout->addWidget(timeLabel);

        progressSlider = new QSlider(bottomBar);
        progressSlider->setObjectName("progressSlider");
        progressSlider->setOrientation(Qt::Orientation::Horizontal);

        progressLayout->addWidget(progressSlider);


        bottomLayout->addLayout(progressLayout);

        controlLayout = new QHBoxLayout();
        controlLayout->setObjectName("controlLayout");
        modeBtn = new QPushButton(bottomBar);
        modeBtn->setObjectName("modeBtn");
        modeBtn->setMinimumSize(QSize(70, 36));

        controlLayout->addWidget(modeBtn);

        leftControlSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        controlLayout->addItem(leftControlSpacer);

        prevBtn = new QPushButton(bottomBar);
        prevBtn->setObjectName("prevBtn");
        prevBtn->setMinimumSize(QSize(40, 40));

        controlLayout->addWidget(prevBtn);

        playPauseBtn = new QPushButton(bottomBar);
        playPauseBtn->setObjectName("playPauseBtn");
        playPauseBtn->setMinimumSize(QSize(50, 50));
        playPauseBtn->setMaximumSize(QSize(50, 50));

        controlLayout->addWidget(playPauseBtn);

        nextBtn = new QPushButton(bottomBar);
        nextBtn->setObjectName("nextBtn");
        nextBtn->setMinimumSize(QSize(40, 40));

        controlLayout->addWidget(nextBtn);

        rightControlSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        controlLayout->addItem(rightControlSpacer);

        volumeLayout = new QHBoxLayout();
        volumeLayout->setObjectName("volumeLayout");
        volumeIconLabel = new QLabel(bottomBar);
        volumeIconLabel->setObjectName("volumeIconLabel");

        volumeLayout->addWidget(volumeIconLabel);

        volumeSlider = new QSlider(bottomBar);
        volumeSlider->setObjectName("volumeSlider");
        volumeSlider->setMinimumSize(QSize(80, 20));
        volumeSlider->setOrientation(Qt::Orientation::Horizontal);
        volumeSlider->setValue(100);

        volumeLayout->addWidget(volumeSlider);

        volumeValueLabel = new QLabel(bottomBar);
        volumeValueLabel->setObjectName("volumeValueLabel");

        volumeLayout->addWidget(volumeValueLabel);


        controlLayout->addLayout(volumeLayout);

        openBtn = new QPushButton(bottomBar);
        openBtn->setObjectName("openBtn");
        openBtn->setMinimumSize(QSize(70, 36));

        controlLayout->addWidget(openBtn);


        bottomLayout->addLayout(controlLayout);


        verticalLayout->addWidget(bottomBar);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\351\237\263\344\271\220\346\222\255\346\224\276\345\231\250", nullptr));
        MainWindow->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"    QMainWindow { background-color: #1a1a2e; }\n"
"    QLabel { color: #ffffff; }\n"
"   ", nullptr));
        albumArtLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "border: 3px solid #333355; border-radius: 140px; background-color: #16213e;", nullptr));
        albumArtLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\216\265", nullptr));
        currentSongLabel->setText(QCoreApplication::translate("MainWindow", "\346\234\252\351\200\211\346\213\251\346\255\214\346\233\262", nullptr));
        currentSongLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 16px; color: #e0e0e0; padding: 10px; font-weight: bold;", nullptr));
        lyricListWidget->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"          QListWidget {\n"
"            background-color: #1a1a2e;\n"
"            border: none;\n"
"            font-size: 14px;\n"
"            color: #aaaaaa;\n"
"            padding: 20px;\n"
"          }\n"
"          QListWidget::item {\n"
"            padding: 8px 0px;\n"
"            border: none;\n"
"          }\n"
"         ", nullptr));
        bottomBar->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"        QWidget#bottomBar {\n"
"          background-color: #16213e;\n"
"          border-top: 1px solid #333355;\n"
"          padding: 8px;\n"
"        }\n"
"       ", nullptr));
        timeLabel->setText(QCoreApplication::translate("MainWindow", "00:00 / 00:00", nullptr));
        timeLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 12px; color: #888888;", nullptr));
        progressSlider->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"             QSlider::groove:horizontal { background: #333355; height: 4px; border-radius: 2px; }\n"
"             QSlider::handle:horizontal { background: #ec4141; width: 12px; height: 12px; margin: -4px 0; border-radius: 6px; }\n"
"             QSlider::sub-page:horizontal { background: #ec4141; border-radius: 2px; }\n"
"            ", nullptr));
        modeBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: transparent; color: #cccccc; border: 1px solid #444466; border-radius: 4px; font-size: 12px; padding: 4px 8px; } QPushButton:hover { background-color: #333355; }", nullptr));
        modeBtn->setText(QCoreApplication::translate("MainWindow", "\351\241\272\345\272\217\346\222\255\346\224\276", nullptr));
        prevBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: transparent; color: #ffffff; border: none; font-size: 20px; } QPushButton:hover { color: #ec4141; }", nullptr));
        prevBtn->setText(QCoreApplication::translate("MainWindow", "\342\217\256", nullptr));
        playPauseBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: #ec4141; color: #ffffff; border: none; border-radius: 25px; font-size: 16px; font-weight: bold; font-family: Arial; } QPushButton:hover { background-color: #ff5555; }", nullptr));
        playPauseBtn->setText(QCoreApplication::translate("MainWindow", " \342\226\267 ", nullptr));
        nextBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: transparent; color: #ffffff; border: none; font-size: 20px; } QPushButton:hover { color: #ec4141; }", nullptr));
        nextBtn->setText(QCoreApplication::translate("MainWindow", "\342\217\255", nullptr));
        volumeIconLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\224\212", nullptr));
        volumeSlider->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"               QSlider::groove:horizontal { background: #333355; height: 3px; border-radius: 1px; }\n"
"               QSlider::handle:horizontal { background: #ffffff; width: 10px; height: 10px; margin: -4px 0; border-radius: 5px; }\n"
"               QSlider::sub-page:horizontal { background: #ec4141; border-radius: 1px; }\n"
"              ", nullptr));
        volumeValueLabel->setText(QCoreApplication::translate("MainWindow", "100%", nullptr));
        volumeValueLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 11px; color: #888888;", nullptr));
        openBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: transparent; color: #cccccc; border: 1px solid #444466; border-radius: 4px; font-size: 12px; padding: 4px 8px; } QPushButton:hover { background-color: #333355; }", nullptr));
        openBtn->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\255\214\346\233\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
