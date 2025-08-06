#include "printwidget.h"
#include <QPainter>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QFontMetrics>
#include <QDir>


QString toCommaNumber(double number) {
    QString str = QString::number(number, 'f', 2);
    return str.replace('.', ',');
}


void drawSeparatedLine(QPainter &painter, int &y, const QString &left, const QString &right, int width) {
    QFontMetrics metrics(painter.font());
    int padding = 10;
    painter.drawText(padding, y, left);
    int rightWidth = metrics.horizontalAdvance(right);
    painter.drawText(width - rightWidth - padding, y, right);
    y += metrics.height() + 5;
}


PrintWidget::PrintWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(400, 300);
}

void PrintWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QFont font("Arial", 12);
    painter.setFont(font);
    painter.setPen(QColorConstants::Svg::white);

    QFile file(":/veri.json");
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
    auto company_lines = company.split("\n");
    QString address = obj.value("address").toString();
    auto address_lines = address.split("\n");
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
    QString unitPrice = toCommaNumber(product.value("unit_price").toDouble());
    QString name = product.value("name").toString();
    QString vat = product.value("vat").toString();
    QString vat2Str = product.value("vat2").toString().replace(",", ".");
    QString total = product.value("total").toString();
    QString payment = product.value("payment_method").toString();

    QString eku_no = obj.value("eku_no").toString();
    QString zno = obj.value("z_no").toString();
    QString bck = obj.value("bck").toString();

    int y = 30;
    int w = this->width();
    QFontMetrics metrics(font);
     auto drawCentered = [&](const QString &text) {
        int textWidth = metrics.horizontalAdvance(text);
        painter.drawText((w - textWidth) / 2, y, text);
        y += metrics.height() + 5;
    };



    for(const auto& company_line : company_lines){
        drawCentered(company_line);
    }


    for(const auto& address_line : address_lines){
        drawCentered(address_line);
    }
    drawCentered("Tel: " + phone);
    drawCentered(taxOffice);
    drawCentered("MERSIS NO: " + mersisNo);
    drawCentered("EPDK: " + epdk);
    drawCentered("ADA NO: " + adaNo);
    drawSeparatedLine(painter, y, date, time, w);
    QString text = QString("FİŞ NO: %1").arg(receiptNo);
    painter.drawText(10, y, text);
    y += 20;

    font.setPointSize(16);
    font.setBold(true);
    painter.setFont(font);
    metrics = QFontMetrics(font);
    drawCentered(plaka);
    y += 5;
    painter.setFont(QFont("Arial", 12));
    metrics = QFontMetrics(painter.font());
    y += 5;
    drawSeparatedLine(painter, y, quantity + " x " + unitPrice, "", w);
    QString rightText = "%" + vat + " *" + total;
    painter.drawText(10, y, name);
    painter.drawText(w - metrics.horizontalAdvance(rightText) - 10, y, rightText);
    y += 20;
    drawCentered(QString(w, '-'));
    QString kdvLabel = "KDV";
    QString kdvValue = "*" + vat2Str;
    painter.drawText(10, y, kdvLabel);
    painter.drawText(w - metrics.horizontalAdvance(kdvValue) - 10, y, kdvValue);
    y += 20;


    QString totalLabel = "TOPLAM:";
    QString totalValue = "*" + total;
    painter.drawText(10, y, totalLabel);
    painter.drawText(w - metrics.horizontalAdvance(totalValue) - 10, y, totalValue);
    y += 20;


    QString paymentLabel = "NAKİT";
    QString paymentValue = "*" + payment;
    painter.drawText(10, y, paymentLabel);
    painter.drawText(w - metrics.horizontalAdvance(paymentValue) - 10, y, paymentValue);
    y += 20;

    drawSeparatedLine(painter, y, "EKÜ NO: " + eku_no, "Z NO: " + zno, w);
    drawCentered("BCK " + bck);
}
