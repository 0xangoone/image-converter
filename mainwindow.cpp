#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}
inline void MainWindow::show_msg(const QString str) {
    QMessageBox *msg = new QMessageBox(this);
    msg->setText(str);
    msg->show();
}
void MainWindow::on_pushButton_2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                tr("افتح صورة"), nullptr, tr("Image Files (*.png *.jpg *.bmp *.jfif *.jpeg *.)"));
    this->input_path = filename;
}
void MainWindow::on_pushButton_clicked()
{
    QString path = ui->lineEdit->text();
    if (path .isNull() ||path .isEmpty()){
        show_msg("اكتب اسم الملف المخرج لو سمحت");
    }
    if (this->input_path.isEmpty() || this->input_path.isNull()){
        show_msg("اختر ملفا لو سمحت");
        return;
    }
    if (this->save_path.isEmpty() || this->save_path.isNull()){
        show_msg("اختر مسار لمجلد الحفظ لو سمحت");
        return;
    }
    try{
        QString output_path = this->save_path + "/" + path;
        cv::Mat image = cv::imread(this->input_path.toStdString());
        cv::imwrite(output_path.toStdString(),image);
        show_msg(u8"تم حفظ");
    }catch(...){
        show_msg(u8"خطا غبي مثلك");
        return;
    }
}
void MainWindow::on_pushButton_3_clicked()
{
    QString path_name = QFileDialog::getExistingDirectory(this);
    this->save_path = path_name;
}

