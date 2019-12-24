#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinBox_valueChanged(int value);
    void on_spinBoxPages_valueChanged(int value);

    void calcPages();

    QVector<QVector<int>> calcBase(int sheets);
    QVector<QVector<int>> addPrinted(const QVector<QVector<int>> &base, int printed);

    QString baseToString(const QVector<QVector<int>> &base);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
