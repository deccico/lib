import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import java.io.*;

public class WebEyeApplet extends Applet {
  WebEyePanel panel;
  OptionPanel oPanel;
          Thread thread;

  boolean isStandalone = false;

    /**Initialize the applet*/
    public void init() {
        this.setLayout(null);
        oPanel = new OptionPanel(this);
        initAll();
   }

    public void initAll() {
        panel = new WebEyePanel();
        add(panel);
        panel.reshape(0, 0, 720, 486);
        panel.setVisible(true);
        thread = new Thread(panel);

        add(oPanel);
        oPanel.reshape(0, 486, 720, 50);
        oPanel.setVisible(true);
    }

    boolean bConnect = false;
    boolean bFirstStart = true;
    public void connect() {
        if( bConnect ) {
            stopPlay();
        }
        else {
            if( !bFirstStart ) {
                this.removeAll();
                initAll();
            }
            bFirstStart = false;
            play();
        }
        bConnect = bConnect ? false : true;
    }

    public void play() {
        if( bloadMode ) panel.setInputFile(file);
        else {
            String id, pw, ip;
            int port;
            id = oPanel.getUsername();
            pw = oPanel.getPassword();
            ip = oPanel.getIP();
            port = oPanel.getPort();

            panel.setAuthInfo(id, pw);
            panel.connect(ip, port);
        }
        thread.start();
    }

    public void stopPlay() {
        thread.stop();
        panel.stopAll();
        panel = null;
        bloadMode = false;
    }

    public void saveImageMode(File saveFile) {
        panel.setOutputFile(saveFile);
    }

    boolean bloadMode = false;
    File file;
    public void loadImageMode(File loadFile) {
        bloadMode = true;
        file = loadFile;
    }

    public void setImageResolution(int res) {
        panel.setImageResolution(res);
    }

    public void setGrayMode(boolean gmode) {
        panel.setGrayMode(gmode);
    }

    public void setVideoSource(int ch) {
        panel.setVideoSource((byte)ch);
    }


    /**Main method*/
    public static void main(String[] args) {
        WebEyeApplet applet = new WebEyeApplet();
        applet.isStandalone = true;
        Frame frame;
        frame = new Frame() {
          protected void processWindowEvent(WindowEvent e) {
            super.processWindowEvent(e);
            if (e.getID() == WindowEvent.WINDOW_CLOSING) {
              System.exit(0);
            }
          }
          public synchronized void setTitle(String title) {
            super.setTitle(title);
            enableEvents(AWTEvent.WINDOW_EVENT_MASK);
          }
        };
        frame.setTitle("Applet Frame");
        frame.add(applet);
        applet.init();
        applet.start();
        frame.setSize(730,576);
        Dimension d = Toolkit.getDefaultToolkit().getScreenSize();
        frame.setLocation((d.width - frame.getSize().width) / 2, (d.height - frame.getSize().height) / 2);
        frame.setVisible(true);
    }
}
