# Untitled - By: Administrator - 周一 4月 15 2019
# 使用的灰度图模式  从白板中识别黑球
#如果要用彩图模式,请参考openmv自带的历程
import sensor, image, time
from pyb import UART
from pyb import LED
import json

sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.GRAYSCALE) # use RGB565.
sensor.set_framesize(sensor.QVGA) # use QQVGA for speed.
sensor.skip_frames(10) # Let new settings take affect.
sensor.set_auto_whitebal(False) # turn this off.
#sensor.set_hmirror(True)#水平翻转
#sensor.set_vflip(True)#竖直反转
clock = time.clock() # Tracks FPS.

uart = UART(3, 115200)#串口配置
def find_max(blobs):#寻找最大色块的函数
    max_size=50 #把小于50面积的色块滤掉,如果小球面积本身就很小,则需要把这个值调小一点
    max_blob=0
    for blob in blobs:
        if ((blob.pixels() > max_size)and(blob.w()<26)and(blob.h()<26)and(blob.w()>5)and(blob.h()>5)):
        #对识别的色块进行限制,小球在摄像头中的长宽应该要大于5,小于26
            max_blob=blob
            max_size = blob.pixels()
    return max_blob


black=(0, 72)#阈值

x1=(33,7)#左上角,因为板子外边有很多干扰,所以只取中间板子的部分进行识别
left_roi = [x1[0],x1[1],219,220]#板子区域
while(True):
    clock.tick()
    img = sensor.snapshot() # Take a picture and return the image.
    blobs = img.find_blobs([black],roi=left_roi)#参数为 阈值,识别区域
    if blobs:
        max_blob=find_max(blobs)
        if max_blob!=0:
            img.draw_rectangle(max_blob.rect())#画方框
           # img.draw_cross(max_blob.cx(), max_blob.cy())
            x_ban=int(max_blob.cx()-x1[0])#求相对于板子的坐标
            y_ban=int(max_blob.cy()-x1[1])#求相对于板子的坐标
            if x_ban<0:
                x_ban=0
            if x_ban>220:
                x_ban=220
            if y_ban<0:
                y_ban=0
            if y_ban>220:
                y_ban=220
            #对坐标进行限幅,因为板子像素就在这范围内。
            checkout=(x_ban+y_ban)#校验位,为x坐标+y坐标 的低八位
            data = bytearray([0xAA,0x55,x_ban,y_ban,checkout,0x54])#转成16进制
            #如果识别的坐标大于255，建议除以2之后再发，因为一个字节范围只有0-255
            uart.write(data)#通过串口发送出去数据
    else:
        print('not found!')
    print(clock.fps())#帧率


