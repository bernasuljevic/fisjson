#include "printwidget.h"
#include <QPainter>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QFontMetrics>
#include <QDir>

// Virgüllü sayı formatı için yardımcı fonksiyon
QString toCommaNumber(double number) {
    QString str = QString::number(number, 'f', 2);
    return str.replace('.', ',');
}

// Satırda solda ve sağda metin çizmek için
void drawSeparatedLine(QPainter &painter, int &y, const QString &left, const QString &right, int width) {
    QFontMetrics metrics(painter.font());
    int padding = 10;
    painter.drawText(padding, y, left);
    int rightWidth = metrics.horizontalAdvance(right);
    painter.drawText(width - rightWidth - padding, y, right);
    y += metrics.height() + 5;
}

// Yapıcı fonksiyon
PrintWidget::PrintWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(400, 300);
}

// Paint işlemi
void PrintWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QFont font("Arial", 12);
    painter.setFont(font);
    painter.setPen(QColorConstants::Svg::purple);

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

    drawCentered(company);
    drawCentered(address);
    drawCentered("Tel: " + phone);
    drawCentered(taxOffice);
    drawCentered("MERSIS NO: " + mersisNo);
    drawCentered("EPDK: " + epdk);
    drawCentered("ADA NO: " + adaNo);
    drawSeparatedLine(painter, y, date, time, w);
    drawSeparatedLine(painter, y, "FİŞ NO:", receiptNo, w);

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
    drawSeparatedLine(painter, y, name, "", w);
    drawSeparatedLine(painter, y, "%", vat, w);
    drawCentered(QString(w, '-'));
    drawSeparatedLine(painter, y, "KDV", vat2Str, w);
    drawSeparatedLine(painter, y, "TOPLAM:", total, w);
    drawSeparatedLine(painter, y, "NAKİT", payment, w);

    drawSeparatedLine(painter, y, "EKÜ NO: " + eku_no, "Z NO: " + zno, w);
    drawCentered("BCK " + bck);
}
