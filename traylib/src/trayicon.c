/* trayicon.c
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


#include <stdlib.h>
#include "eggtrayicon.h"
#include "gtk/gtk.h"
#include "trayicon.h"
#include <pthread.h>

typedef struct trayicon
{

	EggTrayIcon *icon;
	GtkWidget *eventbox;
	GtkWidget *image;
    GMainLoop *loop;

} TrayIcon;

CB *__cb;
void *__callbackdata;

int __initialized =0;
int __running = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

static void
tray_icon_pressed (GtkWidget * button, GdkEventButton * event,
		   TrayIcon * icon)
{
	
	__cb (__callbackdata, (void*) icon, event->button);
	return;
}


void *
tray_icon_new (const char *name, const char *image)
{
	TrayIcon *ticon;

	ticon = malloc (sizeof (TrayIcon));
	
	if (__running)
			gtk_main_quit();
		
	pthread_mutex_lock(&mutex);
	
	ticon->icon = egg_tray_icon_new ((const gchar *) name);
	ticon->eventbox = gtk_event_box_new ();

	g_signal_connect (ticon->eventbox, "button_press_event",
			  G_CALLBACK (tray_icon_pressed), ticon);

	gtk_container_add (GTK_CONTAINER (ticon->icon), ticon->eventbox);

	// tray icon image

	ticon->image = gtk_image_new_from_file ((const gchar *) image);

	gtk_container_add (GTK_CONTAINER (ticon->eventbox), ticon->image);
	
	gtk_widget_show_all (GTK_WIDGET (ticon->icon));
	
	pthread_mutex_unlock(&mutex);
	
	if (__running)
		pthread_cond_signal(&cond);
	
		
	return (void *) ticon;
}

void *
tray_icon_new_from_data (const char *name, const char *data, unsigned long size)
{
	TrayIcon *ticon;

	GdkPixbufLoader *loader;
	GdkPixbufAnimation *animation;
	gboolean rc;
		
	ticon = malloc (sizeof (TrayIcon));
	
	if (__running)
			gtk_main_quit();
		
	pthread_mutex_lock(&mutex);
	
	ticon->icon = egg_tray_icon_new ((const gchar *) name);
	ticon->eventbox = gtk_event_box_new ();

	g_signal_connect (ticon->eventbox, "button_press_event",
			  G_CALLBACK (tray_icon_pressed), ticon);

	gtk_container_add (GTK_CONTAINER (ticon->icon), ticon->eventbox);

	// tray icon image

	loader=gdk_pixbuf_loader_new();
	rc = gdk_pixbuf_loader_write (loader, (const guchar *)data, (gsize) size,NULL);
	
	gdk_pixbuf_loader_close (loader,NULL);
	
	if(rc)
	{
		// get animation
		animation=gdk_pixbuf_loader_get_animation(loader);
		
		ticon->image = gtk_image_new_from_animation (animation);
	} 
	
	
	gtk_container_add (GTK_CONTAINER (ticon->eventbox), ticon->image);
	
	gtk_widget_show_all (GTK_WIDGET (ticon->icon));
	
	pthread_mutex_unlock(&mutex);
	
	if (__running)
		pthread_cond_signal(&cond);
	
		
	return (void *) ticon;
}


void tray_icon_remove(void *icon)
{
	TrayIcon *ticon;
	if (icon == NULL)
		return;
	
	ticon = (TrayIcon *) icon;
	
	
	if (__running)
			gtk_main_quit();
	pthread_mutex_lock(&mutex);
	
	gtk_widget_hide (GTK_WIDGET (ticon->icon));
	gtk_widget_destroy (GTK_WIDGET (ticon->icon));
	
	pthread_mutex_unlock(&mutex);
	
	if (__running)
		pthread_cond_signal(&cond);
	
	free (ticon);
	
	return;
	
}


int
tray_icon_send_message (void *icon, unsigned long timeout,
			const char *message, unsigned long len)
{
	TrayIcon *ticon;
	if (icon == NULL)
		return -1;

	ticon = (TrayIcon *) icon;

	return egg_tray_icon_send_message (ticon->icon, timeout, message,
					   len);
}

void
tray_icon_cancel_message (void *icon, int id)
{
	TrayIcon *ticon;
	if (icon == NULL)
		return;
	ticon = (TrayIcon *) icon;
	egg_tray_icon_cancel_message (ticon->icon, id);
	return;
}

void
tray_icon_set_image (void *icon, const char *image)
{
	TrayIcon *ticon;
	if (icon == NULL)
		return;
	ticon = (TrayIcon *) icon;
	gtk_image_set_from_file (GTK_IMAGE (ticon->image),
				 (const gchar *) image);
}

void
tray_icon_set_image_from_data(void *icon, const char *data, unsigned long size)
{
	GdkPixbufLoader *loader;
	GdkPixbufAnimation *animation;
	gboolean rc;
	
	TrayIcon *ticon;
	if (icon == NULL)
		return;
	ticon = (TrayIcon *) icon;
	
	loader=gdk_pixbuf_loader_new();
	rc = gdk_pixbuf_loader_write (loader, (const guchar *)data, (gsize) size,NULL);
	
	gdk_pixbuf_loader_close (loader,NULL);
	
	if(rc)
	{
		// get animation
		animation=gdk_pixbuf_loader_get_animation(loader);
		
		gtk_image_set_from_animation (GTK_IMAGE (ticon->image),animation);
	} 
	
}

void
tray_icon_init ()
{
	if (!__initialized)
	{
		/* init threads */
		if (!g_thread_supported ())
		{
			
			g_thread_init (NULL);
			pthread_mutex_init (&mutex,NULL);
			pthread_cond_init(&cond, NULL);
		}
		
		gtk_init (NULL, NULL);
		__initialized=1;	
	}
	return;
}

void
tray_icon_run (CB * callback, void *callbackdata)
{

	__cb = callback;
	__callbackdata = callbackdata;

	
	pthread_mutex_lock(&mutex);
	__running=1;
	
	
	while (__running)
	{
		gtk_main();
		pthread_cond_wait(&cond, &mutex);
	}
	pthread_mutex_unlock(&mutex);
	
	return;
}



void
tray_icon_stop ()
{

	__running=0;

	gtk_main_quit ();
	
	pthread_cond_signal(&cond);
	
}
