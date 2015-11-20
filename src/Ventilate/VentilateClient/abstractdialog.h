#ifndef ABSTRACTDIALOG_H
#define ABSTRACTDIALOG_H

#include <QDialog>
#include <QObject>

class AbstractDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AbstractDialog(QWidget *parent = 0);
    virtual ~AbstractDialog();

signals:

public slots:
    virtual void response(QString response) = 0;
};

#endif // ABSTRACTDIALOG_H
