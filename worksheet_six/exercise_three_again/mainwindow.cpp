#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkCylinderSource.h>
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
#include <QColorDialog>

#include <QMessageBox>
#include <QFileDialog>
#include <QAction>
#include <QFile>
#include <QTextStream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    // standard call to setup Qt UI (same as previously)
    ui->setupUi( this );
	
	// Now need to create a VTK render window and link it to the QtVTK widget
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	ui->qvtkWidget->SetRenderWindow( renderWindow );			// note that vtkWidget is the name I gave to my QtVTKOpenGLWidget in Qt creator


	// Now use the VTK libraries to render something. To start with you can copy-paste the cube example code, there are comments to show where the code must be modified.
    //--------------------------------------------- Code From Example 1 --------------------------------------------------------------------------
    // Create a cube using a vtkCubeSource
    //vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();

    // Create a mapper that will hold the cube's geometry in a format suitable for rendering
    //vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    //mapper->SetInputConnection( cubeSource->GetOutputPort() );

    // Create an actor that is used to set the cube's properties for rendering and place it in the window
    //vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    //actor->SetMapper(mapper);
    //actor->GetProperty()->EdgeVisibilityOn();

    //vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
    //actor->GetProperty()->SetColor( colors->GetColor3d("Red").GetData() );

    // Create a renderer, and render window
    renderer = vtkSmartPointer<vtkRenderer>::New();
    //vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();		// ###### We've already created the renderWindow this time ######
    ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer );									// ###### ask the QtVTKOpenGLWidget for its renderWindow ######

    // Link a renderWindowInteractor to the renderer (this allows you to capture mouse movements etc)  ###### Not needed with Qt ######
    //vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    //renderWindowInteractor->SetRenderWindow( ui->vtkWidget->GetRenderWindow() );

    // Add the actor to the scene
    //renderer->AddActor(actor);
    //renderer->SetBackground(colors->GetColor3d("Silver").GetData() );




    // Setup the renderers's camera
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();

    // Render and interact
    renderWindow->Render();					// ###### Not needed with Qt ######
    //renderWindowInteractor->Start();			// ###### Not needed with Qt ######
    //--------------------------------------------- /Code From Example 1 -------------------------------------------------------------------------*/



    //Code for opening a file using action trigger
    connect( ui->actionFileOpen, &QAction::triggered, this, &MainWindow::openFile);

    //Code for pressing a
    //connect( ui->changeColour, &QPushButton::released, this, &MainWindow::handleColourChange );
    connect( ui->loadCube, &QPushButton::released, this, &MainWindow::handleLoadCube );
    connect( ui->loadCylinder, &QPushButton::released, this, &MainWindow::handleLoadCylinder );
    connect( ui->changeColour, &QPushButton::released, this, &MainWindow::handleChangeColour );

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    //Clears the renderer window
    renderer->RemoveAllViewProps();

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
    actor->SetMapper (mapper);
    actor->GetProperty()->SetDiffuse(0.8);
    actor->GetProperty()->SetDiffuseColor(
        colors->GetColor3d ("LightSteelBlue").GetData());
    actor->GetProperty()->SetSpecular(0.3);
    actor->GetProperty()->SetSpecularPower(60.0);



    //Creates a new Actor
    renderer->AddActor(actor);
    renderer->SetBackground(colors->GetColor3d("Dark0liveGreen").GetData());

    // Setup the renderers's camera
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30) ;
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();


    renderWindow->Render();


}


void MainWindow::handleLoadCube()
{


    //--------------------------------------------- Code From Example 1 --------------------------------------------------------------------------
    // Create a cube using a vtkCubeSource
    vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();

    // Create a mapper that will hold the cube's geometry in a format suitable for rendering
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputConnection( cubeSource->GetOutputPort() );

    // Create an actor that is used to set the cube's properties for rendering and place it in the window
    cube_actor = vtkSmartPointer<vtkActor>::New();
    cube_actor->SetMapper(mapper);
    cube_actor->GetProperty()->EdgeVisibilityOn();

    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
    cube_actor->GetProperty()->SetColor( colors->GetColor3d("Red").GetData() );

    // Create a renderer, and render window
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    //vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();		// ###### We've already created the renderWindow this time ######
    ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer );									// ###### ask the QtVTKOpenGLWidget for its renderWindow ######

    // Link a renderWindowInteractor to the renderer (this allows you to capture mouse movements etc)  ###### Not needed with Qt ######
    //vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    //renderWindowInteractor->SetRenderWindow( ui->vtkWidget->GetRenderWindow() );

    // Add the actor to the scene
    renderer->AddActor(cube_actor);
    renderer->SetBackground(colors->GetColor3d("Silver").GetData() );



    // Setup the renderers's camera
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();


    // Render and interact
    renderWindow->Render();					// ###### Not needed with Qt ######


    //renderWindowInteractor->Start();			// ###### Not needed with Qt ######
    //--------------------------------------------- /Code From Example 1 -------------------------------------------------------------------------*/

}

void MainWindow::handleLoadCylinder()
{

    vtkNew<vtkNamedColors> colors;

     // Create a sphere
     vtkNew<vtkCylinderSource> cylinderSource;
     cylinderSource->SetCenter(0.0, 0.0, 0.0);
     cylinderSource->SetRadius(5.0);
     cylinderSource->SetHeight(7.0);
     cylinderSource->SetResolution(100);

     // Create a mapper and actor
     vtkNew<vtkPolyDataMapper> mapper;
     mapper->SetInputConnection(cylinderSource->GetOutputPort());
     vtkNew<vtkActor> cylinder_actor;
     cylinder_actor->GetProperty()->SetColor(colors->GetColor3d("Cornsilk").GetData());
     cylinder_actor->SetMapper(mapper);

     // Create a renderer, render window, and interactor
     //vtkNew<vtkRenderer> renderer;
     //vtkNew<vtkRenderWindow> renderWindow;
     //renderWindow->SetWindowName("Cylinder");
     //renderWindow->AddRenderer(renderer);
     //vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
     //renderWindowInteractor->SetRenderWindow(renderWindow);

     // Add the actor to the scene
     renderer->AddActor(cylinder_actor);
     renderer->SetBackground(colors->GetColor3d("DarkGreen").GetData());




     // Setup the renderers's camera
     renderer->ResetCamera();
     renderer->GetActiveCamera()->Azimuth(30);
     renderer->GetActiveCamera()->Elevation(30);
     renderer->ResetCameraClippingRange();



     // Render and interact
     renderWindow->Render();
     //renderWindowInteractor->Start();


}

void MainWindow::handleChangeColour()
{
    QColor ColourDialog = QColorDialog::getColor();

    float red, green, blue;

    red = ColourDialog.redF();
    green = ColourDialog.greenF();
    blue = ColourDialog.blueF();

    cube_actor->GetProperty()->SetColor(red, green, blue);
    cylinder_actor->GetProperty()->SetColor(red, green, blue);

}


