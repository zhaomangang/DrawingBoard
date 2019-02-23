#include "drawwidget.h"
#include "ui_drawwidget.h"
#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QMessageBox>
#include <QColorDialog>
#include <QFileDialog>
#include <QLineEdit>
#include <QBrush>
DrawWidget::DrawWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawWidget)
{

    ui->setupUi(this);
    image=QImage(this->size().width()-320,this->size().height(),QImage::Format_RGB32);
    //image=QImage(980,780,QImage::Format_RGB32);//设定一张采用32位图（最常用的）的规模为900*600的画布
    setting_color=qRgb(255,255,255);//选定背景色为白色
    image.fill(setting_color);//将背景色填充在画布上
    tempImage = image;

    drawing = false;
    shape = 0;
    ui->shape->setChecked(true);
    width = 0;
    heigh = 0;
    for(int i=0;i<3;i++)
    {
        pointPolygon[i].setX(0);
        pointPolygon[i].setY(0);
    }
    lineEdit.setParent(this);
    lineEdit.resize(70,20);
    lineEdit.setText(" ");
    lineEdit.setVisible(false);
   // ui->lineEdit->show()


}

DrawWidget::~DrawWidget()
{
    delete ui;
}
void DrawWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(drawing == true)
    {

        painter.drawImage(0,0,tempImage);   //鼠标按住但在拖动时在临时画布上画
    }
    else {
        painter.drawImage(0,0,image);//在image上绘画
    }
    //lineEdit.setVisible(false);

}

void DrawWidget::paint(QImage &theImage)
{
    QPainter thePainter(&theImage);
    QPen pen;

    pen.setWidth(ui->penWidth->value());
    pen.setColor(penColor);


    //draw
    thePainter.setPen(pen);
    //shape = 4;
   // tempImage.fill(setting_color);
    switch (shape) {
    case 0:thePainter.drawLine(change,point);change = point;break;
    case 1:thePainter.drawLine(from,point);break;   //thePainter.drawLine(from,to);break;
    case 2:thePainter.drawRect(from.x(),from.y(),width,heigh);break;
    case 3:thePainter.eraseRect(point.x(),point.y(),ui->penWidth->value()+5,ui->penWidth->value()+5);break;
    case 4:thePainter.drawPolygon(pointPolygon,3);break;
    case 5:
                lineEdit.move(point.x(),point.y());
                lineEdit.setVisible(true);
                thePainter.drawText(change,lineEdit.text());
                lineEdit.clear();
                if(lineEdit.text()!="")
                {
                    lineEdit.setVisible(false);
                }
            break;


    default:break;
    }

    thePainter.end(); //结束绘图
    update();

}

void DrawWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        drawing = true;
        point = event->pos();
        from = event->pos();
        change = event->pos();
        width=0;heigh=0;
        pointPolygon[0]=point;
        pointPolygon[1].setX(point.x());

    }


}

void DrawWidget::mouseMoveEvent(QMouseEvent *event)
{
        point = event->pos();
        width = point.x()-from.x();
        heigh = point.y()-from.y();
        pointPolygon[1].setY(point.y());
        pointPolygon[2]=point;

        tempImage = image;
        if(shape == 0||shape==3)
        {
            paint(image);
        }
        else {
            paint(tempImage);
        }


}

void DrawWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        to = event->pos();
        point = event->pos();
        width = to.x()-from.x();
        heigh = to.y()-from.y();
        pointPolygon[2]=point;

        drawing = false;
        paint(image);

    }


}

void DrawWidget::on_radioButton_clicked()
{
    shape = 1;
}

void DrawWidget::on_radioButton_2_clicked()
{
    shape = 2;
}



void DrawWidget::on_pushButton_clicked()
{
    QColorDialog color;//调出颜色选择器对话框
        penColor = color.getRgba();

}

void DrawWidget::on_shape_clicked()
{
    shape = 0;
}

void DrawWidget::on_radioButton_3_clicked()
{
    shape = 3;
}

void DrawWidget::on_pushButton_2_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,
        tr("Save Image"),
        "",
        tr("*.bmp;; *.png;; *.jpg;; *.tif;; *.GIF")); //选择路径
    if(filename.isEmpty())
    {
        return;
    }
    else
    {
        if(! (image.save(filename) ) ) //保存图像
        {
            QMessageBox::information(this,
                tr("Failed to save the image"),
                tr("Failed to save the image!"));
            return;
        }
    }
}

void DrawWidget::on_radioButton_4_clicked()
{
    shape = 4;
}

void DrawWidget::on_pushButton_3_clicked()
{
    image.fill(setting_color);//将背景色填充在画布上
    update();
}

void DrawWidget::on_radioButton_5_clicked()
{
    shape = 5;
}
