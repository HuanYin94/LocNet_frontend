#include <iostream>
#include <string>

#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/features/normal_3d.h>
#include <pcl/common/projection_matrix.h>
#include <pcl/features/feature.h>
#include <pcl/features/fpfh.h>

typedef pcl::PointXYZRGB PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

using namespace std;
using namespace ros;
using namespace pcl;
using namespace pcl::io;

int main() {


    for(int i=0; i<4541; i++)
    {
        cout<<i<<endl;
        stringstream ss;
        ss<<i;
        string str;
        ss>>str;
        string filename = "/media/yh/YH/DataSet/kitti_benchmark_velodyne/dataset/pcd/00/" + str +".ply";
        pcl::PointCloud<pcl::PointXYZ> cloud;
        if (loadPLYFile(filename, cloud) != 0) return false;

        // add center point
        pcl::PointXYZ point = { 0, 0, 0 };
        cloud.insert(cloud.begin(), point);
        cloud.push_back(point);

        // to const ptr
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloudPointer(new pcl::PointCloud<pcl::PointXYZ>);
        cloudPointer = cloud.makeShared();

        // estimate the normal
        pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
        ne.setInputCloud (cloudPointer);
        pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ> ());
        ne.setSearchMethod (tree);
        pcl::PointCloud<pcl::Normal>::Ptr cloud_normals (new pcl::PointCloud<pcl::Normal>);
        ne.setRadiusSearch(0.5);
        ne.compute(*cloud_normals);

        // Setup spin image computation
         pcl::FPFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::FPFHSignature33> fpfh_estimation;
         fpfh_estimation.setInputCloud (cloudPointer);
         fpfh_estimation.setInputNormals (cloud_normals);
         // Search the whole point cloud
         fpfh_estimation.setSearchSurface(cloudPointer);
         // Search only one point
         fpfh_estimation.setIndices(0, 0, 1, 1);
         // Use the same KdTree from the normal estimation
         fpfh_estimation.setSearchMethod (tree);
         fpfh_estimation.setRadiusSearch (80);

         // Actually compute the spin images
         pcl::PointCloud<pcl::FPFHSignature33>::Ptr pfh_features (new pcl::PointCloud<pcl::FPFHSignature33>);
         fpfh_estimation.compute (*pfh_features);

         // Display and retrieve the spin image descriptor vector for the first point.
//        cout<<pfh_features->points.size()<<endl;
         pcl::FPFHSignature33 descriptor = pfh_features->points[0];
         std::cout << descriptor << std::endl;

         /// too slow

    }

    return 0;
}
