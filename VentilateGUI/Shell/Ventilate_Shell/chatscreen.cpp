#include "chatscreen.h"
#include "ui_chatscreen.h"
#include <QDateTime>
#include <QListWidget>
#include <QPlainTextEdit>
#include <QPushButton>

chatscreen::chatscreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatscreen)
{
    ui->setupUi(this);
}

chatscreen::~chatscreen()
{
    delete ui;
}

void chatscreen::on_btnSend_clicked()
{
    ui->lstChatscreen->addItem(+ "<" + QDateTime::currentDateTime().toString("MM/dd/yyyy") + "> " + ui->ptxtMessagebox->toPlainText());
}

void chatscreen::on_btnClear_clicked()
{
    ui->ptxtMessagebox->clear();
    ui->ptxtMessagebox->setFocus();
}
