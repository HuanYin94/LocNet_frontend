#include <iostream>
#include <string>

#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/features/normal_3d.h>
#include <pcl/common/projection_matrix.h>
#include <pcl/features/vfh.h>

typedef pcl::PointXYZRGB PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

using namespace std;
using namespace ros;
using namespace pcl;
using namespace pcl::io;

int main() {

    ofstream outfile("/home/yh/YQ21/0912/00/vfh.txt");

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

        // Setup the feature computation
        typedef pcl::VFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::VFHSignature308> VFHEstimationType;
        VFHEstimationType vfhEstimation;

        // Provide the original point cloud (without normals)
        vfhEstimation.setInputCloud (cloudPointer);
        vfhEstimation.setInputNormals(cloud_normals);
        vfhEstimation.setSearchMethod (tree);

        //vfhEstimation.setRadiusSearch (0.2); // With this, error: "Both radius (.2) and K (1) defined! Set one of them to zero first and then re-run compute()"
        vfhEstimation.setSearchSurface(cloudPointer);
        vfhEstimation.setRadiusSearch (80);
        vfhEstimation.setIndices(0, 0, 1, 1);

        // Actually compute the VFH features
        pcl::PointCloud<pcl::VFHSignature308>::Ptr vfhFeatures(new pcl::PointCloud<pcl::VFHSignature308>);
        vfhEstimation.compute (*vfhFeatures);

        std::cout << "output points.size (): " << vfhFeatures->points.size () << std::endl; // This outputs 1 - should be 397!

        // Display and retrieve the shape context descriptor vector for the 0th point.
        pcl::VFHSignature308 descriptor = vfhFeatures->points[0];
        VFHEstimationType::PointCloudOut::PointType descriptor2 = vfhFeatures->points[0];
//        std::cout << descriptor << std::endl;
        outfile << descriptor << endl;

    }

    return 0;
}
