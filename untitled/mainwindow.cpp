#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QPixmap>
#include <QRandomGenerator>
#include <QAudioOutput>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QScrollBar>
#include <QPainter>
#include <QPainterPath>
#include <QTransform>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentLyricIndex(-1)
    , lyricOffset(1000)  // 歌词延迟1秒，解决歌词快于演唱的问题
    , rotationAngle(0.0)
    , isSwitching(false)
{
    ui->setupUi(this);

    // 创建媒体播放器与音频输出
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);

    // 音量控制 - 手动连接，避免自动连接冲突
    connect(ui->volumeSlider, &QSlider::valueChanged, this, &MainWindow::onVolumeChanged);

    // 进度条 - 只响应用户拖动（sliderMoved），不响应programmatic setValue
    connect(ui->progressSlider, &QSlider::sliderMoved, this, [this](int value){
        player->setPosition(value);
    });

    // 初始化音量滑块
    ui->volumeSlider->setValue(100);
    ui->volumeValueLabel->setText("100%");

    currentIndex = 0;
    playMode = ORDER_PLAY;
    ui->modeBtn->setText("顺序播放");

    // 自动扫描音乐文件夹
    QDir musicDir("D:/AAAAAAwork base/music/music");
    if(musicDir.exists())
    {
        QStringList filters;
        filters << "*.mp3" << "*.wav" << "*.flac" << "*.m4a" << "*.ogg";
        musicDir.setNameFilters(filters);

        QStringList fileList = musicDir.entryList(QDir::Files);

        for(const QString &fileName : fileList)
        {
            QString fullPath = musicDir.absoluteFilePath(fileName);
            musicList << fullPath;
            qDebug() << "找到歌曲:" << fullPath;
        }
    }

    audioOutput->setVolume(1.0);

    // 如果找到了歌曲，加载第一首
    if(!musicList.isEmpty())
    {
        currentIndex = 0;
        player->setSource(QUrl::fromLocalFile(musicList[currentIndex]));
        updateCurrentSongLabel();
        loadLyrics(musicList[currentIndex]);
        loadAlbumArt(musicList[currentIndex]);
        qDebug() << "共加载" << musicList.size() << "首歌曲";
    }
    else
    {
        ui->currentSongLabel->setText("请点击\"添加歌曲\"选择音乐");
    }

    // 连接信号
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::on_durationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::on_positionChanged);
    connect(player, &QMediaPlayer::playbackStateChanged, this, &MainWindow::on_playbackStateChanged);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::on_mediaStatusChanged);

    // 歌词列表样式
    ui->lyricListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->lyricListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->lyricListWidget->setFocusPolicy(Qt::NoFocus);
    ui->lyricListWidget->setSelectionMode(QAbstractItemView::NoSelection);

    // 播放列表：双击切歌
    connect(ui->playlistWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::onPlaylistItemDoubleClicked);

    // 封面旋转定时器
    rotateTimer = new QTimer(this);
    connect(rotateTimer, &QTimer::timeout, this, &MainWindow::rotateAlbumArt);
    rotateTimer->setInterval(50); // 每50ms旋转一次

    // 刷新播放列表
    refreshPlaylist();

    updateCurrentSongLabel();
}

MainWindow::~MainWindow()
{
    rotateTimer->stop();
    delete player;
    delete audioOutput;
    delete ui;
}

QString formatTime(qint64 ms)
{
    qint64 sec = ms / 1000;
    int min = sec / 60;
    int s = sec % 60;
    return QString("%1:%2")
        .arg(min, 2, 10, QLatin1Char('0'))
        .arg(s, 2, 10, QLatin1Char('0'));
}

void MainWindow::on_durationChanged(qint64 duration)
{
    totalTime = duration;
    ui->progressSlider->blockSignals(true);
    ui->progressSlider->setRange(0, totalTime);
    ui->progressSlider->blockSignals(false);
}

void MainWindow::on_positionChanged(qint64 pos)
{
    // 更新进度条
    ui->progressSlider->blockSignals(true);
    ui->progressSlider->setValue(pos);
    ui->progressSlider->blockSignals(false);
    ui->timeLabel->setText(formatTime(pos) + " / " + formatTime(totalTime));

    // 更新歌词显示
    updateLyricDisplay(pos);

    // 检测歌曲即将结束（剩余不到500ms），触发切歌
    if(totalTime > 1000 && pos >= totalTime - 500
       && player->playbackState() == QMediaPlayer::PlayingState
       && !isSwitching)
    {
        qDebug() << "=== 即将切歌 === pos:" << pos << "totalTime:" << totalTime << "mode:" << playMode;
        playNext();
    }
}

void MainWindow::on_playbackStateChanged(QMediaPlayer::PlaybackState state)
{
    if(state == QMediaPlayer::PlayingState)
    {
        ui->playPauseBtn->setText("||");
        rotateTimer->start();
    }
    else
    {
        ui->playPauseBtn->setText("▶");
        rotateTimer->stop();
    }
}

void MainWindow::onVolumeChanged(int value)
{
    audioOutput->setVolume(value / 100.0);
    ui->volumeValueLabel->setText(QString::number(value) + "%");
}

void MainWindow::on_modeBtn_clicked()
{
    if(playMode == ORDER_PLAY)
    {
        playMode = SINGLE_LOOP;
        ui->modeBtn->setText("单曲循环");
    }
    else if(playMode == SINGLE_LOOP)
    {
        playMode = RANDOM_PLAY;
        ui->modeBtn->setText("随机播放");
    }
    else if(playMode == RANDOM_PLAY)
    {
        playMode = ORDER_PLAY;
        ui->modeBtn->setText("顺序播放");
    }
}

void MainWindow::on_playPauseBtn_clicked()
{
    if(musicList.isEmpty())
    {
        QMessageBox::information(this, "提示", "请先点击\"添加歌曲\"选择音乐文件。");
        return;
    }
    if(player->playbackState() == QMediaPlayer::PlayingState)
    {
        player->pause();
    }
    else
    {
        player->play();
    }
    updateCurrentSongLabel();
}

void MainWindow::on_prevBtn_clicked()
{
    if(musicList.isEmpty()) return;

    if(playMode == RANDOM_PLAY)
    {
        // 随机模式：随机切一首
        if(musicList.size() > 1)
        {
            int newIndex = currentIndex;
            while(newIndex == currentIndex)
                newIndex = QRandomGenerator::global()->bounded(0, musicList.size());
            currentIndex = newIndex;
        }
    }
    else
    {
        // 顺序/单曲循环：正常切上一首
        if(currentIndex > 0)
            currentIndex--;
        else
            currentIndex = musicList.size() - 1;
    }

    player->stop();
    player->setSource(QUrl());
    player->setSource(QUrl::fromLocalFile(musicList[currentIndex]));
    player->play();
    updateCurrentSongLabel();
    loadLyrics(musicList[currentIndex]);
    loadAlbumArt(musicList[currentIndex]);
}

void MainWindow::on_nextBtn_clicked()
{
    if(musicList.isEmpty()) return;

    if(playMode == RANDOM_PLAY)
    {
        // 随机模式：随机切一首
        if(musicList.size() > 1)
        {
            int newIndex = currentIndex;
            while(newIndex == currentIndex)
                newIndex = QRandomGenerator::global()->bounded(0, musicList.size());
            currentIndex = newIndex;
        }
    }
    else
    {
        // 顺序/单曲循环：正常切下一首
        if(currentIndex < musicList.size() - 1)
            currentIndex++;
        else
            currentIndex = 0;
    }

    player->stop();
    player->setSource(QUrl());
    player->setSource(QUrl::fromLocalFile(musicList[currentIndex]));
    player->play();
    updateCurrentSongLabel();
    loadLyrics(musicList[currentIndex]);
    loadAlbumArt(musicList[currentIndex]);
}

void MainWindow::on_openBtn_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(
        this, "添加歌曲", QString(), "音频文件 (*.mp3 *.wav *.flac *.ogg *.m4a)");
    if(files.isEmpty())
        return;

    musicList.append(files);
    refreshPlaylist();

    // 如果当前没有在播放任何歌曲，加载第一首新添加的
    if(player->playbackState() == QMediaPlayer::StoppedState
       && player->mediaStatus() == QMediaPlayer::NoMedia)
    {
        currentIndex = musicList.size() - files.size();
        if(currentIndex < 0) currentIndex = 0;
        player->setSource(QUrl::fromLocalFile(musicList[currentIndex]));
        updateCurrentSongLabel();
        loadLyrics(musicList[currentIndex]);
        loadAlbumArt(musicList[currentIndex]);
    }
}


void MainWindow::updateCurrentSongLabel()
{
    if(currentIndex >= 0 && currentIndex < musicList.size())
    {
        QFileInfo fi(musicList[currentIndex]);
        ui->currentSongLabel->setText(fi.completeBaseName());
    }
    else
    {
        ui->currentSongLabel->setText("未选择歌曲");
    }
    highlightCurrentPlaylistItem();
}

void MainWindow::on_mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if(status == QMediaPlayer::NoMedia)
    {
        ui->currentSongLabel->setText("未选择歌曲");
    }
    else if(status == QMediaPlayer::EndOfMedia)
    {
        if(!isSwitching)
        {
            // 延迟到下一个事件循环执行，避免在信号处理中直接操作player
            QTimer::singleShot(100, this, &MainWindow::playNext);
        }
    }
}

// ===== 统一切歌逻辑 =====
void MainWindow::playNext()
{
    if(musicList.isEmpty()) return;
    isSwitching = true;
    totalTime = 0;  // 立即重置，防止positionChanged再次触发

    qDebug() << "playNext() 触发, 当前模式:" << playMode << ", 当前索引:" << currentIndex;

    if(playMode == SINGLE_LOOP)
    {
        // 单曲循环：重新播放当前歌曲
        player->stop();
        player->setSource(QUrl());
        player->setSource(QUrl::fromLocalFile(musicList[currentIndex]));
        player->play();
        qDebug() << "单曲循环: 重新播放" << musicList[currentIndex];
    }
    else if(playMode == RANDOM_PLAY)
    {
        // 随机播放：随机选一首不同的歌
        if(musicList.size() > 1)
        {
            int newIndex = currentIndex;
            while(newIndex == currentIndex)
                newIndex = QRandomGenerator::global()->bounded(0, musicList.size());
            currentIndex = newIndex;
        }
        player->stop();
        player->setSource(QUrl());
        player->setSource(QUrl::fromLocalFile(musicList[currentIndex]));
        player->play();
        updateCurrentSongLabel();
        loadLyrics(musicList[currentIndex]);
        loadAlbumArt(musicList[currentIndex]);
        qDebug() << "随机播放: 切换到" << musicList[currentIndex];
    }
    else // ORDER_PLAY
    {
        if(currentIndex < musicList.size() - 1)
            currentIndex++;
        else
            currentIndex = 0;
        player->stop();
        player->setSource(QUrl());
        player->setSource(QUrl::fromLocalFile(musicList[currentIndex]));
        player->play();
        updateCurrentSongLabel();
        loadLyrics(musicList[currentIndex]);
        loadAlbumArt(musicList[currentIndex]);
        qDebug() << "顺序播放: 切换到" << musicList[currentIndex];
    }

    // 延迟重置标志
    QTimer::singleShot(2000, this, [this]() { isSwitching = false; });
}

// ===== 收起/展开播放列表 =====
void MainWindow::on_togglePlaylistBtn_clicked()
{
    bool visible = ui->playlistWidget->isVisible();
    ui->playlistWidget->setVisible(!visible);
}

// ===== 歌词解析 =====
void MainWindow::loadLyrics(const QString &musicFilePath)
{
    lyrics.clear();
    currentLyricIndex = -1;
    ui->lyricListWidget->clear();

    // 根据音乐文件路径找对应的 .lrc 文件
    QFileInfo fi(musicFilePath);
    QString lrcPath = fi.absolutePath() + "/" + fi.completeBaseName() + ".lrc";

    QFile file(lrcPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QListWidgetItem *item = new QListWidgetItem("暂无歌词");
        item->setTextAlignment(Qt::AlignCenter);
        ui->lyricListWidget->addItem(item);
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    QRegularExpression timeRegex("\\[(\\d{2}):(\\d{2})\\.(\\d{2,3})\\](.*)");

    while(!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        QRegularExpressionMatch match = timeRegex.match(line);
        if(match.hasMatch())
        {
            int min = match.captured(1).toInt();
            int sec = match.captured(2).toInt();
            int ms = match.captured(3).toInt();
            if(match.captured(3).length() == 2)
                ms *= 10; // 两位数转为毫秒

            qint64 time = min * 60000 + sec * 1000 + ms;
            QString text = match.captured(4).trimmed();
            if(text.isEmpty()) text = "...";

            LyricLine lyricLine;
            lyricLine.time = time;
            lyricLine.text = text;
            lyrics.append(lyricLine);
        }
    }
    file.close();

    // 按时间排序
    std::sort(lyrics.begin(), lyrics.end(), [](const LyricLine &a, const LyricLine &b){
        return a.time < b.time;
    });

    // 填充歌词列表
    for(const LyricLine &l : lyrics)
    {
        QListWidgetItem *item = new QListWidgetItem(l.text);
        item->setTextAlignment(Qt::AlignCenter);
        ui->lyricListWidget->addItem(item);
    }
}

// ===== 歌词滚动同步 =====
void MainWindow::updateLyricDisplay(qint64 position)
{
    if(lyrics.isEmpty()) return;

    // 减去偏移量，让歌词显示延迟（解决歌词快于演唱）
    qint64 adjustedPos = position - lyricOffset;
    if(adjustedPos < 0) adjustedPos = 0;

    int newIndex = -1;
    for(int i = 0; i < lyrics.size(); i++)
    {
        if(lyrics[i].time <= adjustedPos)
            newIndex = i;
        else
            break;
    }

    if(newIndex == currentLyricIndex) return;

    // 恢复上一行样式
    if(currentLyricIndex >= 0 && currentLyricIndex < ui->lyricListWidget->count())
    {
        QListWidgetItem *prevItem = ui->lyricListWidget->item(currentLyricIndex);
        prevItem->setForeground(QColor("#aaaaaa"));
        QFont font = prevItem->font();
        font.setPointSize(10);
        font.setBold(false);
        prevItem->setFont(font);
    }

    currentLyricIndex = newIndex;

    // 高亮当前行
    if(currentLyricIndex >= 0 && currentLyricIndex < ui->lyricListWidget->count())
    {
        QListWidgetItem *curItem = ui->lyricListWidget->item(currentLyricIndex);
        curItem->setForeground(QColor("#ffffff"));
        QFont font = curItem->font();
        font.setPointSize(13);
        font.setBold(true);
        curItem->setFont(font);

        // 滚动到当前歌词（居中显示）
        ui->lyricListWidget->scrollToItem(curItem, QAbstractItemView::PositionAtCenter);
    }
}

// ===== 加载封面图片 =====
void MainWindow::loadAlbumArt(const QString &musicFilePath)
{
    QFileInfo fi(musicFilePath);
    QString baseName = fi.completeBaseName(); // 不含后缀的文件名
    QString dir = fi.absolutePath();

    // 尝试多种图片格式
    QStringList imgExts = {"jpg", "jpeg", "png", "bmp", "webp"};
    QPixmap pix;
    for(const QString &ext : imgExts)
    {
        QString imgPath = dir + "/" + baseName + "." + ext;
        pix = QPixmap(imgPath);
        if(!pix.isNull())
        {
            qDebug() << "加载封面:" << imgPath;
            break;
        }
    }

    if(pix.isNull())
    {
        // 没找到封面，显示默认
        qDebug() << "未找到封面图片，尝试路径:" << dir + "/" + baseName + ".jpg";
        ui->albumArtLabel->setText("🎵");
        albumPixmap = QPixmap();
        return;
    }

    // 裁剪为正方形
    int size = qMin(pix.width(), pix.height());
    pix = pix.copy((pix.width() - size) / 2, (pix.height() - size) / 2, size, size);
    albumPixmap = pix.scaled(260, 260, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 制作圆形封面显示
    rotationAngle = 0.0;
    rotateAlbumArt();
}

// ===== 旋转封面 =====
void MainWindow::rotateAlbumArt()
{
    if(albumPixmap.isNull()) return;

    int diameter = 260;
    QPixmap result(diameter, diameter);
    result.fill(Qt::transparent);

    QPainter painter(&result);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // 裁剪为圆形
    QPainterPath clipPath;
    clipPath.addEllipse(0, 0, diameter, diameter);
    painter.setClipPath(clipPath);

    // 旋转绘制
    painter.translate(diameter / 2, diameter / 2);
    painter.rotate(rotationAngle);
    painter.translate(-diameter / 2, -diameter / 2);
    painter.drawPixmap(0, 0, diameter, diameter, albumPixmap);
    painter.end();

    ui->albumArtLabel->setPixmap(result);
    ui->albumArtLabel->setText("");

    // 增加角度
    rotationAngle += 0.5;
    if(rotationAngle >= 360.0)
        rotationAngle -= 360.0;
}

// ===== 刷新播放列表 =====
void MainWindow::refreshPlaylist()
{
    ui->playlistWidget->clear();
    for(int i = 0; i < musicList.size(); i++)
    {
        QFileInfo fi(musicList[i]);
        QString songName = fi.completeBaseName();

        // 尝试加载缩略封面
        QString imgPath = fi.absolutePath() + "/" + songName + ".jpg";
        QPixmap thumb(imgPath);
        if(thumb.isNull())
        {
            // 尝试 png
            imgPath = fi.absolutePath() + "/" + songName + ".png";
            thumb = QPixmap(imgPath);
        }

        QListWidgetItem *item = new QListWidgetItem();
        item->setText(songName);
        item->setData(Qt::UserRole, i); // 存储索引

        if(!thumb.isNull())
        {
            // 缩放为 36x36 的缩略图
            QPixmap scaled = thumb.scaled(36, 36, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
            // 裁剪为正方形
            int x = (scaled.width() - 36) / 2;
            int y = (scaled.height() - 36) / 2;
            scaled = scaled.copy(x, y, 36, 36);
            item->setIcon(QIcon(scaled));
        }
        else
        {
            // 默认图标
            QPixmap defaultIcon(36, 36);
            defaultIcon.fill(QColor("#2d2d4e"));
            item->setIcon(QIcon(defaultIcon));
        }

        ui->playlistWidget->addItem(item);
    }
    ui->playlistWidget->setIconSize(QSize(36, 36));
    highlightCurrentPlaylistItem();
}

// ===== 高亮当前播放歌曲 =====
void MainWindow::highlightCurrentPlaylistItem()
{
    for(int i = 0; i < ui->playlistWidget->count(); i++)
    {
        QListWidgetItem *item = ui->playlistWidget->item(i);
        if(i == currentIndex)
        {
            item->setSelected(true);
            ui->playlistWidget->scrollToItem(item);
        }
        else
        {
            item->setSelected(false);
        }
    }
}

// ===== 双击播放列表切歌 =====
void MainWindow::onPlaylistItemDoubleClicked(QListWidgetItem *item)
{
    int index = item->data(Qt::UserRole).toInt();
    if(index >= 0 && index < musicList.size())
    {
        currentIndex = index;
        player->setSource(QUrl::fromLocalFile(musicList[currentIndex]));
        player->play();
        updateCurrentSongLabel();
        loadLyrics(musicList[currentIndex]);
        loadAlbumArt(musicList[currentIndex]);
    }
}