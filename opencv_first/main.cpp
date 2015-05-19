#include <list>
#include <opencv\cv.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/video/video.hpp>
#include <iostream>
#include <Windows.h>

using namespace cv;
using namespace std;

#define MAX_COUNT 500
int i,k; //�ѹ��� �ʱ�ȭ ? 
int main()
{
    //��������Ͽ� �� �����´�
	VideoCapture vc("C:\\Users\\youjin\\hyj\\video\\test1.avi");
	//VideoCapture capture;
    //capture.open(0);
      
    //capture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    //capture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
	if(!vc.isOpened())
    {
        cerr << "could not opened"<< endl;
        return 0;
    }
	
    namedWindow("original", 1); //�������� â
    namedWindow("edited1", 2);  //����ȭ ���� â 

    vector< vector<Point> > contours;
    BackgroundSubtractorMOG2 bg; //background ���� - ����� ������κ��� �и�  

    // optical flow : Ư���� �ȼ��� �̵��ϴ°ɷ� ��� �� (rgb -> gray �κ�ȯ�ؼ� )
    // 
    Mat gframe, pgframe; //grayframe , pregrayframe
    vector<Point2f> points1, points2; //vector.size() ��! 
    vector<uchar> status;
    vector<float> err;
    bool init = true;
    TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20,0.03);
    Size subPixWinSize(10,10), winSize(31,31);

	Mat frame, tframe;
    Mat nframe(240, 320, CV_16UC3);
	Mat img; // ī���� 
	//Mat counter=imread("C:\\Users\\youjin\\hyj\\img\\counter.jpg"); //ī���� �����̹���
    Mat back, fore;
    bool fvalid = true;
    list<Mat> q;
	int *count; // count ������ ��ü�迭 ����  --> points1�� vector<Point2f>�� ���ǵǾ������ϱ� 
	
    while(true)
    {
		//int i,k=0;
        fvalid = true;
        try
        {
			vc >> frame; //������ �����ӿ� �ֱ� 
			//���� ī���� �̹��� ��ġ�� 
			//	Mat imageROI = frame(Rect(300,80,counter.rows,counter.cols));
			//addWeighted(imageROI,1.0,counter,0.3,0,imageROI);

            bg.operator() (frame, fore,0);
  
            erode(fore, fore, Mat()); //ħ��->������ ����
			erode(fore, fore, Mat());
            //dilate(fore, fore, Mat());  //��â->������ ���� 

            findContours(fore, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
            drawContours(frame, contours, -1, Scalar(255,255,255),CV_FILLED);
			//thinning(fore,fore);
			// color transformation for optical flow
            cvtColor(frame, gframe, CV_BGR2GRAY);

            // gray scale to binary image 
            threshold(gframe, tframe, 250,255,0);

            
            // Harris corner detection 
			// harris corner : corner detect -> goodfeaturestrack���� �����س����Ŵ�
			//�ڳʰ� �� �ε巯��
			// ��Ƽ�� �÷ο��Ҷ� ���簪�̶� preview���� �־��� - > ���ϴϱ� initialize
            if(init){
				goodFeaturesToTrack(gframe, points1, 500, 0.01, 5, Mat(), 3, 0, 0.04); //point1�� ũ�Ⱑ ����!!!!!
				//point1�� ũ�Ⱑ ������ ������ count�� �����͹迭�� �Ҵ��϶� 
				count = new int[points1.size()];
				init=false;
				//count = new int[points1.size()];
			}else if(!points2.empty()){
                //optical flow function.
				//points2 -> pgframe�� ��� points1 -> gframe�� ��´� 
                calcOpticalFlowPyrLK(pgframe, gframe, points2, points1, status, err, winSize, 3, termcrit, 0, 0.001);
	
				//at �޼ҵ� : �� ���ҿ� �����ϱ� ���� at(int x, int y)�޼ҵ� �̿� 
				// �����Ͻ� �޼ҵ尡 ��ȯ�ϴ� Ÿ���� �˾ƾ���  --> ��� �� Ÿ�԰� ��ġ�ϴ��� �ƴ��� Ȯ�� 
             for(i= k = 0; i < points2.size(); i++) {
                 // if point is inside of object
                 if( (int)tframe.at<uchar>(points1[i].x, points1[i].y) == 255) //gray���� 255�� �Ͼ�� 
                 {
					if ((points1[i].x - points2[i].x) > 0) //�� -> �� (�̵��ߴ�?)
					{
                     line(frame, points1[i], points2[i], Scalar(0, 0, 255), 1, 1, 0);
					 circle(frame, points1[i], 2, Scalar(255, 0, 0), 1, 1, 0);
                     line(gframe, points1[i], points2[i], Scalar(0, 0, 255), 1, 1, 0);
                     circle(gframe, points1[i], 1, Scalar(255, 0, 0), 1, 1, 0);
                 }else{
                     line(frame, points1[i], points2[i], Scalar(0, 255, 0), 1, 1, 0);
                     circle(frame, points1[i], 2, Scalar(255, 0, 0), 1, 1, 0);
                     line(gframe, points1[i], points2[i], Scalar(0, 255, 0), 1, 1, 0);
                     circle(gframe, points1[i], 1, Scalar(255, 0, 0), 1, 1, 0);
                 }
                  points1[k++] = points1[i]; //
                 }
             }
              goodFeaturesToTrack(gframe, points1, MAX_COUNT, 0.01, 10, Mat(), 3, 0, 0.04);
            }
			
			// ���⼭���� point1 edit �ϸ� �ȴ� 
			for(int j=0;j<points1.size();j++){
			//����ٰ� if �� ����
				//count = new int[points1.size()];
				if((points1[j].x >=0 || points1[j].x <=500)||(points1[j].y >=0 || points1[j].y <=200) ){
					count[j]++;
					if(count[j]>0) //while���� �ѹ����ư����� �������� �� ������ 150 �����ӵ��� ī��Ʈ�� ���̸� �˶���� 
						cout << "beeeeeep" ;
						Beep(510,400); //1000 - 1��   --> 0.4��   "��"
				}else{
					//count[j]=0;
					//delete [] count;//�簢�� ������ ���� ����������  -> 0 ���� �ʱ�ȭ
				}
			//delete [] count;
			}
            
			std::swap(points2, points1); //ã���Źٲٰ�
            points1.clear(); //�����Ȱ� ���ְ� 
            gframe.copyTo(pgframe); 
			//delete [] count;
        }
        catch(Exception& e)
        {
            cerr << "exception : " << e.err << endl;
        }

        if(fvalid)
        {
            try
			{
				imshow("original", gframe);
                imshow("edited1", tframe); //����ȭ�Ȱ� 
            }
            catch(Exception& e)
            {
                cerr << "exception : " << e.err << endl;   
            }
        }   
        if(waitKey(30) >= 0)
			break;
    }
	delete [] count;
}

