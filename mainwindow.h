#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "chart.h"

struct SerieId{
    Serie* serie;
    int id;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::vector<Chart> charts;
    std::vector<SerieId> series;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
