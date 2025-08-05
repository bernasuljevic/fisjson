#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QDir>
#include <QDateTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadJsonAndDisplay();
}
MainWindow::~MainWindow()
{
    delete ui;
}


QString toCommaNumber(double number) {
    QString str = QString::number(number, 'f', 2);
    return str.replace('.', ',');
}

QString separatedLine(QString left, QString right = "") {
    return QString(
               "<table width='100%' style='margin-top:10px;'>"
               "<tr>"
               "<td align='left'>%1</td>"
               "<td align='right'>%2</td>"
               "</tr>"
               "</table>"
               "<div style='clear:both; margin-bottom:10px;'></div>"
               ).arg(left, right);
}

void MainWindow::loadJsonAndDisplay()
{
    QFile file("veri.json");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Cannot open JSON file!\nPath: " + QDir::currentPath());
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        QMessageBox::critical(this, "Error", "JSON parse error: " + parseError.errorString());
        return;
    }

    QJsonObject obj = doc.object();

    QString company = obj.value("company").toString();
    QString address = obj.value("address").toString();
    QString phone = obj.value("phone").toString();
    QString taxOffice = obj.value("tax_office").toString();
    QString mersisNo = obj.value("mersis_no").toString();
    QString epdk = obj.value("epdk").toString();
    QString adaNo = obj.value("ada_no").toString();
    QString date = obj.value("date").toString();
    QString time = obj.value("time").toString();
    QString receiptNo = obj.value("receipt_no").toString();
    QString plaka = obj.value("plaka").toString();

    QJsonObject product = obj.value("product").toObject();
    QString quantity = product.value("quantity").toString();
    QString unitPrice = QString::number(product.value("unit_price").toDouble(), 'f', 2);
    QString name = product.value("name").toString();
    QString vat = product.value("vat").toString();
    QString vat2Str = product.value("vat2").toString().replace(",", ".");
    QString total = product.value("total").toString();
    QString payment = product.value("payment_method").toString();
    QString paid = product.value("paid_amount").toString();

    QString eku = obj.value("eku_no").toString();
    QString zno = obj.value("z_no").toString();
    QString bck = obj.value("bck").toString();

    QString html;
    html += "<div style='text-align:center;'>" + company + "</div>";
    html += "<div style='text-align:center;'>" + address + "</div>";
    html += "<div style='text-align:center;'>Tel: " + phone + "</div>";
    html += "<div style='text-align:center;'>" + taxOffice + "</div>";
    html += "<div style='text-align:center;'>MERSIS NO: " + mersisNo + "</div>";
    html += "<div style='text-align:center;'>EPDK: " + epdk + "</div>";
    html += "<div style='text-align:center;'>ADA NO: " + adaNo + "</div>";
    html += "<hr>";

    html += separatedLine( date + "<br> " + time);
    html += separatedLine("FİŞ NO:", receiptNo);
    html += "<div style='text-align:center; font-size:20px; font-weight:bold; margin: 10px;'>" + plaka + "</div>";
    html += "<hr>";

    html += separatedLine(quantity + " x " + unitPrice);
    html += separatedLine(name);
    html += separatedLine("VAT %:", vat);
    html += separatedLine("VAT2:", vat2Str);
    html += separatedLine("TOTAL:", total);
    html += separatedLine("Payment Method:", payment);
    html += separatedLine("Paid Amount:", paid);
    html += "<hr>";
    html += separatedLine("EKUNO:", eku);
    html += separatedLine("Z NO:", zno);

    html += "<div style='text-align:center;'>BCK: " + bck + "</div>";

    ui->textBrowser->setHtml(html);
}
