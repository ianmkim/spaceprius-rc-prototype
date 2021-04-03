import numpy as np
import pyvista as pv
import spline
import obj

if __name__ == "__main__":
    obj.convertObjToVtk("mesh.obj")
    mesh = pv.read("mesh.vtk")

    points = spline.make_points()
    line = spline.lines_from_points(points)
    line['scalars'] = np.arange(line.n_points)


    print(points)
    plotter = pv.Plotter()

    plotter.add_mesh(mesh, show_edges=True, pickable=True)
    plotter.add_lines(points)
    cps = plotter.show()

