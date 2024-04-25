import numpy as np
import cv2
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import open3d as o3d

if __name__ == "__main__":
    point_cloud = o3d.io.read_point_cloud("/home/shasankgunturu/Documents/flomob/results/point_cloud.pcd")
    point_cloud_base_frame = np.asarray(point_cloud.points)
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(point_cloud_base_frame[:,0], point_cloud_base_frame[:,1], point_cloud_base_frame[:,2], c=point_cloud_base_frame[:,0], cmap='viridis', s=1)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    cb = plt.colorbar(plt.cm.ScalarMappable(cmap='viridis'), ax=ax)
    cb.set_label('Depth')
    plt.show()
