/* 
JTrayiconWrap.java	
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

public class JTrayiconWrap 
extends Thread

{
	private Hashtable icons;
	private boolean running =false;

	static {
		String tpath = System.getProperty("lib.trayicon.path");
		
		if (tpath == null)
		{
			System.load(tpath);	
		}
		else
		{
    		System.loadLibrary("trayicon");
		}
			
  	}
	
	private static JTrayiconWrap me = null;
	public static JTrayiconWrap getInstance()
	{
	   if (me == null)
	   		me = new JTrayiconWrap();
		return me;
	}
	
	private JTrayiconWrap ()
	{
		this.icons = new Hashtable();
		this.tray_icon_init();
	}
	
	public long addicon (String name, String image, JTrayiconListener l)
	{	
		long trayicon=tray_icon_new(name,image);
		icons.put(new Long(trayicon), l);
		return trayicon;
	}
	
	public void remove (long icon)
	{	
		this.tray_icon_remove(icon);
	}
	

	public void run()
	{
		if (!running)
		{
			running = true;
			this.tray_icon_run();
		}
	}

	public void quit()
	{
		if (running)
		{
			running=false;
			this.tray_icon_stop();		
		}
	}
	
	public boolean isRunning()
	{
		if (running)
			return true;
		else
			return false;
	}
	
	public int size()
	{
		return this.icons.size();
	}
	
	public void set_image(long icon, String image)
	{
		this.tray_icon_set_image(icon, image);
		
	}

  private native long tray_icon_new(String name, String image);
  private native void tray_icon_remove(long icon);
  private native int tray_icon_send_message(long icon, long timeout, String message, long len);
  private native void tray_icon_cancel_message(long icon,int id);
  private native void tray_icon_set_image(long icon,String image);
  private native void tray_icon_init();
  private native void tray_icon_run();
  private native void tray_icon_stop();
  
  private void callback (long icon, int code)
  {
    JTrayiconListener listener;
  	Long key = new Long (icon);
	if (this.icons.containsKey(key))
	{
		listener = (JTrayiconListener) this.icons.get(key);
	
		Runnable eventThread = new EventThread(listener, code );

    	EventQueue.invokeLater( eventThread );
	} 
	
	
  }
  protected static class EventThread implements Runnable
    {
        private int code;
        private JTrayiconListener listener;
		
        public EventThread(JTrayiconListener listener, int code )
        {
            this.code = code;
			this.listener=listener;
        }

        public void run()
        {            
			JTrayiconEvent event = new JTrayiconEvent(this,code);
			event.button=code;

			this.listener.buttonClicked(event);
        }
    }
  
}
