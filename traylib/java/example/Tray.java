/* 
tray.java	                                                  
example program written by Hendrik Muhs   
Copyright (C) 2004 Hendrik Muhs 

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in the Software without 
restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:
 
The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
*/



import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
  
import java.io.*;
  
import de.asuhm.trayicon.*;
  
  public class Tray extends JFrame {
  
   /**
    * Konstruktor
    */
	
   public Tray() throws FileNotFoundException, IOException{
     super(Tray.class.getName());
  
     getContentPane().setLayout(new BorderLayout());
  
       
     JButton button = new JButton("Quit");

	 button.addActionListener(new ActionListener() {
     public void actionPerformed(ActionEvent e) {
  		System.exit(0);
       }
     });
  
     getContentPane().add(button, BorderLayout.CENTER);
  		
  
     setSize(200, 100);
    
	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
     setVisible(true);
	 
	 TrayListener listener =new TrayListener();
	 JTrayicon trayicon = new JTrayicon ("MyTrayIcon","smiley.png",listener);
	
	 
	 // test for set_image_from_data
	 //RandomAccessFile file;
	 //byte[] buffer;
	 
	 //file = new RandomAccessFile("smiley_animated.gif", "r");
	 //buffer= new byte[(int)file.length()];
	 //file.read(buffer);
	 
	 //JTrayicon trayicon = new JTrayicon ("MyTrayIcon",buffer,listener);
	 
	 trayicon.show();
	 
	 //trayicon.set_image(buffer);
	 
   }
  
  
   /**
    * Start-Methode, Aufruf über
    * java de.dpunkt.swing.simpleapp.SimpleApp
    */
   public static void main(String[] argv) throws Exception{
     new Tray();
   }
  }
