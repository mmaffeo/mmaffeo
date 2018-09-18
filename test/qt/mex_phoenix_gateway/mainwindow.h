#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *runTimer;
    bool running;
    qint64 runCount;


public slots:
    void on_pushButtonInit_clicked(void);
    void on_pushButtonRun_clicked(void);
    void run(void);

};

#endif // MAINWINDOW_H
