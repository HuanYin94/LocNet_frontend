#include <iostream>
#include <string>

#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/features/normal_3d.h>
#include <pcl/common/projection_matrix.h>
#include <pcl/features/esf.h>

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

        // Setup the feature computation
        pcl::ESFEstimation<pcl::PointXYZ, pcl::ESFSignature640> esfEstimation;

        // Provide the original point cloud (without normals)
        esfEstimation.setInputCloud (cloudPointer);
        esfEstimation.setSearchMethod (tree);

        //vfhEstimation.setRadiusSearch (0.2); // With this, error: "Both radius (.2) and K (1) defined! Set one of them to zero first and then re-run compute()"
        esfEstimation.setSearchSurface(cloudPointer);
        esfEstimation.setRadiusSearch (80);
        esfEstimation.setIndices(0, 0, 1, 1);
        esfEstimation.setKSearch(0);

        // Actually compute the VFH features
        pcl::PointCloud<pcl::ESFSignature640>::Ptr esfFeatures(new pcl::PointCloud<pcl::ESFSignature640>);
        esfEstimation.compute (*esfFeatures);

//        std::cout << "output points.size (): " << vfhFeatures->points.size () << std::endl; // This outputs 1 - should be 397!

        // Display and retrieve the shape context descriptor vector for the 0th point.
        pcl::ESFSignature640 descriptor = esfFeatures->points[0];
//        std::cout << descriptor << std::endl;

        for(int i=0; i < 640; i++)
           outfile<<descriptor.histogram[i]<<" ";

        outfile<<endl;

    }

    stop = time(NULL);
    cout<<"total time:  "<<stop-start<<" seconds for "<<num<<" clouds."<<endl;

    return 0;
}
