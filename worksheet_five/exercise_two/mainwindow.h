#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stockitemlistmodel.h"

#include <QMainWindow>


namespace Ui 
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    StockItemListModel stockList;


 // used to print text in status bar rather than a box see exercise 4 worksheet 5
 signals:
     void statusUpdateMessage( const QString & message, int timeout );



public slots:
    void handle_add_button();
    void handle_edit_button();
    void handle_remove_button();
    void handle_insert_button();
    void saveFile();


};

#endif // MAINWINDOW_H
