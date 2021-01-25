#include <iostream>
#include <string>

#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/features/normal_3d.h>
#include <pcl/common/projection_matrix.h>
#include <pcl/features/feature.h>
#include <pcl/features/spin_image.h>

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
         pcl::SpinImageEstimation<pcl::PointXYZ, pcl::Normal, pcl::Histogram<153> > spin_image_descriptor(8, 0.5, 16);
         spin_image_descriptor.setInputCloud (cloudPointer);
         spin_image_descriptor.setInputNormals (cloud_normals);
         // Search the whole point cloud
         spin_image_descriptor.setSearchSurface(cloudPointer);
         // Search only one point
         spin_image_descriptor.setIndices(0, 0, 1, 1);
         // Use the same KdTree from the normal estimation
         spin_image_descriptor.setSearchMethod (tree);
         spin_image_descriptor.setRadiusSearch (80);

         // Actually compute the spin images
         pcl::PointCloud<pcl::Histogram<153> >::Ptr spin_images (new pcl::PointCloud<pcl::Histogram<153> >);
         spin_image_descriptor.compute (*spin_images);

         // Display and retrieve the spin image descriptor vector for the first point.
//        cout<<spin_images->points.size()<<endl;
         pcl::Histogram<153> first_descriptor = spin_images->points[0];
//         std::cout << first_descriptor << std::endl;

         for(int i=0; i < 153; i++)
            outfile<<first_descriptor.histogram[i]<<" ";

         outfile<<endl;

    }

    stop = time(NULL);
    cout<<"total time:  "<<stop-start<<" seconds for "<<num<<" clouds."<<endl;


    return 0;
}
