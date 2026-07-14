#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QMainWindow>
#include <QUrl>
#include <QStringList>
#include <QMap>
#include <QListWidget>
#include <QTimer>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum PlayMode
{
    ORDER_PLAY,     //顺序播放
    SINGLE_LOOP,    //单曲循环
    RANDOM_PLAY     //随机播放
};

// 歌词行结构
struct LyricLine {
    qint64 time;    // 毫秒
    QString text;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_playPauseBtn_clicked();
    void on_prevBtn_clicked();
    void on_nextBtn_clicked();
    void on_modeBtn_clicked();
    void on_openBtn_clicked();  // 改名为"添加歌曲"
    void on_playbackStateChanged(QMediaPlayer::PlaybackState state);
    void on_mediaStatusChanged(QMediaPlayer::MediaStatus status);

    void on_durationChanged(qint64 duration);
    void on_positionChanged(qint64 pos);

    void updateCurrentSongLabel();
    void onVolumeChanged(int value);
    void rotateAlbumArt();
    void onPlaylistItemDoubleClicked(QListWidgetItem *item);
    void on_togglePlaylistBtn_clicked();

private:
    void loadLyrics(const QString &musicFilePath);
    void updateLyricDisplay(qint64 position);
    void loadAlbumArt(const QString &musicFilePath);
    void refreshPlaylist();
    void highlightCurrentPlaylistItem();
    void playNext();  // 统一切歌逻辑

    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QStringList musicList;
    QAudioOutput *audioOutput;
    int currentIndex;
    PlayMode playMode;
    qint64 totalTime;

    // 歌词相关
    QList<LyricLine> lyrics;
    int currentLyricIndex;
    qint64 lyricOffset; // 歌词时间偏移（毫秒）

    // 封面旋转相关
    QPixmap albumPixmap;
    qreal rotationAngle;
    QTimer *rotateTimer;

    // 防止重复切歌
    bool isSwitching;
};
#endif // MAINWINDOW_H