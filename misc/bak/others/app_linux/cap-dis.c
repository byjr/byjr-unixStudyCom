#include<fcntl.h>  
#include<unistd.h>  
#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<errno.h>  
#include<sys/ioctl.h>  
#include<sys/mman.h>  
//#include<SDL2/SDL.h>//if SDL2 then use texture instead of overlay  #include<linux/videodev2.h>  
#include<SDL/SDL.h>  
/* 
VIDIOC_QUERYCAP     // 获取设备支持的操作
VIDIOC_G_FMT        // 获取设置支持的视频格式
VIDIOC_S_FMT        // 设置捕获视频的格式
VIDIOC_REQBUFS      // 向驱动提出申请内存的请求 
VIDIOC_QUERYBUF     // 向驱动查询申请到的内存 
VIDIOC_QBUF         // 将空闲的内存加入可捕获视频的队列 
VIDIOC_DQBUF        // 将已经捕获好视频的内存拉出已捕获视频的队列 
VIDIOC_STREAMON     // 打开视频流 
VIDIOC_STREAMOFF    // 关闭视频流 
VIDIOC_QUERYCTRL    // 查询驱动是否支持该命令 
VIDIOC_G_CTRL       // 获取当前命令值 
VIDIOC_S_CTRL       // 设置新的命令值 
VIDIOC_G_TUNER      // 获取调谐器信息 
VIDIOC_S_TUNER      // 设置调谐器信息 
VIDIOC_G_FREQUENCY  // 获取调谐器频率 
VIDIOC_S_FREQUENCY  // 设置调谐器频率    
*/
  
  
  
  
#define DEV_CAMERA "/dev/video0"  
#define REQBUF_COUNT    4  
#define handle_err(msg) \  
                do  {   perror(msg);    exit(EXIT_FAILURE);     } while(0)  
#define FREE(fp) \  
                while(fp) { free(fp);   fp =NULL;   }  
  
typedef struct {  
    void* start;  
    unsigned int length;  
}BUFFER;  
  
SDL_Surface *pscreen = NULL;  
SDL_Overlay *overlay = NULL;  
SDL_Rect drect;  
SDL_Event sdlevent;  
SDL_mutex *affmutex = NULL;  
unsigned char frmrate;  
unsigned charchar *p = NULL;  
unsigned int currtime;  
unsigned int lasttime;  
char* status = NULL;  
  
  
  
  
  
int process_image(BUFFER *buf, int width, int height);  
  
  
int main()  
{  
    //SDL INIT  
    //if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO |  SDL_INIT_TIMER ) < 0)  
     if (SDL_Init(SDL_INIT_EVERYTHING) < 0)  
    {  
        fprintf(stderr, "Can not initialize SDL: %s\n", SDL_GetError());  
        exit(1);  
    }  
  
    //dev info  
    struct v4l2_capability cap;  
    int fd;  
    //fd = open(DEV_CAMERA,O_RDONLY);//the mmap MAP_SHARED will fail:Invalid argument  
    fd = open(DEV_CAMERA,O_RDWR);  
    if(fd<0)  
    {  
        printf("can not open %s\n",DEV_CAMERA);  
        return -1;  
    }  
    ioctl(fd,VIDIOC_QUERYCAP,&cap);  
    printf("DriverName:%s\nCard Name:%s\nBus info:%s\nDriverVersion:%u.%u.%u\n",cap.driver,cap.card,cap.bus_info,(cap.version>>16) & 0xFF,(cap.version>>8) & 0xFF,cap.version & 0xFF);  
  
    //format  
    struct v4l2_fmtdesc fmtdesc;  //格式描述
    fmtdesc.index = 0;  
    fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;  
    printf("support format:\n");  
    while(ioctl(fd,VIDIOC_ENUM_FMT,&fmtdesc) != -1)  
    {  
        printf("\t%d.%s\n",1 + fmtdesc.index++,fmtdesc.description);  
    }  
  
    struct v4l2_format fmt;  
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;  
     ioctl(fd,VIDIOC_G_FMT,&fmt);  
     printf("Current format information:\n\twidth:%d\n\theight:%d\n",fmt.fmt.pix.width,fmt.fmt.pix.height);  
  
     fmtdesc.index = 0;  
     fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;  
     while(ioctl(fd,VIDIOC_ENUM_FMT,&fmtdesc) != -1)  
     {  
         if(fmtdesc.pixelformat & fmt.fmt.pix.pixelformat)  
         {  
            printf("\tformat:%s\n",fmtdesc.description);  
            break;  
         }  
         fmtdesc.index++;  
     }  
  
     fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB32;  
     if(ioctl(fd,VIDIOC_TRY_FMT,&fmt) == -1)  
     {  
         perror("ioctl err");  
         if(errno == EINVAL)  
             printf("not support format RGB32\n");  
     }  
     else  
        printf("RGB32 is supported\n");  
  
     //query buf  
     struct v4l2_requestbuffers reqbuf;  
     reqbuf.count = REQBUF_COUNT;  
     reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;  
     reqbuf.memory = V4L2_MEMORY_MMAP;  
     ioctl(fd,VIDIOC_REQBUFS,&reqbuf);  
  
     BUFFER *buffers;  
  
     buffers = (BUFFER*)calloc(reqbuf.count,sizeof(*buffers));  
     if(!buffers)  
     {  
         handle_err("calloc");  
     }  
     for(unsigned int n_buf = 0;n_buf < reqbuf.count;n_buf++)  
     {  
         struct v4l2_buffer buf;  
         memset(&buf,0,sizeof(buf));  
         buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;  
         buf.memory = V4L2_MEMORY_MMAP;  
         buf.index = n_buf;  
  
         if(-1 == ioctl(fd,VIDIOC_QUERYBUF,&buf))  
         {  
             handle_err("ioctl");  
         }  
         buffers[n_buf].length = buf.length;  
         printf("buf.length = %d,buf.m.offset = %d\n", buf.length,buf.m.offset);  
  
         buffers[n_buf].start = mmap(NULL,buf.length,PROT_READ|PROT_WRITE,MAP_SHARED,fd,buf.m.offset);  
         //buffers[n_buf].start = mmap(NULL,buf.length,PROT_READ,MAP_SHARED,fd,buf.m.offset);  
         if(MAP_FAILED == buffers[n_buf].start)  
         {  
             handle_err("mmap");  
         }  
     }  
  
     //get camera data  
     unsigned int i;  
     enum v4l2_buf_type type;  
     for(i=0;i<reqbuf.count;i++)  
     {  
         struct v4l2_buffer buf;  
         memset(&buf,0,sizeof(buf));  
         buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;  
         buf.memory = V4L2_MEMORY_MMAP;  
         buf.index = i;  
         ioctl(fd,VIDIOC_QBUF,&buf);  
     }  
     type = V4L2_BUF_TYPE_VIDEO_CAPTURE;  
     ioctl(fd,VIDIOC_STREAMON,&type);  
  
     int width = fmt.fmt.pix.width;  
     int height = fmt.fmt.pix.height;  
     pscreen =  
             SDL_SetVideoMode(width, height, 0,  
                              SDL_SWSURFACE );  
     overlay =  
             SDL_CreateYUVOverlay(width, height,  
                                  SDL_YUY2_OVERLAY, pscreen);//format:YUYV use SDL_YUY2_OVERLAY  
  
     p = (unsigned charchar *) overlay->pixels[0];  
     drect.x = 0;  
     drect.y = 0;  
     drect.w = pscreen->w;  
     drect.h = pscreen->h;  
     int quit = 0;  
     while (quit == 0)  
     {  
         while (SDL_PollEvent(&sdlevent))  
         {  
             if (sdlevent.type == SDL_QUIT)  
             {  
                 quit =1;  
                 break;  
             }  
         }  
  
         for(i =0;i<reqbuf.count;i++)  
         {  
             struct v4l2_buffer buf;  
             memset(&buf,0,sizeof(buf));  
             buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;  
             buf.memory = V4L2_MEMORY_MMAP;  
             ioctl(fd,VIDIOC_DQBUF,&buf);  
  
             //deal with data  
             process_image(&buffers[i],fmt.fmt.pix.width,fmt.fmt.pix.height);  
  
             ioctl(fd,VIDIOC_QBUF,&buf);  
         }  
     }  
  
     SDL_DestroyMutex(affmutex);  
     SDL_FreeYUVOverlay(overlay);  
     printf("Clean Up done Quit \n");  
     SDL_Quit();  
  
     type = V4L2_BUF_TYPE_VIDEO_CAPTURE;  
     ioctl(fd,VIDIOC_STREAMOFF,&type);  
     for(i=0;i<reqbuf.count;i++)  
     {  
         if(-1 == munmap(buffers[i].start,buffers[i].length))  
         {  
             handle_err("munmap");  
         }  
     }  
    FREE(buffers);  
    close(fd);  
}  
  
  
  
int process_image(BUFFER *buf,int width,int height)  
{  
    affmutex = SDL_CreateMutex();  
    SDL_LockSurface(pscreen);  
    SDL_LockYUVOverlay(overlay);  
    memcpy(p, buf->start, width * height * 2 /*buf->length*/);  
    SDL_UnlockYUVOverlay(overlay);  
    SDL_UnlockSurface(pscreen);  
  
    SDL_DisplayYUVOverlay(overlay, &drect); /* dispaly it */  
  
    SDL_WM_SetCaption("Jun's camera", NULL);  
    SDL_Delay(40);  
    return 0;  
}  

