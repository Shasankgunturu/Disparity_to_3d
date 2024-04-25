#include <opencv2/opencv.hpp>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

class Reconstruct {
    public:
        Reconstruct(cv::Mat disparity, double fx, double u0, double v0, double baseline) {
            h               = disparity.rows;
            w               = disparity.cols;
            U0              = u0;
            V0              = v0;
            baseline_       = baseline;
            disparity_norm  = cv::Mat::zeros(h, w, CV_64F);
            focal_length    = fx;
            cv::normalize(disparity, disparity_norm, 0, 255, cv::NORM_MINMAX, CV_8UC1);
        }
        void forward() {
            cv::Mat depth = cv::Mat::zeros(h, w, CV_64F);
            pcl::PointCloud<pcl::PointXYZ> cloud;
            for (int i=0; i<h; i++) {
                for (int j=0; j<w; j++) {
                    if (disparity_norm.at<uchar>(i,j)>0) {
                        pcl::PointXYZ point;
                        depth.at<double>(i,j)   = (baseline_*focal_length)/ disparity_norm.at<uchar>(i, j);
                        double x                = (j - U0) * depth.at<double>(i,j) / focal_length;
                        double y                = (i - V0) * depth.at<double>(i,j) / focal_length;
                        double z                = depth.at<double>(i,j);
                        point.x                 = z + 0.28;
                        point.y                 = -x + 0.0375;
                        point.z                 = -y + 0.28;
                        cloud.push_back(point);
                    }
                }
            }
            pcl::io::savePCDFileASCII("/home/shasankgunturu/Documents/flomob/results/point_cloud.pcd", cloud);
            cv::imshow("Depth", depth);
            cv::waitKey(0);
        }
    private:
    cv::Mat disparity_norm;
    double focal_length, U0, V0, baseline_;
    int h, w;
};

int main() {
    cv::Mat disparity = cv::imread("/home/shasankgunturu/Documents/flomob/assignment_files/Disparity.png", cv::IMREAD_GRAYSCALE);
    if (disparity.empty()) {
        std::cerr << "Error: Could not load disparity image." << std::endl;
        return -1;
    }
    double baseline = 0.075;
    double fx       = 398.7956237792969; //since fx = fy from the given matrix
    double u0       = 315.4751892089844;
    double v0       = 205.1688232421875;
    Reconstruct r(disparity, fx, u0, v0, baseline);
    r.forward();
    return 0;
}
