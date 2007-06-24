import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;

/**
 * Title:
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:
 * @author
 * @version 1.0
 */

public class OptionPanel extends Panel {
  WebEyeApplet applet;

  Button butConnect = new Button();

  public OptionPanel(WebEyeApplet applet) {
    try {
      this.applet = applet;
      jbInit();
    }
    catch(Exception ex) {
      ex.printStackTrace();
    }
  }
  void jbInit() throws Exception {
    butConnect.setBackground(Color.cyan);
    butConnect.setLabel("Play");
    butConnect.setBounds(new Rectangle(9, 9, 98, 37));
    butConnect.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        butConnect_actionPerformed(e);
      }
    });
    this.setBackground(Color.cyan);
    this.setLayout(null);
    label1.setFont(new java.awt.Font("Dialog", 3, 13));
    label1.setText("Resolution");
    label1.setBounds(new Rectangle(118, 17, 72, 20));
    chResolution.setBounds(new Rectangle(193, 16, 76, 22));
    chResolution.addItemListener(new java.awt.event.ItemListener() {
      public void itemStateChanged(ItemEvent e) {
        chResolution_itemStateChanged(e);
      }
    });
    ckGray.setBackground(Color.cyan);
    ckGray.setFont(new java.awt.Font("Dialog", 3, 13));
    ckGray.setLabel("Gray mode");
    ckGray.setBounds(new Rectangle(289, 14, 96, 26));
    ckGray.addItemListener(new java.awt.event.ItemListener() {
      public void itemStateChanged(ItemEvent e) {
        ckGray_itemStateChanged(e);
      }
    });
    chChannel.addItemListener(new java.awt.event.ItemListener() {
      public void itemStateChanged(ItemEvent e) {
        chChannel_itemStateChanged(e);
      }
    });
    chChannel.setBounds(new Rectangle(490, 16, 59, 22));
    label2.setFont(new java.awt.Font("Dialog", 3, 13));
    label2.setText("Video source");
    label2.setBounds(new Rectangle(396, 17, 90, 20));
    butSave.setBackground(Color.cyan);
    butSave.setLabel("save");
    butSave.setBounds(new Rectangle(562, 9, 64, 37));
    butSave.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        butSave_actionPerformed(e);
      }
    });
    butLoad.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        butLoad_actionPerformed(e);
      }
    });
    butLoad.setBounds(new Rectangle(637, 9, 64, 37));
    butLoad.setLabel("load");
    butLoad.setBackground(Color.cyan);
    this.add(butConnect, null);
    this.add(label1, null);
    this.add(chResolution, null);
    this.add(ckGray, null);
    this.add(label2, null);
    this.add(chChannel, null);
    this.add(butSave, null);
    this.add(butLoad, null);

    chResolution.add("90x60");
    chResolution.add("180x121");
    chResolution.add("360x243");
    chResolution.add("720x243");
    chResolution.add("720x486");

    chChannel.add("0");
    chChannel.add("1");
    chChannel.add("2");
    chChannel.add("3");
    chChannel.add("4");
  }

  boolean bStart = false;
  Label label1 = new Label();
  Choice chResolution = new Choice();
  Checkbox ckGray = new Checkbox();
  Choice chChannel = new Choice();
  Label label2 = new Label();
  Button butSave = new Button();

  String username, passwd, ip;
  int port;
  boolean nextTurnIsConnect = true;
  Button butLoad = new Button();
  void butConnect_actionPerformed(ActionEvent e) {
      if( nextTurnIsConnect ) {
          if( !applet.bloadMode ) {
              LoginDlg login = new LoginDlg(new Frame(), "Login Dialog", true);
              login.reshape(570, 461, 300, 230);
              login.show();
              username = login.strUsername;
              passwd = login.strPasswd;
              ip = login.strIP;
              port = login.port;
          }
          butConnect.setLabel("Stop");
          butLoad.setEnabled(false);
      }
      else {
          butConnect.setLabel("Play");
          butLoad.setEnabled(true);
      }
      applet.connect();
      nextTurnIsConnect = nextTurnIsConnect ? false : true;
  }

  public String getUsername() {
      return username;
  }
  public String getPassword() {
      return passwd;
  }
  public String getIP() {
      return ip;
  }
  public int getPort() {
      return port;
  }

  void chResolution_itemStateChanged(ItemEvent e) {
      applet.setImageResolution(chResolution.getSelectedIndex());
  }

  void ckGray_itemStateChanged(ItemEvent e) {
      applet.setGrayMode(ckGray.getState());
  }
  void chChannel_itemStateChanged(ItemEvent e) {
      applet.setVideoSource(chChannel.getSelectedIndex());
  }

  void butSave_actionPerformed(ActionEvent e){
      JFileChooser d = new JFileChooser();
      d.showSaveDialog(this);
      File file = d.getSelectedFile();
      applet.saveImageMode(file);
  }
  void butLoad_actionPerformed(ActionEvent e) {
      JFileChooser d = new JFileChooser();
      d.showOpenDialog(this);
      File file = d.getSelectedFile();
      applet.loadImageMode(file);
  }
}
