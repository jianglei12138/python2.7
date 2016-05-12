#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Python.h"
#include <android/log.h>

JNIEXPORT jstring JNICALL Java_com_example_pythontest_MainActivity_getUrl
  (JNIEnv *env, jclass jthis)
{
    //set path and home,pay attention --> python3.5.zip
    //putenv("PYTHONPATH=/data/data/com.example.pythontest/files/python27.zip");
    //putenv("PYTHONHOME=/data/data/com.example.pythontest/files");

    Py_Initialize();
    if ( !Py_IsInitialized()){
        __android_log_print(ANDROID_LOG_INFO, "JNIEnv","Py_Initialize failed!!\n"); 
        return (*env)->NewStringUTF(env,"");
    }
    PyErr_Print();
    //add current path to search pythonforandroid.py file
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("reload(sys)");
    PyRun_SimpleString("sys.setdefaultencoding('utf-8')");
    PyRun_SimpleString("sys.path.append('/data/data/com.example.pythontest/files')"); //this mean pythonforandroid.py under /data/data/com.example.pythontest/files
     PyErr_Print();
    PyObject *pModule;
    PyObject *ytFunction;
    PyObject *ytArgs;
    PyObject *ytRetValue;
    PyObject *streamLink;
    //import module which name pythonforandroid under /data/data/com.example.pythontest/files
    pModule = PyImport_ImportModule("youtube");
    if(!pModule){
        PyErr_Print();
        __android_log_print(ANDROID_LOG_INFO, "JNIEnv","import python module failed!!\n");
        return (*env)->NewStringUTF(env,"");
    }

    ytFunction = PyObject_GetAttrString(pModule, "get_stream");

    if(!ytFunction){
        __android_log_print(ANDROID_LOG_INFO, "JNIEnv","get yt function failed!!!\n");
        return (*env)->NewStringUTF(env,"");
    }
    ytArgs = PyTuple_New(1);
    PyTuple_SetItem(ytArgs, 0, Py_BuildValue("s", "http://v.youku.com/v_show/id_XOTYwNzg5OTg4.html?from=s1.8-1-1.2"));
    ytRetValue = PyObject_CallObject(ytFunction, ytArgs);
    //for youku ---> entries
    streamLink = PyDict_GetItemString(ytRetValue, "entries");
    PyObject* representation = PyObject_Repr(streamLink);
    const char* s = PyString_AsString(representation);
    __android_log_print(ANDROID_LOG_INFO, "JNIEnv","pRetValue %s", s);

    Py_DECREF(representation);
    Py_DECREF(pModule);
    Py_DECREF(ytFunction);
    Py_DECREF(ytArgs);
    Py_DECREF(ytRetValue);
    Py_Finalize();

    return (*env)->NewStringUTF(env,s);
}