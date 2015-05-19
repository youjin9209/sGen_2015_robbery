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
int i,k; //한번만 초기화 ? 
int main()
{
    //경로지정하여 상 가져온다
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
	
    namedWindow("original", 1); //원본영샹 창
    namedWindow("edited1", 2);  //이진화 띄우는 창 

    vector< vector<Point> > contours;
    BackgroundSubtractorMOG2 bg; //background 제거 - 배경을 사람으로부터 분리  

    // optical flow : 특정한 픽셀이 이동하는걸로 잡는 거 (rgb -> gray 로변환해서 )
    // 
    Mat gframe, pgframe; //grayframe , pregrayframe
    vector<Point2f> points1, points2; //vector.size() 로! 
    vector<uchar> status;
    vector<float> err;
    bool init = true;
    TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20,0.03);
    Size subPixWinSize(10,10), winSize(31,31);

	Mat frame, tframe;
    Mat nframe(240, 320, CV_16UC3);
	Mat img; // 카운터 
	//Mat counter=imread("C:\\Users\\youjin\\hyj\\img\\counter.jpg"); //카운터 고정이미지
    Mat back, fore;
    bool fvalid = true;
    list<Mat> q;
	int *count; // count 포인터 객체배열 선언  --> points1이 vector<Point2f>로 정의되어있으니까 
	
    while(true)
    {
		//int i,k=0;
        fvalid = true;
        try
        {
			vc >> frame; //영상을 프레임에 넣기 
			//고정 카운터 이미지 합치기 
			//	Mat imageROI = frame(Rect(300,80,counter.rows,counter.cols));
			//addWeighted(imageROI,1.0,counter,0.3,0,imageROI);

            bg.operator() (frame, fore,0);
  
            erode(fore, fore, Mat()); //침식->노이즈 제거
			erode(fore, fore, Mat());
            //dilate(fore, fore, Mat());  //팽창->노이즈 제거 

            findContours(fore, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
            drawContours(frame, contours, -1, Scalar(255,255,255),CV_FILLED);
			//thinning(fore,fore);
			// color transformation for optical flow
            cvtColor(frame, gframe, CV_BGR2GRAY);

            // gray scale to binary image 
            threshold(gframe, tframe, 250,255,0);

            
            // Harris corner detection 
			// harris corner : corner detect -> goodfeaturestrack으로 구현해놓은거다
			//코너가 더 두드러짐
			// 옵티컬 플로우할때 현재값이랑 preview값을 넣어줘 - > 비교하니까 initialize
            if(init){
				goodFeaturesToTrack(gframe, points1, 500, 0.01, 5, Mat(), 3, 0, 0.04); //point1의 크기가 결정!!!!!
				//point1의 크기가 결정된 다음에 count의 포인터배열을 할당하라 
				count = new int[points1.size()];
				init=false;
				//count = new int[points1.size()];
			}else if(!points2.empty()){
                //optical flow function.
				//points2 -> pgframe이 담고 points1 -> gframe이 담는다 
                calcOpticalFlowPyrLK(pgframe, gframe, points2, points1, status, err, winSize, 3, termcrit, 0, 0.001);
	
				//at 메소드 : 각 원소에 접근하기 위해 at(int x, int y)메소드 이용 
				// 컴파일시 메소드가 반환하는 타입을 알아야지  --> 행렬 내 타입과 일치하는지 아닌지 확인 
             for(i= k = 0; i < points2.size(); i++) {
                 // if point is inside of object
                 if( (int)tframe.at<uchar>(points1[i].x, points1[i].y) == 255) //gray에는 255가 하얀색 
                 {
					if ((points1[i].x - points2[i].x) > 0) //후 -> 전 (이동했니?)
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
			
			// 여기서부터 point1 edit 하면 된다 
			for(int j=0;j<points1.size();j++){
			//여기다가 if 문 돌려
				//count = new int[points1.size()];
				if((points1[j].x >=0 || points1[j].x <=500)||(points1[j].y >=0 || points1[j].y <=200) ){
					count[j]++;
					if(count[j]>0) //while문에 한번돌아갈때가 한프레임 한 점마다 150 프레임동안 카운트가 쌓이면 알람울려 
						cout << "beeeeeep" ;
						Beep(510,400); //1000 - 1초   --> 0.4초   "도"
				}else{
					//count[j]=0;
					//delete [] count;//사각형 밖으로 나간 점이있으면  -> 0 으로 초기화
				}
			//delete [] count;
			}
            
			std::swap(points2, points1); //찾은거바꾸고
            points1.clear(); //오래된거 없애고 
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
                imshow("edited1", tframe); //이진화된거 
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

