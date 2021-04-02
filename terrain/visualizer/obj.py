from __future__ import print_function
import sys
import vtk
import pyvista as pv

def convertObjToVtk(filename):
    reader = vtk.vtkOBJReader()
    reader.SetFileName(filename)
    reader.Update()
    obj = reader.GetOutput()

    writer = vtk.vtkPolyDataWriter()
    writer.SetFileName(filename.replace(".obj", ".vtk"))

    if vtk.VTK_MAJOR_VERSION <= 5:
        writer.SetInput(obj)
    else:
        writer.SetInputData(obj)
    writer.Write()

if __name__ == "__main__":
    convertObjToVtk("mesh.obj")

    mesh = pv.read("mesh.vtk")
    mesh.plot(smooth_shading=True)
