#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <condition_variable>

#ifndef _WIN32
#include "x11.h"
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, std::condition_variable* p = nullptr);

#ifndef _WIN32
    explicit MainWindow(X11* x11, std::condition_variable* p = nullptr);
#endif

    ~MainWindow();

    bool quit = false;
    bool set_previous_gamma = true;
    bool ignore_closeEvent = true;

    void updateBrLabel();
    void updatePollingSlider(int, int);

    bool run = true;
    bool* force = nullptr;
    std::condition_variable* pausethr = nullptr;

private slots:
    void init();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    void on_minBrSlider_valueChanged(int val);
    void on_maxBrSlider_valueChanged(int val);
    void on_offsetSlider_valueChanged(int val);
    void on_speedSlider_valueChanged(int val);
    void on_tempSlider_valueChanged(int val);
    void on_thresholdSlider_valueChanged(int val);
    void on_pollingSlider_valueChanged(int val);

    void on_closeButton_clicked();
    void on_hideButton_clicked();

    void on_autoCheck_stateChanged(int arg1);

    void on_manBrSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon* trayIcon;
    QMenu* createMenu();
    void toggleSliders(bool show);

#ifdef _WIN32
    QPoint mouse;
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    bool windowPressed = false;
#endif

    void closeEvent(QCloseEvent *);

    #ifndef _WIN32
        X11* x11;
    #endif
};

#endif // MAINWINDOW_H