# Front-end of LocNet

<img src="https://github.com/ZJUYH/LocNet_frontend/blob/main/image/range.png" width= 1000>

This page contains the front-end of LocNet network, implemented by Matlab.

For example, you can use the files in `kitti_dataset/range` to achieve the representations, based on the absolute range information. Specifically, the `binsToImageCells.m` is the main file to obtain the image-like cells.

We also present the comparative methods, please refer to the `Comparisons`.

If you use our implementation in your work, please cite the following paper:

	@article{yin20193d,
	  title={3D LiDAR-Based Global Localization Using Siamese Neural Network},
	  author={Yin, Huan and Wang, Yue and Ding, Xiaqing and Tang, Li and Huang, Shoudong and Xiong, Rong},
	  journal={IEEE Transactions on Intelligent Transportation Systems},
	  year={2019},
	  publisher={IEEE}
	}

or other related conferences: 

	title={LocNet: Global localization in 3D point clouds for mobile vehicles}
	title={Efficient 3D LIDAR based loop closing using deep neural network}

As for the caffe model in these papers, please refer to [LocNet_caffe](https://github.com/ZJUYH/LocNet_caffe).

If you have any questions, please contact: [Huan Yin](https://yinhuan.site/) `zjuyinhuan@gmail.com`.
