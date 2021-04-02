import pyvista as pv
import numpy as np

def make_triangle_labels(path_file="centers.xyz"):
    data = []
    with open(path_file, 'r') as reader:
        for line in reader:
            idxyz = line.split()
            id = idxyz[0]
            x = float(idxyz[1])
            y = float(idxyz[2])
            z = float(idxyz[3])
            data.append((id, x, y, z))
    return data

def make_points(path_file="path.xyz"):
    x = []
    y = []
    z = []
    with open(path_file, 'r') as reader:
        for line in reader:
            xyz = line.split()
            x.append(float(xyz[0]))
            y.append(float(xyz[1]))
            z.append(float(xyz[2]))
    return np.column_stack((x,y,z))
    '''
    theta = np.linspace(-4 * np.pi, 4 * np.pi, 100)
    z = np.linspace(-2, 2, 100)
    r = z**2 + 1
    x = r * np.sin(theta)
    y = r * np.cos(theta)
    return np.column_stack((x, y, z))
    '''

def lines_from_points(points):
    """Given an array of points, make a line set"""
    poly = pv.PolyData()
    poly.points = points
    cells = np.full((len(points)-1, 3), 2, dtype=np.int_)
    cells[:, 1] = np.arange(0, len(points)-1, dtype=np.int_)
    cells[:, 2] = np.arange(1, len(points), dtype=np.int_)
    poly.lines = cells
    return poly

if __name__ == "__main__":
    points = make_points()
    print(points)
    #points[0:5, :]

    line = lines_from_points(points)
    line["scalars"] = np.arange(line.n_points)
    tube = line.tube(radius=0.1)
    tube.plot(smooth_shading=True)

