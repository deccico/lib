import java.awt.*;
import java.awt.event.*;

/**
 * Title:
 * Description:
 * Copyright:    Copyright (c) 2002
 * Company:
 * @author
 * @version 1.0
 */

public class LoginDlg extends Dialog {
  Panel panel1 = new Panel();
  Label label1 = new Label();
  Label label2 = new Label();
  Label label3 = new Label();
  Label label4 = new Label();
  TextField tfIPAddr = new TextField();
  TextField tfVideoPort = new TextField();
  TextField tfUserName = new TextField();
  TextField tfPasswd = new TextField();

  String strIP, strUsername, strPasswd;
  int port;
  Button butOK = new Button();

  public LoginDlg(Frame frame, String title, boolean modal) {
    super(frame, title, modal);
    enableEvents(AWTEvent.WINDOW_EVENT_MASK);
    try {
      jbInit();
      add(panel1);
      pack();
    }
    catch(Exception ex) {
      ex.printStackTrace();
    }
  }

  public LoginDlg(Frame frame) {
    this(frame, "", false);
  }

  public LoginDlg(Frame frame, boolean modal) {
    this(frame, "", modal);
  }

  public LoginDlg(Frame frame, String title) {
    this(frame, title, false);
  }
  void jbInit() throws Exception {
    label1.setFont(new java.awt.Font("Dialog", 3, 14));
    label1.setText("username");
    label1.setBounds(new Rectangle(38, 94, 83, 18));
    panel1.setLayout(null);
    label2.setBounds(new Rectangle(38, 123, 83, 18));
    label2.setText("password");
    label2.setFont(new java.awt.Font("Dialog", 3, 14));
    label3.setFont(new java.awt.Font("Dialog", 3, 14));
    label3.setText("IP Address");
    label3.setBounds(new Rectangle(38, 22, 83, 18));
    label4.setFont(new java.awt.Font("Dialog", 3, 14));
    label4.setText("Video port");
    label4.setBounds(new Rectangle(38, 50, 83, 18));
    tfIPAddr.setText("211.53.133.99");
    tfIPAddr.setBounds(new Rectangle(134, 20, 118, 22));
    tfVideoPort.setBounds(new Rectangle(134, 48, 118, 22));
    tfVideoPort.setText("8080");
    tfUserName.setText("guest");
    tfUserName.setBounds(new Rectangle(134, 92, 118, 22));
    tfPasswd.setBounds(new Rectangle(134, 121, 118, 22));
    tfPasswd.setEchoChar('*');
    tfPasswd.setText("guest");
    butOK.setBackground(Color.pink);
    butOK.setLabel("OK");
    butOK.setBounds(new Rectangle(113, 164, 75, 29));
    butOK.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        butOK_actionPerformed(e);
      }
    });
    panel1.setBackground(Color.pink);
    panel1.add(label3, null);
    panel1.add(label4, null);
    panel1.add(label1, null);
    panel1.add(label2, null);
    panel1.add(tfIPAddr, null);
    panel1.add(tfVideoPort, null);
    panel1.add(tfUserName, null);
    panel1.add(tfPasswd, null);
    panel1.add(butOK, null);
  }
  protected void processWindowEvent(WindowEvent e) {
    if (e.getID() == WindowEvent.WINDOW_CLOSING) {
      cancel();
    }
    super.processWindowEvent(e);
  }
  void cancel() {
    dispose();
  }

  void butOK_actionPerformed(ActionEvent e) {
      strIP = tfIPAddr.getText();
      port = Integer.parseInt(tfVideoPort.getText());
      strUsername = tfUserName.getText();
      strPasswd = tfPasswd.getText();
      dispose();
  }
}
