#pragma once

#include <vtkImageReader2Factory.h>
#include <vtkTexture.h>
#include <vtkSkybox.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkImageReader2.h>

class Stars {
public:
    Stars() {
        // Absolute Loaction
        // const char* => C-style string
        const char* imagePath = "D:\\FAU\\FAU course\\SS25\\SV\\exercise 1\\scivis-ss25\\images\\panorama_image.png";

        // Create suitable Reader type throught file extension, such as .png
        // CreateImageReader2() return vtkImageReader2* pointer
        // Take() transfer to smartpointer
        auto reader = vtkSmartPointer<vtkImageReader2>::Take(
            vtkImageReader2Factory::CreateImageReader2(imagePath));
        
        //if (reader.GetPointer() != nullptr)
        if (reader) {
            // Set image path
            reader->SetFileName(imagePath);
            // Update data (read data)
            reader->Update();

            // Initialize immediately
            // Instance of vtkSkybox
            texture = vtkSmartPointer<vtkTexture>::New();
            texture->SetInputConnection(reader->GetOutputPort());

            // Instance of vtkSkybox
            skybox = vtkSmartPointer<vtkSkybox>::New();
            skybox->SetTexture(texture);
            skybox->SetProjectionToSphere();
        }
    }

    void InitRenderer(vtkSmartPointer<vtkRenderer> renderer)
    {
        renderer->AddActor(skybox);
    }

private:
    // Private for invariants
    // SmartPointer use for long-term, share with multi-render, and as class member
    // Make sure the lifetime can match the render
    // SmartPointer use for most object inherent from vtkObject or vtkObjectBase
    // Declared but not initialized => null smart pointer
    // Use vtkSmartPointer default constructor
    vtkSmartPointer<vtkTexture> texture;
    vtkSmartPointer<vtkSkybox> skybox;
};
