/* 
JTrayicon.java	  
Copyright (C) 2004 Hendrik Muhs 
Java TrayIcon interface written by Hendrik Muhs   
 
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

package de.asuhm.trayicon;

import java.util.*;
import java.awt.*;


public class JTrayicon 
extends Thread

{
	private JTrayiconWrap tray;
	private long icon;
	private String name;
	private String image;
	private byte[] data;
	private JTrayiconListener listener;


	public JTrayicon (String name, String image, JTrayiconListener l)
	{
		this.name=name;
		this.image=image;
		this.listener=l;
		this.tray = JTrayiconWrap.getInstance();
	}
	
	public JTrayicon (String name, byte[] data, JTrayiconListener l)
	{
		this.name=name;
		this.data=data;
		this.listener=l;
		this.tray = JTrayiconWrap.getInstance();
	}
	
	public void show()
	{	
		if (this.image != null) 
	 		this.icon = this.tray.addicon(this.name,this.image,this.listener);
		else
			this.icon = this.tray.addicon(this.name,this.data,this.listener);
		
		if (!tray.isRunning())
		{
			tray.start();
		}
	}
	
	public void hide ()
	{	
		tray.remove(this.icon);
		
		if (tray.size() == 0)
			tray.quit();
	}
	

	public void setImage(String image)
	{
		this.image=image;
		this.data=null;
		tray.setImage(this.icon, image);
		
	}

	public void setImage(byte[] data)
	{
		this.image=null;
		this.data=data;
		tray.setImage(this.icon, data);
	}
}
