#include "RotationsRender.h"
#include "core/SkPath.h"
#include <iostream>
void RotationsRender::draw(SkCanvas* canvas, int elapsed, int w, int h)
{
    canvas->clear(SK_ColorWHITE);

//    SkMatrix mat1;
////    mat1.setTranslate(100,100);
//    SkRect rect1 = mat1.mapRect(rect);
//    SkMatrix t;
//    t.preRotate(90,mat1.getTranslateX()+200/2,mat1.getTranslateY()+100/2).mapRect(rect);
//    SkRect rect2 = t.mapRect(rect1);
////    canvas->translate(100, 0);
////    canvas->rotate(60);

//    paint.setAntiAlias(true);
//    paint.setColor(0xff4285F4);
////        canvas->drawRect(rect, paint);//200 100

////        canvas->rotate(SkIntToScalar(30));
////        paint.setColor(0xffDB4437);
//    canvas->drawRect(rect2, paint);
//    canvas->flush();
//    return;



    SkMatrix mat,stdMat;
    mat.setTranslate(100,100);
    SkPoint curPt =SkPoint::Make(mat.getTranslateX(),mat.getTranslateY());

    SkPath cornerSkPath,corner4;
    float u = 50,v=50;
    cornerSkPath.moveTo(0,0);
    cornerSkPath.lineTo(u,0);
    cornerSkPath.lineTo(u,u/2);
    cornerSkPath.lineTo(u/2,u/2);
    cornerSkPath.lineTo(u/2,u);
    cornerSkPath.lineTo(0,u);
    cornerSkPath.lineTo(0,0);
    cornerSkPath.close();

    SkPath   rectSkPath;
    rectSkPath.moveTo(0,0);
    rectSkPath.lineTo(v,0);
    rectSkPath.lineTo(v,v);//v/2
    rectSkPath.lineTo(0,v);//v/2
    rectSkPath.lineTo(0,0);
    rectSkPath.close();

    paint.setAntiAlias(true);
    paint.setColor(0xff4285F4);     //argb

    //同语义 Matrix的preTranslate是先平移再应用矩阵
    int W=200,H=200;
    SkRect outline =SkRect::MakeWH(W,H);                  //看一下正常的4边角怎么画的
    std::vector<float> D={
        0,0,(W-v)/2,0,(W-u)-(W-v)/2,0,
        u-W,(H-v)/2,
        0,(H-u)/2,(W-v)/2,0,(W-u)-(W-v),0,
        0,-(H-u-(H-v)/2)};//逐行 为了方便旋转
    std::vector<float> Dc{0,0,W-u,0,
                u-W,H-u,W-u,0};
    cornerSkPath.transform(mat);//增量过程
    rectSkPath.transform(mat);
    std::cout<<"-------------------"<<std::endl;
//    for(int i=0;i<8;i++){
//        int dx=D[i*2],dy=D[i*2+1];
//        std::cout<<"i="<<i<<" "<<curPt.x()<<" "<<curPt.y()<<std::endl;
//        if(i&1){
////            rectSkPath.transform(SkMatrix().preRotate(45*(i-1),curPt.x()+v/2,curPt.y()+v/2));
//            curPt.offset(dx,dy);
////            rectSkPath.offset(dx,dy);
////            corner4.addPath(rectSkPath);
//        }else{
//            cornerSkPath.transform(SkMatrix().preRotate(45*i,curPt.x()+u/2,curPt.y()+u/2));
//            curPt.offset(dx,dy);
//            cornerSkPath.offset(dx,dy);
//            corner4.addPath(cornerSkPath);
//       }
//    }
     for(int i=0;i<4;i++){
         int dx=Dc[i*2],dy=Dc[i*2+1];
         std::cout<<"i="<<i<<" "<<curPt.x()<<" "<<curPt.y()<<std::endl;
         cornerSkPath.transform(SkMatrix().preRotate(90*i,curPt.x()+u/2,curPt.y()+u/2));
         curPt.offset(dx,dy);
         cornerSkPath.offset(dx,dy);
         corner4.addPath(cornerSkPath);
     }
    std::cout<<"-------------------"<<std::endl;
            canvas->drawPath(corner4, paint);

        //    canvas->rotate(SkIntToScalar(20));
        //    paint.setColor(0xffDB4437);
        //    canvas->drawRect(rect, paint);

            canvas->flush();
        }

        void RotationsRender::init(int w, int h)
        {
            paint.setAntiAlias(true);
            rect = SkRect::MakeXYWH(0, 0, 200, 100);
        }

        void RotationsRender::resize(int w, int h)
        {
        }
