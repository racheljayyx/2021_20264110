#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QAction>
#include <QFile>
#include <QTextStream>
#include <QDir>

#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkDataSetMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkSTLReader.h>
#include <vtkCylinderSource.h>
#include <vtkLight.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->qvtkWidget->SetRenderWindow(renderWindow);


    connect( ui->loadButton, &QPushButton::released, this, &MainWindow::handleLoadButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleLoadButton()
{

    // Read file into string object using QFileDialog: : getOpenFileName
    QString fileName = QFileDialog::getOpenFileName (this, tr ("Open STL File"), "./", tr ("STL Files (*.stl)"));

    //Create vtk reader object to point to the filename
    vtkNew<vtkSTLReader> reader;

    //Convert the filename from qstring to a char pointer|
    QByteArray ba = fileName.toLocal8Bit();
    const char *c_str = ba.data();
    reader->SetFileName(c_str);
    reader->Update();

    // Visualize
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(reader->GetOutputPort());

    vtkNew<vtkNamedColors> colors;

    vtkNew<vtkActor> actor;
    actor->SetMapper (mapper) ;
    actor->GetProperty()->SetDiffuse(0.8);
    actor->GetProperty()->SetDiffuseColor(
        colors->GetColor3d ("LightSteelBlue").GetData());
    actor->GetProperty()->SetSpecular(0.3);
    actor->GetProperty()->SetSpecularPower(60.0);

    //Clears the renderer window
    renderer->RemoveAllViewProps();

    //Creates a new Actor

    renderer->AddActor (actor) ;
    renderer->SetBackground (colors-›GetColor3d("Dark0liveGreen").GetData());

    // Setup the renderers's camera
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth (30) ;
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();

    renderWindow->Render);

}
