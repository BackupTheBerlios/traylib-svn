/* trayicon.h
 * Copyright (C) 2004 Hendrik Muhs
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

 
typedef void (CB)(void*, void*, int);

 
void* tray_icon_new(const char * name, const char *image);
void * tray_icon_new_from_data (const char *name, const char *data, unsigned long size);



void tray_icon_remove(void *icon);

int tray_icon_send_message   (void * icon,unsigned long         timeout,
					   const char  *message,
					   unsigned long len);
					   
void tray_icon_cancel_message (void * icon,int id);

void tray_icon_set_image(void * icon,const char *image);
void tray_icon_set_image_from_data(void *icon, const char *data, unsigned long size);

void tray_icon_init();
void tray_icon_run(CB * callback, void * callbackdata);
void tray_icon_stop();
