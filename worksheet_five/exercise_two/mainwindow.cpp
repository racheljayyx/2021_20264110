// mainwindow.cpp ------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stockitem.h"
#include "edititemdialog.h"
#include "stockitemlistmodel.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QAction>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Link the ListModel to the ListView

    ui->listView->setModel( &stockList );
    // Tell this list view to only accept single selections

    ui->listView->setSelectionBehavior( QAbstractItemView::SelectItems );

    // Connect the released() signal of the addButton object to the handleAddButton slot in this object
    connect( ui->add_button, &QPushButton::released, this, &MainWindow::handle_add_button );
    connect( ui->edit_button, &QPushButton::released, this, &MainWindow::handle_edit_button );
    connect( ui->remove_button, &QPushButton::released, this, &MainWindow::handle_remove_button );
    connect( ui->insert_button, &QPushButton::released, this, &MainWindow::handle_insert_button );

    connect( this, &MainWindow::statusUpdateMessage, ui->statusBar, &QStatusBar::showMessage );


    connect( ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile );

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handle_add_button()
{
    StockItem item;
    stockList.addItem( item );
    emit statusUpdateMessage( QString("Add button was clicked"), 0 );
}

void MainWindow::handle_edit_button()
{
    EditItemDialog dialog( this );
    QModelIndexList selectedList;
    selectedList = ui->listView->selectionModel()->selectedIndexes();
    if( selectedList.length() == 1 )
    {
        // selectedList is a list of all selected items in the listView. Since we set its
        // behaviour to single selection, were only interested in the first selecteded item.
        StockItem item = stockList.getItem( selectedList[0] );
        if( dialog.runDialog( item ) )
        {
            // user clicked ok, need to update item in list...
            stockList.setItem( item, selectedList[0] );
        }
    }
    else
    {

        emit statusUpdateMessage( QString("No item selected to edit!"), 0 );
    }
}

void MainWindow::handle_remove_button()
{
    EditItemDialog dialog( this );
    QModelIndexList selectedList;
    selectedList = ui->listView->selectionModel()->selectedIndexes();

    stockList.removeItem(selectedList[0]);

    // This causes MainWindow to emit the signal that will then be
    // received by the statusbar's slot
    emit statusUpdateMessage( QString("Remove button was clicked"), 0 );
}

void MainWindow::handle_insert_button()
{
    StockItem item;
    EditItemDialog dialog( this );
    QModelIndexList selectedList;
    selectedList = ui->listView->selectionModel()->selectedIndexes();

    stockList.insertItem( item, selectedList[0]);
    emit statusUpdateMessage( QString("Insert above button was clicked"), 0 );

}

void MainWindow::saveFile()
{
    //this actually doesnt save the file it creates the save as dialouge box we usually see.
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), "/data", tr("Text Files (*.txt)"));

    QFile file(filename);

      if (file.open(QFile::WriteOnly))
      {
          QTextStream out(&file);
          for (int i=0; i < stockList.getItemTotalNum(); i++ )
          {
              out << "------------------------------------------ \n";
              out << stockList.getItems(i).getName()<< "\n";
              out << stockList.getItems(i).getUnitCost()<< "\n";
              out << stockList.getItems(i).getStockLevel()<< "\n";
              out << stockList.getItems(i).getStockLevel()<< "\n";
              out << "------------------------------------------ \n";
          }



       }

}

// ---------------------------------------------------------------------

