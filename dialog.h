#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;

private slots:
    void numPressed();
    void unaryPressed();
    void binaryPressed();

    void on_btnUndo_clicked();
    void on_btnC_clicked();
    void on_btnEql_clicked();

};
#endif // DIALOG_H
