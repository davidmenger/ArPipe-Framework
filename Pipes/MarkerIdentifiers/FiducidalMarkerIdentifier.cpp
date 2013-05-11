//
//  FiducidalMarkerIdentifier.cpp
//  AR
//
//  Created by Menger David on 11.05.13.
//  Copyright (c) 2013 storyous.com s.r.o. All rights reserved.
//

#include "FiducidalMarkerIdentifier.h"

using namespace cv;

namespace ArPipe {
    
    
    
    int FiducidalMarkerIdentifier::detectMarker(const cv::Mat &in,int &nRotations)
    {
        assert(in.rows==in.cols);
        Mat grey;
        if ( in.type()==CV_8UC1) grey=in;
        else cv::cvtColor(in,grey,CV_BGR2GRAY);
        //threshold image
        threshold(grey, grey,125, 255, THRESH_BINARY|THRESH_OTSU);
        
        //now, analyze the interior in order to get the id
        //try first with the big ones
        
        return analyzeMarkerImage(grey,nRotations);
    }
    
    
    /************************************
     *
     *
     *
     *
     ************************************/
    /**
     */
    Mat FiducidalMarkerIdentifier::createMarkerImage(int id,int size) throw (cv::Exception)
    {
        Mat marker(size,size, CV_8UC1);
        marker.setTo(Scalar(0));
        if (0<=id && id<1024) {
            //for each line, create
            int swidth=size/7;
            int ids[4]={0x10,0x17,0x09,0x0e};
            for (int y=0;y<5;y++) {
                int index=(id>>2*(4-y)) & 0x0003;
                int val=ids[index];
                for (int x=0;x<5;x++) {
                    Mat roi=marker(Rect((x+1)* swidth,(y+1)* swidth,swidth,swidth));
                    if ( ( val>>(4-x) ) & 0x0001 ) roi.setTo(Scalar(255));
                    else roi.setTo(Scalar(0));
                }
            }
        }
        else  throw cv::Exception(9004,"id invalid","createMarker",__FILE__,__LINE__);
        
        return marker;
    }
    
    cv::Mat FiducidalMarkerIdentifier::getMarkerMat(int id) throw (cv::Exception)
    {
        Mat marker(5,5, CV_8UC1);
        marker.setTo(Scalar(0));
        if (0<=id && id<1024) {
            //for each line, create
            int ids[4]={0x10,0x17,0x09,0x0e};
            for (int y=0;y<5;y++) {
                int index=(id>>2*(4-y)) & 0x0003;
                int val=ids[index];
                for (int x=0;x<5;x++) {
                    if ( ( val>>(4-x) ) & 0x0001 ) marker.at<uchar>(y,x)=1;
                    else marker.at<uchar>(y,x)=0;
                }
            }
        }
        else throw cv::Exception (9189,"Invalid marker id","aruco::fiducidal::createMarkerMat",__FILE__,__LINE__);
        return marker;
    }
    
    
    
    /************************************
     *
     *
     *
     *
     ************************************/
    Mat FiducidalMarkerIdentifier::rotate(Mat  in)
    {
        Mat out;
        in.copyTo(out);
        for (int i=0;i<in.rows;i++)
        {
            for (int j=0;j<in.cols;j++)
            {
                out.at<uchar>(i,j)=in.at<uchar>(in.cols-j-1,i);
            }
        }
        return out;
    }
    
    
    /************************************
     *
     *
     *
     *
     ************************************/
    int FiducidalMarkerIdentifier::hammDistMarker(Mat  bits)
    {
        int ids[4][5]=
        {
            {
                1,0,0,0,0
            }
            ,
            {
                1,0,1,1,1
            }
            ,
            {
                0,1,0,0,1
            }
            ,
            {
                0, 1, 1, 1, 0
            }
        };
        int dist=0;
        
        for (int y=0;y<5;y++)
        {
            int minSum=1e5;
            //hamming distance to each possible word
            for (int p=0;p<4;p++)
            {
                int sum=0;
                //now, count
                for (int x=0;x<5;x++)
                    sum+=  bits.at<uchar>(y,x) == ids[p][x]?0:1;
                if (minSum>sum) minSum=sum;
            }
            //do the and
            dist+=minSum;
        }
        
        return dist;
    }
    
    /************************************
     *
     *
     *
     *
     ************************************/
    int FiducidalMarkerIdentifier::analyzeMarkerImage(Mat &grey,int &nRotations)
    {
        
        //Markers  are divided in 7x7 regions, of which the inner 5x5 belongs to marker info
        //the external border shoould be entirely black
        
        int swidth=grey.rows/7;
        for (int y=0;y<7;y++)
        {
            int inc=6;
            if (y==0 || y==6) inc=1;//for first and last row, check the whole border
            for (int x=0;x<7;x+=inc)
            {
                int Xstart=(x)*(swidth);
                int Ystart=(y)*(swidth);
                Mat square=grey(Rect(Xstart,Ystart,swidth,swidth));
                int nZ=countNonZero(square);
                if (nZ> (swidth*swidth) /2) {
                    // 		cout<<"neb"<<endl;
                    return -1;//can not be a marker because the border element is not black!
                }
            }
        }
        
        //now,
        vector<int> markerInfo(5);
        Mat _bits=Mat::zeros(5,5,CV_8UC1);
        //get information(for each inner square, determine if it is  black or white)
        
        for (int y=0;y<5;y++)
        {
            
            for (int x=0;x<5;x++)
            {
                int Xstart=(x+1)*(swidth);
                int Ystart=(y+1)*(swidth);
                Mat square=grey(Rect(Xstart,Ystart,swidth,swidth));
                int nZ=countNonZero(square);
                if (nZ> (swidth*swidth) /2)  _bits.at<uchar>( y,x)=1;
            }
        }
        // 		printMat<uchar>( _bits,"or mat");
        
        //checkl all possible rotations
        Mat _bitsFlip;
        Mat Rotations[4];
        Rotations[0]=_bits;
        int dists[4];
        dists[0]=hammDistMarker( Rotations[0]) ;
        pair<int,int> minDist( dists[0],0);
        for (int i=1;i<4;i++)
        {
            //rotate
            Rotations[i]=rotate(Rotations[i-1]);
            //get the hamming distance to the nearest possible word
            dists[i]=hammDistMarker( Rotations[i]) ;
            if (dists[i]<minDist.first)
            {
                minDist.first=  dists[i];
                minDist.second=i;
            }
        }
        // 		        printMat<uchar>( Rotations [ minDist.second]);
        // 		 	cout<<"MinDist="<<minDist.first<<" "<<minDist.second<<endl;
        
        nRotations=minDist.second;
        if (minDist.first!=0)	 //FUTURE WORK: correct if any error
            return -1;
        else {//Get id of the marker
            int MatID=0;
            cv::Mat bits=Rotations [ minDist.second];
            for (int y=0;y<5;y++)
            {
                MatID<<=1;
                if ( bits.at<uchar>(y,1)) MatID|=1;
                MatID<<=1;
                if ( bits.at<uchar>(y,3)) MatID|=1;
            }
            return MatID;
        }
    }
    
    
    /************************************
     *
     *
     *
     *
     ************************************/
    bool FiducidalMarkerIdentifier::correctHammMarker(Mat &bits)
    {
        //detect this lines with errors
        bool errors[4];
        int ids[4][5]=
        {
            {
                0,0,0,0,0
            }
            ,
            {
                0,0,1,1,1
            }
            ,
            {
                1,1,0,0,1
            }
            ,
            {
                1, 1, 1, 1, 0
            }
        };
        
        for (int y=0;y<5;y++)
        {
            int minSum=1e5;
            //hamming distance to each possible word
            for (int p=0;p<4;p++)
            {
                int sum=0;
                //now, count
                for (int x=0;x<5;x++)
                    sum+=  bits.at<uchar>(y,x) == ids[p][x]?0:1;
                if (minSum>sum) minSum=sum;
            }
            if (minSum!=0) errors[y]=true;
            else errors[y]=false;
        }
        
        return true;
    }
    
    
    
}