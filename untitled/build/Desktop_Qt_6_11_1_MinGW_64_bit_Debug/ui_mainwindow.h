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
    QListWidget *playlistWidget;
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
    QPushButton *togglePlaylistBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1050, 650);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        mainContentLayout = new QHBoxLayout();
        mainContentLayout->setObjectName("mainContentLayout");
        leftPanel = new QVBoxLayout();
        leftPanel->setObjectName("leftPanel");
        topSpacer1 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        leftPanel->addItem(topSpacer1);

        albumArtLabel = new QLabel(centralwidget);
        albumArtLabel->setObjectName("albumArtLabel");
        albumArtLabel->setMinimumSize(QSize(260, 260));
        albumArtLabel->setMaximumSize(QSize(260, 260));
        albumArtLabel->setAlignment(Qt::AlignCenter);

        leftPanel->addWidget(albumArtLabel);

        currentSongLabel = new QLabel(centralwidget);
        currentSongLabel->setObjectName("currentSongLabel");
        currentSongLabel->setAlignment(Qt::AlignCenter);

        leftPanel->addWidget(currentSongLabel);

        bottomSpacer1 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        leftPanel->addItem(bottomSpacer1);


        mainContentLayout->addLayout(leftPanel);

        lyricListWidget = new QListWidget(centralwidget);
        lyricListWidget->setObjectName("lyricListWidget");
        lyricListWidget->setMinimumSize(QSize(350, 300));

        mainContentLayout->addWidget(lyricListWidget);

        playlistWidget = new QListWidget(centralwidget);
        playlistWidget->setObjectName("playlistWidget");
        playlistWidget->setMinimumSize(QSize(220, 300));
        playlistWidget->setMaximumSize(QSize(250, 16777215));

        mainContentLayout->addWidget(playlistWidget);


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
        modeBtn->setMinimumSize(QSize(70, 32));

        controlLayout->addWidget(modeBtn);

        leftControlSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        controlLayout->addItem(leftControlSpacer);

        prevBtn = new QPushButton(bottomBar);
        prevBtn->setObjectName("prevBtn");
        prevBtn->setMinimumSize(QSize(36, 36));

        controlLayout->addWidget(prevBtn);

        playPauseBtn = new QPushButton(bottomBar);
        playPauseBtn->setObjectName("playPauseBtn");
        playPauseBtn->setMinimumSize(QSize(46, 46));
        playPauseBtn->setMaximumSize(QSize(46, 46));

        controlLayout->addWidget(playPauseBtn);

        nextBtn = new QPushButton(bottomBar);
        nextBtn->setObjectName("nextBtn");
        nextBtn->setMinimumSize(QSize(36, 36));

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
        openBtn->setMinimumSize(QSize(70, 32));

        controlLayout->addWidget(openBtn);

        togglePlaylistBtn = new QPushButton(bottomBar);
        togglePlaylistBtn->setObjectName("togglePlaylistBtn");
        togglePlaylistBtn->setMinimumSize(QSize(32, 32));

        controlLayout->addWidget(togglePlaylistBtn);


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
        albumArtLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "border: 3px solid #333355; border-radius: 130px; background-color: #16213e;", nullptr));
        albumArtLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\216\265", nullptr));
        currentSongLabel->setText(QCoreApplication::translate("MainWindow", "\346\234\252\351\200\211\346\213\251\346\255\214\346\233\262", nullptr));
        currentSongLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 15px; color: #e0e0e0; padding: 8px; font-weight: bold;", nullptr));
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
        playlistWidget->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"          QListWidget {\n"
"            background-color: #16213e;\n"
"            border: 1px solid #333355;\n"
"            border-radius: 8px;\n"
"            font-size: 13px;\n"
"            color: #cccccc;\n"
"            padding: 5px;\n"
"          }\n"
"          QListWidget::item {\n"
"            padding: 6px 4px;\n"
"            border-bottom: 1px solid #252545;\n"
"            border-radius: 4px;\n"
"          }\n"
"          QListWidget::item:hover {\n"
"            background-color: #252545;\n"
"          }\n"
"          QListWidget::item:selected {\n"
"            background-color: #333366;\n"
"            color: #ffffff;\n"
"          }\n"
"         ", nullptr));
        bottomBar->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"        QWidget#bottomBar {\n"
"          background-color: #1e1e3f;\n"
"          border-top: 1px solid #2d2d4e;\n"
"          padding: 6px;\n"
"        }\n"
"       ", nullptr));
        timeLabel->setText(QCoreApplication::translate("MainWindow", "00:00 / 00:00", nullptr));
        timeLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 11px; color: #6b6b8a;", nullptr));
        progressSlider->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"             QSlider::groove:horizontal { background: #2d2d4e; height: 4px; border-radius: 2px; }\n"
"             QSlider::handle:horizontal { background: #8b8b9e; width: 10px; height: 10px; margin: -3px 0; border-radius: 5px; }\n"
"             QSlider::sub-page:horizontal { background: #8b8b9e; border-radius: 2px; }\n"
"            ", nullptr));
        modeBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: transparent; color: #8b8b9e; border: none; font-size: 12px; padding: 4px 8px; } QPushButton:hover { color: #ffffff; }", nullptr));
        modeBtn->setText(QCoreApplication::translate("MainWindow", "\351\241\272\345\272\217\346\222\255\346\224\276", nullptr));
        prevBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: transparent; color: #8b8b9e; border: none; font-size: 16px; } QPushButton:hover { color: #ffffff; }", nullptr));
        prevBtn->setText(QCoreApplication::translate("MainWindow", "|\342\227\200", nullptr));
        playPauseBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: #2d2d4e; color: #8b8b9e; border: none; border-radius: 23px; font-size: 18px; font-weight: bold; } QPushButton:hover { background-color: #3d3d5e; color: #ffffff; }", nullptr));
        playPauseBtn->setText(QCoreApplication::translate("MainWindow", "\342\226\266", nullptr));
        nextBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: transparent; color: #8b8b9e; border: none; font-size: 16px; } QPushButton:hover { color: #ffffff; }", nullptr));
        nextBtn->setText(QCoreApplication::translate("MainWindow", "\342\226\266|", nullptr));
        volumeIconLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\224\212", nullptr));
        volumeIconLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 12px;", nullptr));
        volumeSlider->setStyleSheet(QCoreApplication::translate("MainWindow", "\n"
"               QSlider::groove:horizontal { background: #2d2d4e; height: 3px; border-radius: 1px; }\n"
"               QSlider::handle:horizontal { background: #8b8b9e; width: 8px; height: 8px; margin: -3px 0; border-radius: 4px; }\n"
"               QSlider::sub-page:horizontal { background: #8b8b9e; border-radius: 1px; }\n"
"              ", nullptr));
        volumeValueLabel->setText(QCoreApplication::translate("MainWindow", "100%", nullptr));
        volumeValueLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 11px; color: #6b6b8a;", nullptr));
        openBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: transparent; color: #8b8b9e; border: none; font-size: 12px; padding: 4px 8px; } QPushButton:hover { color: #ffffff; }", nullptr));
        openBtn->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\346\255\214\346\233\262", nullptr));
        togglePlaylistBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: transparent; color: #8b8b9e; border: none; font-size: 14px; } QPushButton:hover { color: #ffffff; }", nullptr));
        togglePlaylistBtn->setText(QCoreApplication::translate("MainWindow", "\342\211\241", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
