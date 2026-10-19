import rclpy
from rclpy.node import Node
import numpy as np
from sensor_msgs.msg import PointCloud2, Image
import sensor_msgs_py.point_cloud2 as pc2
from cv_bridge import CvBridge

class GlobalMapper(Node):
    def __init__(self):
        super().__init__('global_mapper_py')

        self.map_size = 200.0
        self.voxel_res = 0.2
        self.dim = int(self.map_size / self.voxel_res)

        self.voxels = np.zeros((self.dim, self.dim, self.dim), dtype=np.uint8)
        self.semantic = np.zeros_like(self.voxels)

        self.bridge = CvBridge()

        self.sub_pc = self.create_subscription(
            PointCloud2, '/pointcloud', self.pc_callback, 10)

        self.sub_sem = self.create_subscription(
            Image, '/semantic_mask', self.sem_callback, 10)

    def pc_callback(self, msg):
        for p in pc2.read_points(msg, field_names=("x", "y", "z"), skip_nans=True):
            x, y, z = p
            gx = int((x + self.map_size/2) / self.voxel_res)
            gy = int((y + self.map_size/2) / self.voxel_res)
            gz = int((z + self.map_size/2) / self.voxel_res)
            if 0 <= gx < self.dim and 0 <= gy < self.dim and 0 <= gz < self.dim:
                self.voxels[gx, gy, gz] = 1

    def sem_callback(self, msg):
        mask = self.bridge.imgmsg_to_cv2(msg, desired_encoding='mono8')
        # semantic integration logic here

def main(args=None):
    rclpy.init(args=args)
    node = GlobalMapper()
    rclpy.spin(node)
    rclpy.shutdown()
