#pragma once

#include "crtbp.hpp"

#include <vtkTexturedSphereSource.h>  // §ï¥ÎTexturedSphereSource
#include <vtkJPEGReader.h>           // JPEG reader
#include <vtkTexture.h>              // Add texture
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>

/// <summary>
/// Class that represents the Earth.
/// </summary>
class Earth
{
public:
    /// <summary>
    /// Constructor.
    /// </summary>
    Earth()
    {
        // Process: vtkPolyData -> vtkPolyDataMapper -> vtkActor -> vtkRender

        // Create a sphere with texture coordinates
        // vtkNew & vtkSmartpointer: All for automatically memoory control
        // vtkNew for local, vtkSmartpointer for global
        // vtkNew without the counter
        const double sphere_radius = 0.05;
        // template
        vtkNew<vtkTexturedSphereSource> sphereSource;  // Change to use TexturedSphereSource
        sphereSource->SetRadius(sphere_radius);
        sphereSource->SetPhiResolution(100);
        sphereSource->SetThetaResolution(100);

        // Mapping from Geometric datas to Primitives
        // GetOutputPort(): the part to get output data
        // SetInputConnection make the connection between GetOutputPort() & maper
        // mapper: use to get output data
        vtkNew<vtkPolyDataMapper> mapper;
        mapper->SetInputConnection(sphereSource->GetOutputPort());

        // Read earth texture
        const char* imagePath = "D:\\FAU\\FAU course\\SS25\\SV\\exercise 1\\scivis-ss25\\images\\earth.jpg";
        vtkNew<vtkJPEGReader> reader;
        reader->SetFileName(imagePath);

        // Create earth texture
        vtkNew<vtkTexture> texture;
        texture->SetInputConnection(reader->GetOutputPort());
        texture->InterpolateOn();


        mActor = vtkSmartPointer<vtkActor>::New();
        mActor->SetMapper(mapper);
        mActor->SetTexture(texture);  // Texture
        mActor->SetPosition(CRTBP::Earth().x(), CRTBP::Earth().y(), 0);
    }

    /// <summary>
    /// Updates the properties of the Earth.
    /// </summary>
    /// <param name="dt">Time passed since the last Update in milliseconds.</param>
    /// <param name="t">Total time passed since start of the application in milliseconds.</param>
    void Update(double dt, double t)
    {
        // rotate actor
        double angle_dt = dt * 0.1;                          // not a realistic rotation speed!
        mActor->RotateWXYZ(angle_dt, 0, 0.398749, 0.91706);   // 23.5?titled rotation axis
    }

    /// <summary>
    /// Adds the actors to the renderer.
    /// </summary>
    /// <param name="renderer">Renderer to add the actors to.</param>
    void InitRenderer(vtkSmartPointer<vtkRenderer> renderer)
    {
        renderer->AddActor(mActor);
    }

private:
    Earth(const Earth&) = delete;            // Delete the copy-constructor.
    void operator=(const Earth&) = delete;   // Delete the assignment operator.

    vtkSmartPointer<vtkActor> mActor;        // Actor that represents the scene geometry.
};