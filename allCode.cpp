#define SDL_MAIN_HANDLED 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <cmath>
#include <SDL2/SDL.h>
#define pi 3.14159265358979323846
const double degToRadFactor=pi/180;double toRadians(double degrees){return degrees*degToRadFactor;}double toDegrees(double radians){return radians/degToRadFactor;}int max(int var1,int var2){if(var1>var2)return var1;return var2;}double max(double var1,double var2){if(var1>var2)return var1;
return var2;}int min(int var1,int var2){if(var1<var2)return var1;return var2;}double min(double var1,double var2){if(var1<var2)return var1;return var2;}double inRange(double num,double from,double to){if((num>=from)&&(num<=to))return((num-from)/(to-from));return -1;}double quickArctan(double x)
{double a=90;double b=0.3;return(a*((b*x)/sqrt(1+((b*x)*(b*x)))));}double getAngle(double x1,double y1,double x2=0,double y2=0){if(x1==x2){if(y1>=y2)return 0;return 180;}if(y1==y2){if(x1>=x2)return 90;return 270;}double m=abs((x1-x2)/(y1-y2));double angle=toDegrees(atan(m));if(y1<y2)
angle=(double)180-angle;if(x1<x2)angle=(double)360-angle;return angle;}class Vec2{public: double x; double y;Vec2(double inputX,double inputY){this->x=inputX; this->y=inputY;this->magnitudeValue=0;this->magnitudeUpdated=false;}Vec2(){this->x=0; this->y=0;this->magnitudeValue=0;
this->magnitudeUpdated=false;}Vec2*copy(){return new Vec2(this->x,this->y);}bool is(Vec2*other){return(this->x==other->x&&this->y==other->y);}Vec2*add(Vec2*other){this->x+=other->x; this->y+=other->y;this->magnitudeUpdated=false;return this;}Vec2*sub(Vec2*other){this->x-=other->x;this->y-=other->y;
this->magnitudeUpdated=false;return this;}Vec2*scale(double factor){this->x*=factor;this->y*=factor;if(this->magnitudeUpdated)this->magnitudeValue*=factor;return this;}Vec2*inverseScale(double factor){return this->scale(1/factor);}Vec2*normalise(double toMagnitude=1){double factor=toMagnitude/
this->magnitude();return this->scale(factor);}double get(int index){switch(index){case 0:return this->x;case 1:return this->y;default:return 0;}}double*toArray(){double*array=new double[2];array[0]=this->x;array[1]=this->y;return array;}double magnitude(){if(!this->magnitudeUpdated){
this->magnitudeValue=sqrt((this->x*this->x)+(this->y*this->y));this->magnitudeUpdated=true;}return this->magnitudeValue;}double distanceTo(Vec2*other){double dx=this->x-other->x;double dy=this->y-other->y;return sqrt((dx*dx)+(dy*dy));}Vec2*midpoint(Vec2*other){return new Vec2((this->x+other->x)/2,
(this->y+other->y)/2);}double dotProduct(Vec2*other){return(this->x*other->x)+(this->y*other->y);}void rotate(double radians,Vec2*around=NULL){if(radians==0)return;double aroundX=0;double aroundY=0;double relativeX=this->x;double relativeY=this->y;if(around!=NULL){aroundX=around->x;aroundY=around->y
;relativeX-=aroundX;relativeY-=aroundY;}double sinValue=sin(radians);double cosValue=cos(radians);this->x=(cosValue*relativeX)-(sinValue*relativeY)+aroundX;this->y=(cosValue*relativeY)+(sinValue*relativeX)+aroundY;return;}bool operator==(Vec2*other){return this->is(other);}bool operator!=(Vec2*
other){return !this->is(other);}Vec2*operator+=(Vec2*other){return this->add(other);}Vec2*operator-=(Vec2*other){return this->sub(other);}private:double magnitudeValue;bool magnitudeUpdated;};class Vec3{public:double x;double y;double z;Vec3(double inputX,double inputY,double inputZ){this->x=inputX;
this->y=inputY;this->z=inputZ;this->magnitudeValue=0;this->magnitudeUpdated=false;}Vec3(){this->x=0;this->y=0;this->z=0;this->magnitudeValue=0;this->magnitudeUpdated=false;}Vec3*copy(){return new Vec3(this->x,this->y,this->z);}bool is(Vec3*other){return(this->x==other->x &&this->y==other->y &&
this->z==other->z);}Vec3*add(Vec3*other){this->x+=other->x;this->y+=other->y;this->z+=other->z;this->magnitudeUpdated=false;return this;}Vec3*sub(Vec3*other){this->x-=other->x;this->y-=other->y;this->z-=other->z;this->magnitudeUpdated=false;return this;}Vec3*scale(double factor){this->x*=factor;
this->y*=factor;this->z*=factor;if(this->magnitudeUpdated)this->magnitudeValue*=factor;return this;}Vec3*inverseScale(double factor){return this->scale(1/factor);}Vec3*normalise(double toMagnitude=1){double factor=toMagnitude/this->magnitude();return this->scale(factor);}double get(int index)
{switch(index){case 0:return this->x;case 1:return this->y;case 2:return this->z;default:return 0;}}double*toArray(){double*array=new double[3];array[0]=this->x;array[1]=this->y;array[2]=this->z;return array;}double magnitude(){if(!this->magnitudeUpdated){this->magnitudeValue=sqrt((this->x*
this->x)+(this->y*this->y)+(this->z*this->z));this->magnitudeUpdated=true;}return this->magnitudeValue;}double distanceTo(Vec3*other){double dx=this->x-other->x;double dy=this->y-other->y;double dz=this->z-other->z;return sqrt((dx*dx)+(dy*dy)+(dz*dz));}Vec3*midpoint(Vec3*other){return new Vec3
((this->x+other->x)/2,(this->y+other->y)/2,(this->z+other->z)/2);}double dotProduct(Vec3*other){return(this->x*other->x)+(this->y*other->y)+(this->z*other->z);}Vec3*crossProduct(Vec3*other){double x=(this->y*other->z)-(this->z*other->y);double y=(this->z*other->x)-(this->x*other->z);
double z=(this->x*other->y)-(this->y*other->x);return new Vec3(x,y,z);}double getAngle(Vec3*other){double dotProduct=this->dotProduct(other);
double magnitudeFactor=this->magnitude()*other->magnitude();double ratio=dotProduct/magnitudeFactor;if(ratio<-1)return pi;if(ratio>1) return 0;
return acos(ratio);}void rotate(double yaw,double pitch,double roll,Vec3*around=NULL){if(yaw==0&&pitch==0&&roll==0)return;
double aroundX=0;double aroundY=0;double aroundZ=0;double relativeX=this->x;double relativeY=this->y;double relativeZ=this->z;
if(around!=NULL){aroundX=around->x;aroundY=around->y;aroundZ=around->z;relativeX-=aroundX;relativeY-=aroundY;relativeZ-=aroundZ;}if(yaw!=0){
double sinValue=sin(yaw);double cosValue=cos(yaw);this->x=(cosValue*relativeX)-(sinValue*relativeZ)+aroundX;
this->z=(cosValue*relativeZ)+(sinValue*relativeX)+aroundZ;}if(pitch!=0){double sinValue=sin(pitch);double cosValue=cos(pitch);
this->y=(cosValue*relativeY)-(sinValue*relativeZ)+aroundY;this->z=(cosValue*relativeZ)+(sinValue*relativeY)+aroundZ;}
if(roll!=0){double sinValue=sin(roll);double cosValue=cos(roll);this->y=(cosValue*relativeY)-(sinValue*relativeX)+aroundY;
this->x=(cosValue*relativeX)+(sinValue*relativeY)+aroundX;}return;}bool operator==(Vec3*other){return this->is(other);}bool operator!=(Vec3*other){
return !this->is(other);}private:double magnitudeValue;bool magnitudeUpdated;};class Tri2{public:Vec2*v1;Vec2*v2;Vec2*v3;Tri2(bool nullPointers=false){
if(nullPointers){this->v1=NULL;this->v2=NULL;this->v3=NULL;}else{this->v1=new Vec2(0,0);this->v2=new Vec2(0,0);this->v3=new Vec2(0,0);}}~Tri2(){
delete this->v1;delete this->v2;delete this->v3;}void setv1(double x,double y,double z){this->v1->x=x;this->v1->y=y;}void setv1(Vec2*vec){delete this->v1;
this->v1=vec->copy();}void setv2(double x,double y,double z){this->v2->x=x;this->v2->y=y;}void setv2(Vec2*vec){delete this->v2;this->v2=vec->copy();}
void setv3(double x,double y,double z){this->v3->x=x;this->v3->y=y;}void setv3(Vec2*vec){delete this->v3;this->v3=vec->copy();}};class Tri3{public:
Vec3*v1;Vec3*v2;Vec3*v3;Vec3*normal;Tri3(bool nullPointers=false){if(nullPointers){this->v1=NULL;this->v2=NULL;this->v2=NULL;this->normal=NULL;
return;}else{this->v1=new Vec3(0,0,0);this->v2=new Vec3(0,0,0);this->v3=new Vec3(0,0,0);this->normal=new Vec3(0,0,0);return;}}~Tri3(){
delete this->v1;delete this->v2;delete this->v3;delete this->normal;}Tri3*copy(){Tri3*newCopy=new Tri3(true);newCopy->v1=this->v1->copy();
newCopy->v2=this->v2->copy();newCopy->v3=this->v3->copy();newCopy->normal=this->normal->copy();return newCopy;}void setv1(double x,double y,double z){
this->v1->x=x;this->v1->y=y;this->v1->z=z;}void setv1(Vec3*vec){delete this->v1;this->v1=vec->copy();}void setv2(double x,double y,double z){
this->v2->x=x;this->v2->y=y;this->v2->z=z;}void setv2(Vec3*vec){delete this->v2;this->v2=vec->copy();}void setv3(double x,double y,double z){
this->v3->x=x;this->v3->y=y;this->v3->z=z;}void setv3(Vec3*vec){delete this->v3;this->v3=vec->copy();}void setNormal(double x,double y,double z){
this->normal->x=x;this->normal->y=y;this->normal->z=z;}void setNormal(Vec3*normal){delete this->normal;this->normal=normal->copy();}
void updateNormal(){Vec3*vec1to2=new Vec3(this->v1->x-this->v2->x,this->v1->y-this->v2->y,this->v1->z-this->v2->z);Vec3*vec1to3=new Vec3(
this->v1->x-this->v3->x,this->v1->y-this->v3->y,this->v1->z-this->v3->z);Vec3*newNormal=vec1to2->crossProduct(vec1to3);newNormal->normalise();
delete this->normal;delete vec1to2,vec1to3;this->normal=newNormal;return;}bool isFacing(Vec3*vec){return this->normal->getAngle(vec)>=(pi/2);}};
class Color{public:static const Uint32 RED=0xFFFF0000;static const Uint32 GREEN =0xFF00FF00;static const Uint32 BLUE  =0xFF0000FF;
static const Uint32 BLACK =0xFF000000;static const Uint32 WHITE=0xFFFFFFFF;static const Uint32 GREY  =0xFF888888;static const Uint32 CHESS_WHITE=0xFFBBBBBB;
static const Uint32 CHESS_BLACK=0xFF444444;Uint32 rawValue;Uint8 redValue;Uint8 greenValue;Uint8 blueValue;Uint8 opacityValue;Color(Uint32 color){
this->rawValue=color;this->opacityValue=(Uint8)(color >> 24);this->redValue=(Uint8)(color >> 16);this->greenValue=(Uint8)(color >> 8);
this->blueValue=(Uint8)(color);}Color(Uint8 o,Uint8 r,Uint8 g,Uint8 b){this->redValue=r;this->greenValue=g;this->blueValue=b;this->opacityValue=o;
this->rawValue=0x00000000;this->rawValue|=o;this->rawValue <<=8;this->rawValue|=r;this->rawValue <<=8;this->rawValue|=g;this->rawValue <<=8;
this->rawValue|=b;}private:};class Drawer{public:Uint32*buffer;unsigned int bufferHeight;unsigned int bufferWidth;unsigned int bufferSize;
Drawer(Uint32*buffer,unsigned int bufferWidthInput,unsigned int bufferHeightInput){this->buffer=buffer;this->bufferWidth=bufferWidthInput;
this->bufferHeight=bufferHeightInput;this->bufferSize=bufferHeightInput*bufferWidthInput;}void writePixel(Uint32 pixel,int x,int y){
if(this->buffer==NULL){return;}if(x >=this->bufferWidth)return;if(y >=this->bufferHeight)return;int index=(y*this->bufferWidth)+x;
if(index>this->bufferSize)return;buffer[index]=pixel;return;}void drawLine(Uint32 pixel,Vec2*from,Vec2*to){if(this->buffer==NULL){return;}
int distx=to->x-from->x;int disty=to->y-from->y;int totalDist=max(abs(distx),abs(disty));for(int i=0; i<totalDist; i++){
int x=floor((from->x)+(distx*((double)i/totalDist)));int y=floor((from->y)+(disty*((double)i/totalDist)));this->writePixel(pixel,x,y);}
return;}void drawRect(Uint32 pixel,int startx,int starty,int endx,int endy){if(this->buffer==NULL){return;}int incerementI=1;int incerementJ=1;
if(startx>endx)incerementI=-1;if(starty>endy)incerementJ=-1;for(int i=startx; i!=endx; i+=incerementI){
for(int j=starty; j!=endy; j+=incerementJ){this->writePixel(pixel,i,j);}}return;}void drawElipse(Uint32 pixel,int locationx,int locationy,int radiusx,
int radiusy){int limit=radiusx*radiusy;double factorx=sqrt(radiusy/radiusx);double factory=1/factorx;for(int i=-radiusx; i<radiusx; i++){
for(int j=-radiusy; j<radiusy; j++){if(((factorx*i)*(factorx*i))+((factory*j)*(factory*j))< limit){
this->writePixel(pixel,locationx+i,locationy+j);}}}}void drawTriangle(Uint32 pixel,int x1,int y1,int x2,int y2,int x3,int y3){
int lowX,lowY;int midX,midY;int highX,highY;sortByX(x1,y1,x2,y2,x3,y3,&lowX,&lowY,&midX,&midY,&highX,&highY);int startY,endY;
double actualPointSideY=lowY;double actualLineSideY=lowY;double slopeLeftMid=((double)(midY-lowY))/(double)(midX-lowX);
double slopeMidRight=((double)(highY-midY))/(double)(highX-midX);double slopeLeftRight=((double)(highY-lowY))/(double)(highX-lowX);
if(lowX!=midX){for(int i=lowX; i<midX; i++){actualPointSideY+=slopeLeftMid;actualLineSideY+=slopeLeftRight;startY=min(actualPointSideY,actualLineSideY);
endY=max(actualPointSideY,actualLineSideY);for(int j=startY; j<endY; j++){this->writePixel(pixel,i,j);}}}if(midX!=highX){
for(int i=midX; i<highX; i++){actualPointSideY+=slopeMidRight;actualLineSideY+=slopeLeftRight;startY=min(actualPointSideY,actualLineSideY);
endY=max(actualPointSideY,actualLineSideY);for(int j=startY; j<endY; j++){this->writePixel(pixel,i,j);}}}return;}void drawTriangle(Uint32 pixel,Tri2*tri){
int x1=(int)round(tri->v1->x);int y1=(int)round(tri->v1->y);int x2=(int)round(tri->v2->x);int y2=(int)round(tri->v2->y);int x3=(int)round(tri->v3->x);
int y3=(int)round(tri->v3->y);this->drawTriangle(pixel,x1,y1,x2,y2,x3,y3);return;}private:
void sortByX(int x1,int y1,int x2,int y2,int x3,int y3,int*lowX,int*lowY,int*midX,int*midY,int*highX,int*highY){
bool oneSmallerThanTwo=(x1-x2)< 0;bool twoSmallerThanThree=(x2-x3)< 0;bool threeSmallerThanOne=(x3-x1)< 0;if(oneSmallerThanTwo&&!threeSmallerThanOne){
*lowX=x1;*lowY=y1;if(twoSmallerThanThree){*midX=x2;*midY=y2;*highX=x3;*highY=y3;}else{*midX=x3;*midY=y3;*highX=x2;*highY=y2;}}
else if(twoSmallerThanThree&&!oneSmallerThanTwo){*lowX=x2;*lowY=y2;if(threeSmallerThanOne){*midX=x3;*midY=y3;*highX=x1;*highY=y1;}
else{*midX=x1;*midY=y1;*highX=x3;*highY=y3;}}else if(threeSmallerThanOne&&!twoSmallerThanThree){*lowX=x3;*lowY=y3;if(oneSmallerThanTwo){
*midX=x1;*midY=y1;*highX=x2;*highY=y2;}else{*midX=x2;*midY=y2;*highX=x1;*highY=y1;}}return;}};class FrameState{public:class MouseState{
public:bool leftButtonIsDown;bool rightButtonIsDown;bool middleButtonIsDown;int posX;int posY;MouseState(){this->leftButtonIsDown=false;this->rightButtonIsDown=false;
this->posX=0;this->posY=0;}void setState(MouseState*state){this->leftButtonIsDown=state->leftButtonIsDown;this->rightButtonIsDown=state->rightButtonIsDown;
this->middleButtonIsDown=state->middleButtonIsDown;this->posX=state->posX;this->posY=state->posY;}void leftButtonDown(){this->leftButtonIsDown=true;
}void leftButtonUp(){this->leftButtonIsDown=false;}void middleButtonDown(){this->middleButtonIsDown=true;}void middleButtonUp(){this->middleButtonIsDown=false;}
void rightButtonDown(){this->rightButtonIsDown=true;}void rightButtonUp(){this->rightButtonIsDown=false;}void setPos(int x,int y){this->posX=x;this->posY=y;
}private:};class KeyboardState{public:bool*letterKeys;bool*numKeys;bool*miscKeys;KeyboardState(){this->letterKeys=new bool[26];this->numKeys=new bool[10];
this->miscKeys=new bool[9];for(int i=0; i<26; i++){this->letterKeys[i]=false;if(i<10)this->numKeys[i]=false;if(i<9)this->miscKeys[i]=false;}
return;}~KeyboardState(){delete[]this->letterKeys;delete[]this->numKeys;delete[]this->miscKeys;}void setState(KeyboardState*state){for(int i=0; i<26; i++){
this->letterKeys[i]=state->letterKeys[i];if(i<10)this->numKeys[i]=state->numKeys[i];if(i<9)this->miscKeys[i]=state->miscKeys[i];}}
bool*getKeyRef(int keyCode){switch(keyCode){case SDLK_a:
return &(this->letterKeys[letterKeyIndex::a]);break;case SDLK_b:return &(this->letterKeys[letterKeyIndex::b]);break;case SDLK_c:
return &(this->letterKeys[letterKeyIndex::c]);break;case SDLK_d:return &(this->letterKeys[letterKeyIndex::d]);break;case SDLK_e:
return &(this->letterKeys[letterKeyIndex::e]);break;case SDLK_f:return &(this->letterKeys[letterKeyIndex::f]);break;case SDLK_g:
return &(this->letterKeys[letterKeyIndex::g]);break;case SDLK_h:return &(this->letterKeys[letterKeyIndex::h]);break;case SDLK_i:
return &(this->letterKeys[letterKeyIndex::i]);break;case SDLK_j:return &(this->letterKeys[letterKeyIndex::j]);break;case SDLK_k:
return &(this->letterKeys[letterKeyIndex::k]);break;case SDLK_l:return &(this->letterKeys[letterKeyIndex::l]);break;case SDLK_m:
return &(this->letterKeys[letterKeyIndex::m]);break;case SDLK_n:return &(this->letterKeys[letterKeyIndex::n]);break;case SDLK_o:
return &(this->letterKeys[letterKeyIndex::o]);break;case SDLK_p:return &(this->letterKeys[letterKeyIndex::p]);break;case SDLK_q:
return &(this->letterKeys[letterKeyIndex::q]);break;case SDLK_r:return &(this->letterKeys[letterKeyIndex::r]);break;case SDLK_s:
return &(this->letterKeys[letterKeyIndex::s]);break;case SDLK_t:return &(this->letterKeys[letterKeyIndex::t]);break;case SDLK_u:
return &(this->letterKeys[letterKeyIndex::u]);break;case SDLK_v:return &(this->letterKeys[letterKeyIndex::v]);break;case SDLK_w:
return &(this->letterKeys[letterKeyIndex::w]);break;case SDLK_x:return &(this->letterKeys[letterKeyIndex::x]);break;case SDLK_y:
return &(this->letterKeys[letterKeyIndex::y]);break;case SDLK_z:return &(this->letterKeys[letterKeyIndex::z]);break;case SDLK_0:
return &(this->numKeys[numKeyIndex::zero]);break;case SDLK_1:return &(this->numKeys[numKeyIndex::one]);break;case SDLK_2:
return &(this->numKeys[numKeyIndex::two]);break;case SDLK_3:return &(this->numKeys[numKeyIndex::three]);break;case SDLK_4:
return &(this->numKeys[numKeyIndex::four]);break;case SDLK_5:return &(this->numKeys[numKeyIndex::five]);break;case SDLK_6:
return &(this->numKeys[numKeyIndex::six]);break;case SDLK_7:return &(this->numKeys[numKeyIndex::seven]);break;case SDLK_8:
return &(this->numKeys[numKeyIndex::eight]);break;case SDLK_9:return &(this->numKeys[numKeyIndex::nine]);break;case SDLK_BACKSPACE:
return &(this->miscKeys[miscKeyIndex::backspace]);break;case SDLK_TAB:return &(this->miscKeys[miscKeyIndex::tab]);break;case SDLK_RETURN:
return &(this->miscKeys[miscKeyIndex::enter]);break;case SDLK_ESCAPE:return &(this->miscKeys[miscKeyIndex::escape]);break;case SDLK_SPACE:
return &(this->miscKeys[miscKeyIndex::space]);break;case SDLK_CAPSLOCK:return &(this->miscKeys[miscKeyIndex::capslock]);break;case SDLK_LCTRL:
return &(this->miscKeys[miscKeyIndex::control]);break;case SDLK_LSHIFT:return &(this->miscKeys[miscKeyIndex::shift]);break;case SDLK_LALT:
return &(this->miscKeys[miscKeyIndex::alt]);break;}return NULL;}void keyDown(int keyCode){bool*key=this->getKeyRef(keyCode);if(key!=NULL)(*key)=true;
return;}void keyUp(int keyCode){bool*key=this->getKeyRef(keyCode);if(key!=NULL)(*key)=false;return;}bool keyIsDown(int keyCode){
bool*key=this->getKeyRef(keyCode);if(key!=NULL)return(*key)==true;else return false;}private:enum letterKeyIndex{a=0,b=1,c=2,d=3,e=4,
f=5,g=6,h=7,i=8,j=9,k=10,l=11,m=12,n=13,o=14,p=15,q=16,r=17,s=18,t=19,u=20,v=21,w=22,x=23,y=24,z=25};
enum numKeyIndex{zero=0,one=1,two=2,three=3,four=4,five=5,six=6,seven=7,eight=8,nine=9};enum miscKeyIndex{space=0,control=1,
shift=2,alt=3,capslock=4,tab=5,enter=6,escape=7,backspace=8};};int frameCount;MouseState*mouse;KeyboardState*keys;FrameState*lastFrame;
FrameState(bool hasChild=true){this->frameCount=0;this->mouse=new MouseState();this->keys=new KeyboardState();
if(hasChild)this->lastFrame=new FrameState(false);else this->lastFrame=NULL;}~FrameState(){if(this->mouse!=NULL)delete this->mouse;
if(this->keys!=NULL)delete this->keys;if(this->lastFrame!=NULL)delete this->lastFrame;}void addEvent(SDL_Event*event){if((*event).type==SDL_MOUSEBUTTONDOWN){
if((*event).button.button==SDL_BUTTON_LEFT){this->mouse->leftButtonDown();}if((*event).button.button==SDL_BUTTON_RIGHT){this->mouse->rightButtonDown();}
if((*event).button.button==SDL_BUTTON_MIDDLE){this->mouse->middleButtonDown();}return;}if((*event).type==SDL_MOUSEBUTTONUP){
if((*event).button.button==SDL_BUTTON_LEFT){this->mouse->leftButtonUp();}if((*event).button.button==SDL_BUTTON_RIGHT){this->mouse->rightButtonUp();}
if((*event).button.button==SDL_BUTTON_MIDDLE){this->mouse->middleButtonUp();}return;}if((*event).type==SDL_KEYDOWN){this->keys->keyDown((*event).key.keysym.sym);
}if((*event).type==SDL_KEYUP){this->keys->keyUp((*event).key.keysym.sym);}return;}void nextFrame(){if(this->lastFrame==NULL)return;this->lastFrame->setState(this);
this->frameCount++;return;}bool wasLeftJustPressed(){return(this->mouse->leftButtonIsDown&&!this->lastFrame->mouse->leftButtonIsDown);}bool wasRightJustPressed(){
return(this->mouse->rightButtonIsDown&&!this->lastFrame->mouse->rightButtonIsDown);}bool wasLeftJustReleased(){
return(!this->mouse->leftButtonIsDown&&this->lastFrame->mouse->leftButtonIsDown);}bool wasRightJustReleased(){
return(!this->mouse->rightButtonIsDown&&this->lastFrame->mouse->rightButtonIsDown);}int deltaMousePosX(){if(this->lastFrame==NULL)return 0;
return(this->mouse->posX)-(this->lastFrame->mouse->posX);}int deltaMousePosY(){if(this->lastFrame==NULL)return 0;
return(this->mouse->posY)-(this->lastFrame->mouse->posY);}bool keyIsDown(int keyCode){return this->keys->keyIsDown(keyCode);}private:
void setState(FrameState*state){this->frameCount=state->frameCount;this->mouse->setState(state->mouse);this->keys->setState(state->keys);}};class Camera{
public:Vec3*pos;Vec3*velocity;Vec3*acceleration;double yaw;double pitch;double roll;Vec3*facingDirection;Vec2*fov;double movementSpeed;Camera(){
this->pos=new Vec3(0,0,0);this->velocity=new Vec3(0,0,0);this->acceleration=new Vec3(0,0,0);this->facingDirection=new Vec3(0,0,0);
this->fov=new Vec2(0,0);this->yaw=0;this->pitch=0;this->roll=0;this->movementSpeed=3;}~Camera(){delete this->pos;delete this->velocity;
delete this->acceleration;delete this->facingDirection;delete this->fov;}void setPos(double x,double y,double z){this->pos->x=x;this->pos->y=y;this->pos->z=z;
return;}void setPos(Vec3*position){delete this->pos;this->pos=position->copy();}void setVelocity(double x,double y,double z){this->velocity->x=x;
this->velocity->y=y;this->velocity->z=z;return;}void setVelocity(Vec3*velocity){delete this->velocity;this->velocity=velocity->copy();}
void setAcceleration(double x,double y,double z){this->acceleration->x=x;this->acceleration->y=y;this->acceleration->z=z;return;}
void setAcceleration(Vec3*acceleration){delete this->acceleration;this->acceleration=acceleration->copy();}void setFacingDirection(double x,double y,double z){
this->facingDirection->x=x;this->facingDirection->y=y;this->facingDirection->z=z;return;}void setFacingDirection(Vec3*facingDirection){
delete this->facingDirection;this->facingDirection=facingDirection->copy();}void setFov(double x,double y){this->fov->x=x;this->fov->y=y;return;}
void setFov(Vec2*fov){delete this->fov;this->fov=fov->copy();}void rotate(double yaw,double pitch,double roll){this->facingDirection->rotate(yaw,pitch,roll);
this->yaw+=yaw;this->pitch+=pitch;this->roll+=roll;}void project(Vec3*vec,Vec2*displayPos){Vec3*relative=vec->copy();relative->sub(this->pos);
relative->rotate(this->yaw,0,0);relative->rotate(0,this->pitch,0);if(relative->z<0){delete relative;displayPos->x=-1;displayPos->y=-1;return;}
Vec2*tempVar=new Vec2(relative->x,relative->z);double dist=tempVar->magnitude();double dy=relative->y-this->pos->y;delete tempVar;
double angleYaw=getAngle(relative->x,relative->z);double anglePitch=(double)90-getAngle(dist,dy);double camYawFrom=-((double)this->fov->x/2);
double camYawTo=((double)this->fov->x/2);if(angleYaw>180){angleYaw-=360;}double locationX=inRange(angleYaw,(double)-180,(double)180);
double camPitchFrom=-(this->fov->y/2);double camPitchTo=(this->fov->y/2);if(anglePitch>180){anglePitch-=360;}
double locationY=inRange(anglePitch,(double)-180,(double)180);locationX=(((double)180*((double)2*locationX-(double)1))/this->fov->x)+((double)0.5);
locationY=(((double)180*((double)2*locationY-(double)1))/this->fov->y)+((double)0.5);displayPos->x=locationX;displayPos->y=locationY;return;}
void project(Mesh*mesh){for(int i=0; i<mesh->vertexCount; i++){this->project(mesh->verticies[i],mesh->projectedVerticies[i]);}}};class Display{
public:int width;int height;int widthOffset;int heightOffset;Display(int width,int height){this->width=width;this->height=height;this->widthOffset=0;
this->heightOffset=0;}Display(int width,int height,int widthOffset,int heightOffset){this->width=width;this->height=height;this->widthOffset=widthOffset;
this->heightOffset=heightOffset;}void toDisplayPos(Vec2*vec){int drawPosx=(int)(vec->x*(double)this->width);drawPosx+=this->widthOffset;
int drawPosy=this->height-(int)(vec->y*(double)this->height);drawPosy+=this->heightOffset;vec->x=drawPosx;vec->y=drawPosy;return;}
void toDisplayPos(Mesh*mesh){for(int i=0; i<mesh->vertexCount; i++){this->toDisplayPos(mesh->projectedVerticies[i]);}}};class Mesh{public:class IndexMap{
public:static const int VERTEX1=0;static const int VERTEX2=1;static const int VERTEX3=2;static const int NORMAL=3;int*map;int size;IndexMap(int size){
this->map=new int[size*4];this->size=size;}~IndexMap(){delete this->map;}IndexMap*copy(){IndexMap*newCopy=new IndexMap(this->size);
for(int i=0; i <(this->size*4); i++){newCopy->map[i]=this->map[i];}return newCopy;}void setGroup(int index,int v1,int v2,int v3,int normal){
int actualIndex=index*4;this->map[actualIndex+VERTEX1]=v1;this->map[actualIndex+VERTEX2]=v2;this->map[actualIndex+VERTEX3]=v3;
this->map[actualIndex+NORMAL]=normal;}void setValue(int index,int subIndex,int value){this->map[(index*4)+subIndex ]=value;}
void getGroup(int index,int*v1,int*v2,int*v3,int*normal){int actualIndex=index*4;(*v1)=this->map[actualIndex+VERTEX1];
(*v2)=this->map[actualIndex+VERTEX2];(*v3)=this->map[actualIndex+VERTEX3];(*normal)=this->map[actualIndex+NORMAL];}int getValue(int index,int subIndex){
return this->map[(index*4)+subIndex ];}};static Mesh*cubeMesh;static Mesh*tetrahedronMesh;Vec3**verticies;Vec3**normals;Tri3**tris;int vertexCount;
int normalCount;int triCount;IndexMap*indexMap;Vec2**projectedVerticies;Tri2**projectedTris;Mesh(){this->verticies=NULL;this->normals=NULL;this->tris=NULL;
this->vertexCount=0;this->normalCount=0;this->triCount=0;this->indexMap=NULL;this->projectedVerticies=NULL;this->projectedTris=NULL;}~Mesh(){
delete this->indexMap;for(int i=0; i<this->vertexCount; i++){ if(this->verticies[i]!=NULL)delete this->verticies[i]; 
if(this->projectedVerticies[i]!=NULL)delete this->projectedVerticies[i]; }for(int i=0; i<this->triCount; i++){if(this->tris[i]!=NULL)delete this->tris[i];
if(this->projectedTris[i]!=NULL)delete this->projectedTris[i];}for(int i=0; i<this->normalCount; i++){if(this->normals[i]!=NULL)delete this->normals[i];
}delete[]this->verticies;delete[]this->normals;delete[]this->tris;delete[]this->projectedVerticies;delete[]this->projectedTris;return;}Mesh*copy(){
Mesh*newCopy=new Mesh();newCopy->vertexCount=this->vertexCount;newCopy->normalCount=this->normalCount;newCopy->triCount=this->triCount;
newCopy->verticies=new Vec3*[this->vertexCount];newCopy->normals=new Vec3*[this->normalCount];newCopy->tris=new Tri3*[this->triCount];
newCopy->projectedVerticies=new Vec2*[this->vertexCount];newCopy->projectedTris=new Tri2*[this->triCount];for(int i=0; i<this->vertexCount; i++)
newCopy->verticies[i]=this->verticies[i]->copy();for(int i=0; i<this->normalCount; i++)newCopy->normals[i]=this->normals[i]->copy();
for(int i=0; i<this->triCount; i++){newCopy->tris[i]=new Tri3(true);newCopy->projectedTris[i]=new Tri2(true);}for(int i=0; i<this->vertexCount; i++)
newCopy->projectedVerticies[i]=new Vec2();newCopy->indexMap=this->indexMap->copy();newCopy->mapTris();return newCopy;}void move(double dx,double dy,double dz){
}void scale(double factorX,double factorY,double factorZ){}void rotate(double yaw,double pitch,double roll,Vec3*around=NULL){}void mapTris(){
int vertex1Index,vertex2Index,vertex3Index,normalIndex;for(int i=0; i<this->indexMap->size; i++){
this->indexMap->getGroup(i,&vertex1Index,&vertex2Index,&vertex3Index,&normalIndex);this->tris[i]->v1=this->verticies[vertex1Index];
this->tris[i]->v2=this->verticies[vertex2Index];this->tris[i]->v3=this->verticies[vertex3Index];this->tris[i]->normal=this->verticies[normalIndex];
this->projectedTris[i]->v1=this->projectedVerticies[vertex1Index];this->projectedTris[i]->v2=this->projectedVerticies[vertex2Index];
this->projectedTris[i]->v3=this->projectedVerticies[vertex3Index];}}static void initMeshes(){Vec3**vertexList;Vec3**normalList;Tri3**triList;
Vec2**projectedVertexList;Tri2**projectedTriList;IndexMap*indexMap;vertexList=new Vec3*[8];normalList=new Vec3*[6];triList=new Tri3*[12];
projectedVertexList=new Vec2*[8];projectedTriList=new Tri2*[12];vertexList[0]=new Vec3(-0.5,-0.5,-0.5);vertexList[1]=new Vec3(-0.5,-0.5,0.5);
vertexList[2]=new Vec3(0.5,-0.5,-0.5);vertexList[3]=new Vec3(0.5,-0.5,0.5);vertexList[4]=new Vec3(-0.5,0.5,-0.5);vertexList[5]=new Vec3(-0.5,0.5,0.5);
vertexList[6]=new Vec3(0.5,0.5,-0.5);vertexList[7]=new Vec3(0.5,0.5,0.5);normalList[0]=new Vec3(0,-1,0);normalList[1]=new Vec3(0,1,0);
normalList[2]=new Vec3(-1,0,0);normalList[3]=new Vec3(1,0,0);normalList[4]=new Vec3(0,0,-1);normalList[5]=new Vec3(0,0,1);
indexMap=new IndexMap(12);indexMap->setGroup(0,0,3,1,0);indexMap->setGroup(1,0,3,2,0);indexMap->setGroup(2,4,7,5,1);
indexMap->setGroup(3,4,7,6,1);indexMap->setGroup(4,0,5,4,2);indexMap->setGroup(5,0,5,1,2);indexMap->setGroup(6,2,7,3,3);
indexMap->setGroup(7,2,7,6,3);indexMap->setGroup(8,0,6,2,4);indexMap->setGroup(9,0,6,4,4);indexMap->setGroup(10, 1,7,3,5);
indexMap->setGroup(11, 1,7,5,5);for(int i=0; i<12; i++)triList[i]=new Tri3(true);for(int i=0; i<8; i++)projectedVertexList[i]=new Vec2();
for(int i=0; i<12; i++)projectedTriList[i]=new Tri2(true);Mesh::cubeMesh=new Mesh();Mesh::cubeMesh->indexMap=indexMap;Mesh::cubeMesh->verticies=vertexList;
Mesh::cubeMesh->normals=normalList;Mesh::cubeMesh->vertexCount=8;Mesh::cubeMesh->normalCount=6;Mesh::cubeMesh->triCount=12;Mesh::cubeMesh->tris=triList;
Mesh::cubeMesh->projectedVerticies=projectedVertexList;Mesh::cubeMesh->projectedTris=projectedTriList;Mesh::cubeMesh->mapTris();}};Mesh*Mesh::cubeMesh=NULL;
Mesh*Mesh::tetrahedronMesh=NULL;typedef uint8_t int1byte;typedef uint16_t int2bytes;typedef uint32_t int4bytes;typedef uint64_t int8bytes;std::ofstream outputFile;
void logInit(std::string fileName){try{outputFile.open(fileName);} catch(...){std::cout << "Couldnt open log.txt" << std::endl;system("pause");return;}}
void logClear(){if(!outputFile.is_open()){std::cout << "logInit must be called first" << std::endl;system("pause");return;}outputFile.clear();}void logNewLine(){
if(!outputFile.is_open()){std::cout << "logInit must be called first" << std::endl;system("pause");return;}outputFile << "\n";}
void logWrite(std::string message,bool newLine=false){if(!outputFile.is_open()){std::cout << "logInit must be called first" << std::endl;system("pause");return;}
outputFile << message;if(newLine)outputFile << std::endl;return;}void logWrite(char message,bool newLine=false){std::string outputString;outputString+=message;
logWrite(outputString,newLine);}void logWrite(wchar_t message,bool newLine=false){std::string outputString;outputString+=message;logWrite(outputString,newLine);
}void logWrite(int message,bool newLine=false){logWrite(std::to_string(message),newLine);return;}void logWrite(long message,bool newLine=false){
logWrite(std::to_string(message),newLine);return;}void logWrite(long long message,bool newLine=false){logWrite(std::to_string(message),newLine);return;}
void logWrite(double message,bool newLine=false){logWrite(std::to_string(message),newLine);return;}void logWrite(int8bytes message,bool newLine=false){
std::stringstream stream;stream << "0x" << std::hex << std::uppercase << message;std::string hexString=stream.str();logWrite(hexString,newLine);return;}
void logWrite(int2bytes message,bool newLine=false){logWrite((int8bytes)message,newLine);return;}void logWrite(int4bytes message,bool newLine=false){
logWrite((int8bytes)message,newLine);return;}void logWrite(int1byte message,bool newLine=false){logWrite((int8bytes)message,newLine);return;}
void logVar(std::string message,int variable){logWrite(message,false);logWrite(": ",false);logWrite(variable,true);}
void logVar(std::string message,double variable){logWrite(message,false);logWrite(": ",false);logWrite(variable,true);}
void drawMesh(Mesh*mesh,Camera*camera,Drawer*drawer){for(int i=0; i<mesh->triCount; i++){if(!mesh->tris[i]->isFacing(camera->facingDirection))continue;
drawer->drawTriangle(Color::WHITE,mesh->projectedTris[i]);}for(int i=0; i<mesh->vertexCount; i++){
drawer->drawElipse(Color::GREEN,mesh->projectedVerticies[i]->x,mesh->projectedVerticies[i]->y,5,5);}}void drawSky(Drawer*drawer,Camera*camera,Display*display){
Vec2*heightVec=new Vec2(display->height,0);heightVec->rotate(camera->pitch);double height=(display->height/2)+heightVec->y;delete heightVec;
if(height<0)return;uint32_t skyColorLight=0xFF323296;uint32_t skyColorDark=0xFF161648;drawer->drawRect(skyColorLight,display->widthOffset,display->heightOffset,
display->widthOffset+display->width,display->heightOffset+(height-(double)25));drawer->drawRect(skyColorDark,display->widthOffset,
display->heightOffset+(height-(double)25),display->widthOffset+display->width,display->heightOffset+height);return;}Vec3*points[8];Mesh*cube;
void initGraphics(){for(int i=0; i<8; i++){int x=i % 2;int y=(int)(i % 4)>=2;int z=(int)i >=4;points[i]=new Vec3(5*x,5*y,5*z);}
cube=Mesh::cubeMesh->copy();}void drawGraphics(Drawer*drawer,FrameState*frameState,Camera*camera,Display*display){drawSky(drawer,camera,display);
camera->project(cube);display->toDisplayPos(cube);drawMesh(cube,camera,drawer);return;}const int WINDOW_HEIGHT=600;const int WINDOW_WIDTH=1000;
SDL_Window*window=NULL;SDL_Renderer*renderer=NULL;SDL_Texture*texture=NULL;Uint32*buffer=NULL;void getBuffer(){int*windowWidthTemp=new int(WINDOW_WIDTH);
SDL_LockTexture(texture,NULL,(void**)&buffer,windowWidthTemp);delete windowWidthTemp;}void flip(){int*windowWidthTemp=new int(WINDOW_WIDTH);
SDL_UnlockTexture(texture);SDL_UpdateTexture(texture,NULL,buffer,(*windowWidthTemp)*sizeof(Uint32));SDL_RenderClear(renderer);
SDL_RenderCopy(renderer,texture,NULL,NULL);SDL_RenderPresent(renderer);buffer=NULL;delete windowWidthTemp;}
void handleInput(FrameState*frameState,Camera*camera,double dt){if(frameState->keyIsDown(SDLK_LSHIFT))camera->movementSpeed=10;else camera->movementSpeed=3;
double dist=((double)camera->movementSpeed)*(dt/1000);Vec2*cameraMovVec=new Vec2();if(frameState->keyIsDown(SDLK_w))cameraMovVec->y+=dist;
if(frameState->keyIsDown(SDLK_s))cameraMovVec->y-=dist;if(frameState->keyIsDown(SDLK_a))cameraMovVec->x-=dist;
if(frameState->keyIsDown(SDLK_d))cameraMovVec->x+=dist;cameraMovVec->rotate(-camera->yaw);camera->pos->x+=cameraMovVec->x;
camera->pos->z+=cameraMovVec->y;delete cameraMovVec;if(frameState->keyIsDown(SDLK_SPACE))camera->pos->y+=dist;if(frameState->keyIsDown(SDLK_LCTRL))
camera->pos->y-=dist;if(frameState->mouse->leftButtonIsDown){camera->rotate((double)(frameState->deltaMousePosX())*(double)0.002,0,0);
camera->rotate(0,(double)(frameState->deltaMousePosY())*(double)-0.002,0);}}int main(int argc,char*argv[]){if(SDL_Init(SDL_INIT_EVERYTHING)< 0){
fprintf(stderr,"SDL_Init Failed! SDL_Error: %s\n",SDL_GetError());return 1;}
window=SDL_CreateWindow("SDL2 Window",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);if(window==NULL){
fprintf(stderr,"CreateWindow Failed! SDL_Error: %s\n",SDL_GetError());return 1;}renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
if(renderer==NULL){fprintf(stderr,"CreateRenderer Failed! SDL_Error: %s\n",SDL_GetError());return 1;}
texture=SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,WINDOW_WIDTH,WINDOW_HEIGHT);
if(texture==NULL){fprintf(stderr,"CreateTexture Failed! SDL_Error: %s\n",SDL_GetError());return 1;}logInit("log.txt");logClear();logWrite("Starting...",true);
Mesh::initMeshes();initGraphics();FrameState*frameState=new FrameState();Drawer*drawer;SDL_Event event;Display*display1=new Display(WINDOW_WIDTH,WINDOW_HEIGHT);
Camera*camera1=new Camera();camera1->setPos(0,0,-10);camera1->setFov(90,54);camera1->setFacingDirection(0,0,1);
auto timeVar=std::chrono::high_resolution_clock::now();double appStartTime=std::chrono::duration_cast<std::chrono::milliseconds>(timeVar.time_since_epoch()).count();
double lastFrameTime=appStartTime;double thisFrameTime=appStartTime;double dt;bool leave=false;while(!leave){logWrite("Frame ",false);
logWrite(frameState->frameCount,true);timeVar=std::chrono::high_resolution_clock::now();lastFrameTime=thisFrameTime;
thisFrameTime=std::chrono::duration_cast<std::chrono::milliseconds>(timeVar.time_since_epoch()).count();dt=thisFrameTime-lastFrameTime;int mouseX,mouseY;
SDL_GetMouseState(&mouseX,&mouseY);frameState->mouse->setPos(mouseX,mouseY);while(SDL_PollEvent(&event)!=0){
if(event.type==SDL_QUIT){ leave=true; std::cout<<"closed"; }else frameState->addEvent(&event);}handleInput(frameState,camera1,dt);getBuffer();
drawer=new Drawer(buffer,(int)WINDOW_WIDTH,(int)WINDOW_HEIGHT);drawer->drawRect(Color::BLACK,0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
drawGraphics(drawer,frameState,camera1,display1);delete drawer;flip();frameState->nextFrame();}delete frameState;delete camera1;delete display1;
SDL_DestroyWindow(window);SDL_Quit();return 0;}