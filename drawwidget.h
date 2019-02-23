#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QPoint>
#include <QLineEdit>

namespace Ui {
class DrawWidget;
}

class DrawWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawWidget(QWidget *parent = nullptr);
    ~DrawWidget();
    void paint(QImage &theImage);
    QColor penColor;
private:
    Ui::DrawWidget *ui;
    QImage image;   //
    QImage tempImage;
    QRgb setting_color;//背景色

    bool drawing;
    int shape;
    QPoint point;
    QPoint from;
    QPoint to;
    QPoint change;
    QPoint pointPolygon[3];
    int width,heigh;
    QLineEdit lineEdit;



protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private slots:
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_pushButton_clicked();
    void on_shape_clicked();
    void on_radioButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_radioButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_radioButton_5_clicked();
};

#endif // DRAWWIDGET_H
