/* 
JTrayiconWrap.c	   
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


#if defined(__GNUC__)
typedef long long __int64;	/*For gcc on Windows */
#endif
#include <jni.h>
#include <stdlib.h>
#include <string.h>

#include "trayicon.h"
#include "JTrayiconWrap.h"


#ifdef __cplusplus
extern "C"
{
#endif
typedef struct callbackdata {

JNIEnv *cb_jenv;
jobject cb_obj;
jmethodID cb_mid;
	
}CallBackData;

	

	void __callback (void * callbackdata, void *, int);

	void __callback (void * callbackdata, void* icon, int code)
	{
		CallBackData *data;
		jlong jicon=0;
		data = (CallBackData *) callbackdata;
		
		*(void **) &jicon = icon;
		
		if (data->cb_mid)
			(*data->cb_jenv)->CallVoidMethod (data->cb_jenv, data->cb_obj,
						      data->cb_mid, jicon, code);
		return;
	}
	
JNIEXPORT jlong JNICALL Java_de_asuhm_trayicon_JTrayiconWrap_tray_1icon_1new (JNIEnv * jenv,
								jobject obj,
								jstring jarg1,
								jstring jarg2)
	{
		jlong jresult = 0;
		jclass cls;
		char *arg1, *arg2;
		void *result;
				
		{
			arg1 = 0;
			if (jarg1)
			{
				arg1 = (char *) (*jenv)->
					GetStringUTFChars (jenv, jarg1, 0);
				if (!arg1)
					return 0;
			}
			arg2 = 0;
			if (jarg2)
			{
				arg2 = (char *) (*jenv)->
					GetStringUTFChars (jenv, jarg2, 0);
				if (!arg2)
					return 0;
			}
		}
		result = (void *) tray_icon_new ((const char *) arg1,
						 (const char *) arg2);

		*(void **) &jresult = result;
		{
			if (arg1)
				(*jenv)->ReleaseStringUTFChars (jenv, jarg1,
								arg1);
		}
		{
			if (arg2)
				(*jenv)->ReleaseStringUTFChars (jenv, jarg2,
								arg2);
		}
		
		return jresult;
	}

JNIEXPORT jlong JNICALL Java_de_asuhm_trayicon_JTrayiconWrap_tray_1icon_1new_1from_1data (JNIEnv * jenv,
								jobject obj,
								jstring jarg1,
								jbyteArray jarg2)
	{
		jlong jresult = 0;
		jclass cls;
		char *arg1, *arg2;
		void *result;
		jsize arraylength;		
		
		{
			arg1 = 0;
			if (jarg1)
			{
				arg1 = (char *) (*jenv)->
					GetStringUTFChars (jenv, jarg1, 0);
				if (!arg1)
					return 0;
			}
			arg2 = 0;
			if (jarg2)
			{
				arraylength =  (*jenv)->GetArrayLength (jenv,jarg2);
				
				arg2 = (char *) (*jenv)->
					GetByteArrayElements (jenv, jarg2, 0);
				if (!arg2)
					return 0;
			}
		}
		result = (void *) tray_icon_new_from_data ((const char*) arg1,
						 (const char  *) arg2, (unsigned long) arraylength);

		*(void **) &jresult = result;
		{
			if (arg1)
				(*jenv)->ReleaseStringUTFChars (jenv, jarg1,
								arg1);
		}
		{
			if (arg2)
				(*jenv)->ReleaseByteArrayElements (jenv, jarg2,
								arg2,0);
		}
		
		return jresult;
	}


	
		JNIEXPORT void JNICALL Java_de_asuhm_trayicon_JTrayiconWrap_tray_1icon_1remove
		(JNIEnv * jenv, jobject  obj, jlong jarg1)
	{
		void *arg1 = (void *) 0;

		arg1 = *(void **) &jarg1;
		tray_icon_remove(arg1);

		return;
	}
	
	
	JNIEXPORT jint JNICALL
		Java_de_asuhm_trayicon_JTrayiconWrap_tray_1icon_1send_1message (JNIEnv * jenv,
							  jobject  obj,
							  jlong jarg1,
							  jlong jarg2,
							  jstring jarg3,
							  jlong jarg4)
	{
		jint jresult = 0;
		void *arg1 = (void *) 0;
		unsigned long arg2;
		char *arg3;
		unsigned long arg4;
		int result;

		arg1 = *(void **) &jarg1;
		arg2 = (unsigned long) jarg2;
		{
			arg3 = 0;
			if (jarg3)
			{
				arg3 = (char *) (*jenv)->
					GetStringUTFChars (jenv, jarg3, 0);
				if (!arg3)
					return 0;
			}
		}
		arg4 = (unsigned long) jarg4;
		result = (int) tray_icon_send_message (arg1, arg2,
						       (const char *) arg3,
						       arg4);

		jresult = (jint) result;
		{
			if (arg3)
				(*jenv)->ReleaseStringUTFChars (jenv, jarg3,
								arg3);
		}
		return jresult;
	}


	JNIEXPORT void JNICALL
		Java_de_asuhm_trayicon_JTrayiconWrap_tray_1icon_1cancel_1message (JNIEnv * jenv,
							    jobject obj,
							    jlong jarg1,
							    jint jarg2)
	{

		void *arg1 = (void *) 0;
		int arg2;

		arg1 = *(void **) &jarg1;
		arg2 = (int) jarg2;
		tray_icon_cancel_message (arg1, arg2);
		return;
	}

	JNIEXPORT void JNICALL Java_de_asuhm_trayicon_JTrayiconWrap_tray_1icon_1set_1image
		(JNIEnv * jenv, jobject  obj, jlong jarg1, jstring jarg2)
	{
		void *arg1 = (void *) 0;
		char *arg2;

		arg1 = *(void **) &jarg1;
		{
			arg2 = 0;
			if (jarg2)
			{
				arg2 = (char *) (*jenv)->
					GetStringUTFChars (jenv, jarg2, 0);
				if (!arg2)
					return;
			}
		}
		tray_icon_set_image (arg1, (const char *) arg2);

		{
			if (arg2)
				(*jenv)->ReleaseStringUTFChars (jenv, jarg2,
								arg2);
		}
		return;
	}
	
	
	JNIEXPORT void JNICALL Java_de_asuhm_trayicon_JTrayiconWrap_tray_1icon_1set_1image_1from_1data
		(JNIEnv * jenv, jobject  obj, jlong jarg1, jbyteArray jarg2)
	{
		void *arg1 = (void *) 0;
		char *arg2;
		jsize arraylength;
		arg1 = *(void **) &jarg1;
		{
			
			arg2 = 0;
			if (jarg2)
			{
				arraylength = (*jenv)->GetArrayLength (jenv,jarg2);
				
				arg2 = (char *) (*jenv)->
					GetByteArrayElements (jenv, jarg2, 0);
				if (!arg2)
					return;
			}
		}	
			
		tray_icon_set_image_from_data (arg1, (const char *) arg2, (unsigned long) arraylength);

		{
			if (arg2)
				(*jenv)->ReleaseByteArrayElements (jenv, jarg2,
								arg2,0);
		}
		return;
	}



	JNIEXPORT void JNICALL Java_de_asuhm_trayicon_JTrayiconWrap_tray_1icon_1init
		(JNIEnv * jenv, jobject obj)
	{
		tray_icon_init ();
	}


	JNIEXPORT void JNICALL Java_de_asuhm_trayicon_JTrayiconWrap_tray_1icon_1run
		(JNIEnv * jenv, jobject obj)
	{
		jclass cls;
		CallBackData *callbackdata;

		
		callbackdata=malloc(sizeof(CallBackData));
		
		callbackdata->cb_jenv = jenv;
		callbackdata->cb_obj = obj;
		
		cls = (*jenv)->GetObjectClass (jenv, obj);
		
		callbackdata->cb_mid =
			(*jenv)->GetMethodID (jenv, cls, "callback", "(JI)V");
		
		tray_icon_run ((CB *) __callback, (void*) callbackdata);

		return;
	}


	JNIEXPORT void JNICALL Java_de_asuhm_trayicon_JTrayiconWrap_tray_1icon_1stop
		(JNIEnv * jenv, jobject  obj)
	{
		tray_icon_stop ();
	}

#ifdef __cplusplus
}
#endif
