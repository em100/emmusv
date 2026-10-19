import rclpy
from rclpy.node import Node
import numpy as np
from sensor_msgs.msg import PointCloud2
from nav_msgs.msg import OccupancyGrid
import sensor_msgs_py.point_cloud2 as pc2

class LocalMapper(Node):
    def __init__(self):
        super().__init__('local_mapper_py')

        self.grid_size = 20.0
        self.resolution = 0.1
        self.dim = int(self.grid_size / self.resolution)

        self.grid = np.zeros((self.dim, self.dim), dtype=np.int8)

        self.sub = self.create_subscription(
            PointCloud2, '/pointcloud', self.pc_callback, 10)

        self.pub = self.create_publisher(
            OccupancyGrid, '/local_map', 10)

    def pc_callback(self, msg):
        self.grid.fill(0)

        for p in pc2.read_points(msg, field_names=("x", "y"), skip_nans=True):
            x, y = p
            gx = int((x + self.grid_size/2) / self.resolution)
            gy = int((y + self.grid_size/2) / self.resolution)
            if 0 <= gx < self.dim and 0 <= gy < self.dim:
                self.grid[gx, gy] = 100

        self.publish_grid()

    def publish_grid(self):
        msg = OccupancyGrid()
        msg.header.frame_id = "map"
        msg.info.resolution = self.resolution
        msg.info.width = self.dim
        msg.info.height = self.dim
        msg.data = self.grid.flatten().tolist()
        self.pub.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    node = LocalMapper()
    rclpy.spin(node)
    rclpy.shutdown()
