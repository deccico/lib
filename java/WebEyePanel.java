
import java.awt.*;
import java.awt.image.*;
import java.awt.Color.*;
import java.io.*;
import java.util.*;
import java.awt.event.*;

public class WebEyePanel extends Panel implements Runnable {

  WebEyeController controller;
  WebEyeDecoder decoder;
  Timer timer;
  int count;
  // image size ...
  Image image ;

  // Image decryption key-string
  String strEncKey = null;
  // user name and passwd
  String username, passwd;

  boolean bImageSaveMode = false;
  boolean bImageLoadMode = false;

  /** BITMAP HEADER class **/
  class BITMAPFILEHEADER {
      byte[]  bfType = {0x42, 0x4d};
      int   bfSize;
      byte[]  bfReserved1 = {0x00, 0x00};
      byte[]  bfReserved2 = {0x00, 0x00};
      int   bfOffBits = 0x3E;
  }
  class BITMAPINFO {
      /** BITMAPINFO HEADER **/
      int   biSize = 0x30;
      int   biWidth;
      int   biHeight;
      byte[]  biPlanes = {0x00, 0x01};
      byte[]  biBitCount = {0x00, 0x18};
      byte[]   biCompression = {0x41, 0x44, 0x56, 0x31};
      int   biSizeImage;
      int   biXPelsPerMeter = 0x00000000;
      int   biYPelsPerMeter = 0x00000000;
      int   biClrUsed = 0x00000000;
      int   biClrImportant = 0x00000000;
      /** RGBQUAD **/
      byte[] rgbQuad = {0x00, 0x00, 0x00, 0x00};
  }

  BITMAPFILEHEADER bf = new BITMAPFILEHEADER();
  BITMAPINFO bi = new BITMAPINFO();

  public WebEyePanel() {
    try {
      jbInit();
      controller = new WebEyeController(2, 0, false);
      decoder = new WebEyeDecoder();
      timer = new Timer(1000);
      username = null;
      passwd = null;
    }
    catch(Exception ex) {
      ex.printStackTrace();
    }
  }
  void jbInit() throws Exception {
    this.setBackground(Color.black);
    this.setLayout(null);
  }

  public void stopAll() {
  try{
      bImageLoadMode = false;
      bImageSaveMode = false;
      if( fin != null ) fin.close();
      if( fout != null ) fout.close();
  } catch(IOException e){}
      timer.stop();
      timer = null;
  }

  public boolean connect(String ip, int port) {
      System.out.println(ip+" "+port);
      return controller.connect(ip, port);
  }

  public void setImageResolution(int res) {
      controller.setImageResolution(res);
  }

  public void setGrayMode(boolean gm) {
      controller.setGrayMode(gm);
  }

  public void setVideoSource(byte ch) {
      controller.setVideoSource(ch);
  }

  int oldRes = 0;

  // for Wavelet image data I/O ...
  FileInputStream fin;
  FileOutputStream fout;
  DataInputStream din;
  DataOutputStream dout;

  public void initBITMAPHEADER() {

  }
  public boolean setInputFile(File inFile) {
      try {
          fin = new FileInputStream(inFile);
          din = new DataInputStream(fin);
          bImageLoadMode = true;
          return true;
      } catch( FileNotFoundException e) {
          return false;
      }
  }

  public boolean setOutputFile(File outFile) {
      try {
          fout = new FileOutputStream(outFile);
          dout = new DataOutputStream(fout);
          bImageSaveMode = true;
          return true;
      } catch(IOException e) {
          return false;
      }
  }

  public boolean writeOneFrame(byte[] frameBytes) {
      try {
          if( bf.bfSize == 0 ) return false;
          int tempInt;
          /** write BITMAPFILEHEADER **/
          dout.write(bf.bfType, 0, 2);
          tempInt = convertToJavaType(bf.bfSize);
          dout.writeInt(tempInt);
          dout.write(bf.bfReserved1, 0, 2);
          dout.write(bf.bfReserved2, 0, 2);
          tempInt = convertToJavaType(bf.bfOffBits);
          dout.writeInt(tempInt);

          /** write BITMAPINFO **/
          tempInt = convertToJavaType(bi.biSize);
          dout.writeInt(tempInt);
          tempInt = convertToJavaType(bi.biWidth);
          dout.writeInt(tempInt);
          tempInt = convertToJavaType(bi.biHeight);
          dout.writeInt(tempInt);
          dout.write(bi.biPlanes, 0, 2);
          dout.write(bi.biBitCount, 0, 2);
          dout.write(bi.biCompression, 0, 4);
          tempInt = convertToJavaType(bi.biSizeImage);
          dout.writeInt(tempInt);
          dout.writeInt(bi.biXPelsPerMeter);
          dout.writeInt(bi.biYPelsPerMeter);
          dout.writeInt(bi.biClrUsed);
          dout.writeInt(bi.biClrImportant);
          dout.write(bi.rgbQuad, 0, 4);
          dout.write(bi.rgbQuad, 0, 4);

          /** write Frame Data **/
          dout.write(frameBytes, 0, bi.biSizeImage);
          return true;
      } catch(IOException e){
          return false;
      }
  }

  public byte[] readOneFrame() {
      byte[] bmHeader;
      byte[] frameBytes;
      try {
          bmHeader = new byte[62];
          din.read(bmHeader, 0, 0x3E);

          int length = readBMPHeader(bmHeader);
          if( length == 0 ) return null;
          frameBytes = new byte[length];
          din.read(frameBytes, 0, length);
          return frameBytes;
      }catch(IOException e){
          return null;
      }
  }

  public int readBMPHeader(byte[] data) {
      try {
          byte[] temp = new byte[62];
          int frameSize = 0;
          ByteArrayInputStream bin = new ByteArrayInputStream(data);
          DataInputStream tDin = new DataInputStream(bin);
          tDin.read(temp, 0, 2);
          frameSize = this.convertToJavaType(tDin.readInt())-0x3E;
          tDin.close();
          bin.close();
          return frameSize;
      } catch(IOException e){
          return 0;
      }
  }
  public void extractImageInfo(byte[] frameBytes, boolean bSaveMode) {
      byte byteval;
      int mRotate, chan_id, res;
      int sTime;
      int[] vitcMark = {0xffffffff, 0x00000040};
      short mTime;
      boolean isNTSC, isGrayMode, isProgressMode, isEncrypted;
      boolean usePanTilt, useZoom;

      // check vitc and extract time information..
      int vitcMark0 = (frameBytes[0]>>24) |
                     (frameBytes[1]>>16) |
                     (frameBytes[2]>> 8) |
                     frameBytes[3];
      int vitcMark1 = (frameBytes[4]>>24) |
                     (frameBytes[5]>>16) |
                     (frameBytes[6]>> 8) |
                     frameBytes[7];
      if( vitcMark0 == vitcMark[0] && vitcMark1 == vitcMark[1] ) {
          sTime = frameBytes[8]&0xff |
                  ((int)frameBytes[9]&0xff)<<8 |
                  ((int)frameBytes[10]&0xff)<<16 |
                  ((int)frameBytes[11]&0xff)<<24;

          //get image informations ...
          byteval = frameBytes[14];
          // image resolution cheak
          res  = (int)(byteval & controller.M1_RESOLUTION_BITS);
          // video type check
          isNTSC = ((byteval & controller.M1_SIGNAL_TYPE_BIT) == controller.M1_SIGNAL_TYPE_BIT) ? false : true;
          //check gray mode or not
          isGrayMode = ((byteval & controller.M1_GRAY_MODE_BIT) == controller.M1_GRAY_MODE_BIT) ? true : false;
          //check progressive mode
          isProgressMode = ((byteval & controller.M1_PROGRESSIVE_MODE_BIT) == controller.M1_PROGRESSIVE_MODE_BIT) ? true : false;

          // attach Pan/Tilt/Zoom device ?
          usePanTilt = ((byteval & controller.M1_PANTILT_USE_BIT) == controller.M1_PANTILT_USE_BIT) ? true : false;
          useZoom = ((byteval & controller.M1_ZOOM_USE_BIT) == controller.M1_ZOOM_USE_BIT) ? true : false;

          //--------------------------------
          //extract mode2...
          byteval = frameBytes[15];
          isEncrypted = ((byteval&(byte)controller.M2_IMG_ENC_BIT) == 0) ? false:true;
          mRotate = (int)(byteval&(byte)controller.M2_CAM_ROT_BITS);
          chan_id = ((int)byteval&(byte)controller.M2_VID_CHAN_BITS)>>3;
          int imageWidth = 0, imageHeight = 0;

          switch( res ){
              case 0: imageWidth = 90; imageHeight = 60;
                  break;
              case 1: imageWidth = 180; imageHeight = 121;
                  break;
              case 2: imageWidth = 360; imageHeight = 243;
                  break;
              case 3: imageWidth = 720; imageHeight = 243;
                  break;
              case 4: imageWidth = 720; imageHeight = 486;
                  break;
          }
          if( bSaveMode) {
              int frameSize = frameBytes.length;
              bf.bfSize = frameSize+0x3E;
              bi.biSizeImage = frameSize;
              bi.biWidth = imageWidth;
              bi.biHeight = imageHeight;
          } else {
              // decompress WebEye Image data
              decoder.resolution = res;
              decoder.isNTSC = isNTSC;
              decoder.isGrayMode = isGrayMode;
              decoder.isProgressMode = isProgressMode;
              decoder.chan_id = chan_id;
              decoder.mRotate = mRotate;
              decoder.isEncrypted = isEncrypted;
              decoder.bUsePalType = false;
              if( isEncrypted ) {
                  decoder.encKey = strEncKey.getBytes();
              }
              // display bitmap image to Test-Panel...
              if( oldRes != res ) {
                  repaint();
                  oldRes = res;
              }

              displayImage(frameBytes);
          }
      }
  }

  public void setAuthInfo(String uname, String pass){
      username = uname;
      passwd = pass;
  }

  public void run(){
      byte[] frameBytes;
      count = 0;
      timer.start();
      controller.setResolution(2);

      while(true) {
          count++;
          /** load wavelet image from file **/
          if( bImageLoadMode ) {
              frameBytes = readOneFrame();
              if( frameBytes == null ) return;
              extractImageInfo(frameBytes, bImageSaveMode);
          }
          else {
              byte ret = controller.requestOneFrame();
              //System.out.println(Integer.toHexString(ret));
              if( ret == 0x40 ){
                  controller.sendAuthenticationCode(username, passwd);
              }
              else if( ret == 0x30 ){
                  frameBytes = controller.readFrame();
                  /** save wavelet image to file **/
                  extractImageInfo(frameBytes, bImageSaveMode);
                  if( bImageSaveMode ) {
                      writeOneFrame(frameBytes);
                  }
              } else if(ret == controller.TOF_RES_PARM) { // receive res_parm
//                  System.out.println("Image quality level::"+controller.resParam.qualityLevel+" QBOX ambient level::"+controller.resParam.qBOXAmbientLevel);
              }
          }

          try {
              Thread.sleep(20);
          }catch(InterruptedException e){}
      }
  }

      public void displayImage(byte[] frameBytes) {
          boolean ret = decoder.updateFrame(frameBytes);
          image = decoder.getImage();
          Graphics graphic = getGraphics();

          //image = image.getScaledInstance(360, 243, Image.SCALE_FAST);
          graphic.drawImage(image , 0 , 10 , null );
      }

      public void update(Graphics g) {
          paint(g);
      }


      public void paint(Graphics g) {
          updateScreen(g);
      }

      public void updateScreen(Graphics g) {
          try {
                  Dimension dim = this.getSize();
                  g.setColor(new Color(0, 0, 0));
                  g.fillRect(0 , 0 , dim.width , dim.height );
          }catch ( NullPointerException ex ) {
          }
      }

      public int convertToJavaType(int _value) throws IOException{
          int _retValue = 0 ;
          _retValue =  (_value >> 24 & 0x000000ff)
                | (_value >>  8 & 0x0000ff00)
                | (_value <<  8 & 0x00ff0000)
                | (_value << 24 & 0xff000000);

          return _retValue ;
      }
// frame counting ...
    class Timer extends Thread {
            int interval = 0 ;
            public Timer( int _millsec ) {
                    interval = _millsec ;
            }
            public void run(){
                    try {
                            while(true)
                            {
                                    frameCount();
                                    sleep(interval);
                            }
                    }catch(InterruptedException e) {
                    }
            }
    }
    public void frameCount(){
        System.out.println(count+" frames/secs");
        count = 0;
    }
}
