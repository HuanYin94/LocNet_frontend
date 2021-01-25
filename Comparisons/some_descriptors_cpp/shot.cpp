#include <iostream>
#include <string>

#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/features/normal_3d.h>
#include <pcl/common/projection_matrix.h>
#include <pcl/features/feature.h>
#include <pcl/features/shot.h>

typedef pcl::PointXYZRGB PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

using namespace std;
using namespace ros;
using namespace pcl;
using namespace pcl::io;

int main(int argc,char *argv[]) {

    ofstream outfile(argv[1]);
    string s = argv[2];
    int num = atoi(s.c_str());

    time_t start,stop;
    start = time(NULL);

    for(int i=0; i<num; i++)
    {
        cout<<i<<endl;
        stringstream ss;
        ss<<i;
        string str;
        ss>>str;
        string filename = argv[3] + str +".ply";
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
        typedef pcl::SHOT352 ShotFeature;
         pcl::SHOTEstimation<pcl::PointXYZ, pcl::Normal, ShotFeature> shotEstimation;
         shotEstimation.setInputCloud (cloudPointer);
         shotEstimation.setInputNormals (cloud_normals);
         // Search the whole point cloud
         shotEstimation.setSearchSurface(cloudPointer);
         // Search only one point
         shotEstimation.setIndices(0, 0, 1, 1);
         // Use the same KdTree from the normal estimation
         shotEstimation.setSearchMethod (tree);
         shotEstimation.setRadiusSearch (80);

         // Actually compute the spin images
         pcl::PointCloud<ShotFeature>::Ptr shotFeatures(new pcl::PointCloud<ShotFeature>);
         shotEstimation.compute (*shotFeatures);

         // Display and retrieve the spin image descriptor vector for the first point.
//        cout<<pfh_features->points.size()<<endl;
         ShotFeature descriptor = shotFeatures->points[0];
//         std::cout << descriptor << std::endl;

         for(int i=0; i < 352; i++)
            outfile<<descriptor.descriptor[i]<<" ";

         outfile<<endl;


    }

    stop = time(NULL);
    cout<<"total time:  "<<stop-start<<" seconds for "<<num<<" clouds."<<endl;


    return 0;
}
