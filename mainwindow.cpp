#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    calcPages();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_spinBox_valueChanged(int value)
{
    calcPages();
}
void MainWindow::on_spinBoxPages_valueChanged(int value)
{
    calcPages();
}
void MainWindow::calcPages()
{
    int blockSheetsCount = ui->spinBox->value();
    int pageCount = ui->spinBoxPages->value();

    ui->textEdit->clear();

    int printed = 0;
    int block = 0;
    int blockSize = blockSheetsCount * 4;
    QString text;
    for (;;) {

        int left = pageCount - printed;
        if (left >= blockSize) {
            QVector<QVector<int>> base = calcBase(blockSheetsCount);

            QVector<QVector<int>> newBase = addPrinted(base, printed);
            text += baseToString(newBase);
        } else if (left > 0) {
            blockSize = int(left / 4.0 + 1) * 4;
            QVector<QVector<int>> base = calcBase(blockSize / 4);
            QVector<QVector<int>> newBase = addPrinted(base, printed);
            text += baseToString(newBase);
            break;
        } else {
            break;
        }

        printed += blockSize;
        block++;
    }

    ui->textEdit->setText(text);
}
QVector<QVector<int>> MainWindow::calcBase(int sheets)
{
    QVector<QVector<int>> base;

    int i = 1;
    int j = sheets * 4;

    for (int k = sheets - 1; k >= 0; k--) {
        QVector<int> line;
        line.push_back(i++);
        line.push_back(i++);
        line.push_back(j--);
        line.push_back(j--);
        base.push_back(line);
    }
    return base;
}
QVector<QVector<int>> MainWindow::addPrinted(const QVector<QVector<int>>& base, int printed)
{
    QVector<QVector<int>> newBase;

    for (QVector<int> line : base) {

        QVector<int> newLine;
        for (int i : line) {
            newLine.push_back(printed + i);
        }
        newBase.push_back(newLine);
    }
    return newBase;
}
QString MainWindow::baseToString(const QVector<QVector<int>>& base)
{
    QString line1;
    QString line2;

    for (int i = 0; i < base.count(); ++i) {
        auto line = base[i];
        line1 += QString::number(line[2]) + ",";
        line1 += QString::number(line[0]);
        if (i < base.count() - 1) {
            line1 += ",";
        }
    }

    for (int i = base.count() - 1; i >= 0; --i) {
        auto line = base[i];
        line2 += QString::number(line[1]) + ",";
        line2 += QString::number(line[3]);

        if (i > 0) {
            line2 += ",";
        }
    }

    return line1 + "\n" + line2 + "\n\n";
}
