#include "BrowseVar.hxx"
/* Generated by GIWS (version 1.1.0) */
/*

Copyright 2007-2008 INRIA

Author : Sylvestre Ledru & others

This software is a computer program whose purpose is to hide the complexity
of accessing Java objects/methods from C++ code.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
*/

namespace org_scilab_modules_ui_data {

// Returns the current env

JNIEnv * BrowseVar::getCurrentEnv() {
JNIEnv * curEnv = NULL;
this->jvm->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
return curEnv;
}
// Destructor

BrowseVar::~BrowseVar() {
JNIEnv * curEnv = NULL;
this->jvm->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);

curEnv->DeleteGlobalRef(this->instance);
curEnv->DeleteGlobalRef(this->instanceClass);
curEnv->DeleteGlobalRef(this->stringArrayClass);}
// Constructors

BrowseVar::BrowseVar(JavaVM * jvm_) {
jmethodID constructObject = NULL ;
jobject localInstance ;
jclass localClass ;
const std::string construct="<init>";
const std::string param="()V";
jvm=jvm_;

JNIEnv * curEnv = getCurrentEnv();

localClass = curEnv->FindClass( this->className().c_str() ) ;
if (localClass == NULL) {
std::cerr << "Could not get the Class " << this->className() <<  std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
}

this->instanceClass = static_cast<jclass>(curEnv->NewGlobalRef(localClass));

/* localClass is not needed anymore */
curEnv->DeleteLocalRef(localClass);

if (this->instanceClass == NULL) {
std::cerr << "Could not create a Global Ref of " << this->className() <<  std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
}


constructObject = curEnv->GetMethodID( this->instanceClass, construct.c_str() , param.c_str() ) ;
if(constructObject == NULL){
std::cerr << "Could not retrieve the constructor of the class " << this->className() << " with the profile : " << construct << param << std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
}

localInstance = curEnv->NewObject( this->instanceClass, constructObject ) ;
if(localInstance == NULL){
std::cerr << "Could not instantiate the object " << this->className() << " with the constructor : " << construct << param << std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
}
 
this->instance = curEnv->NewGlobalRef(localInstance) ;
if(this->instance == NULL){
std::cerr << "Could not create a new global ref of " << this->className() << std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
}
/* localInstance not needed anymore */
curEnv->DeleteLocalRef(localInstance);

                /* Methods ID set to NULL */
voidopenVariableBrowserID=NULL; 
voidopenVariableBrowserjobjectArray_ID=NULL; 
voidopenVariableBrowserjobjectArray_jobjectArray_jobjectArray_jobjectArray_jobjectArray_ID=NULL; 
voidcloseVariableBrowserID=NULL; 


}

BrowseVar::BrowseVar(JavaVM * jvm_, jobject JObj) {
        jvm=jvm_;

        JNIEnv * curEnv = getCurrentEnv();

jclass localClass = curEnv->GetObjectClass(JObj);
        this->instanceClass = static_cast<jclass>(curEnv->NewGlobalRef(localClass));
        curEnv->DeleteLocalRef(localClass);

        if (this->instanceClass == NULL) {

std::cerr << "Could not create a Global Ref of " << this->className() <<  std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
        }

        this->instance = curEnv->NewGlobalRef(JObj) ;
        if(this->instance == NULL){

std::cerr << "Could not create a new global ref of " << this->className() << std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
        }
        /* Methods ID set to NULL */
        voidopenVariableBrowserID=NULL; 
voidopenVariableBrowserjobjectArray_ID=NULL; 
voidopenVariableBrowserjobjectArray_jobjectArray_jobjectArray_jobjectArray_jobjectArray_ID=NULL; 
voidcloseVariableBrowserID=NULL; 


}

// Generic methods

void BrowseVar::synchronize() {
if (getCurrentEnv()->MonitorEnter(instance) != JNI_OK) {
std::cerr << "Fail to enter monitor." << std::endl;
exit(EXIT_FAILURE);

}
}

void BrowseVar::endSynchronize() {
if ( getCurrentEnv()->MonitorExit(instance) != JNI_OK) {

std::cerr << "Fail to exit monitor." << std::endl;
exit(EXIT_FAILURE);
}
}
// Method(s)

void BrowseVar::openVariableBrowser (JavaVM * jvm_){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID voidopenVariableBrowserID = curEnv->GetStaticMethodID(cls, "openVariableBrowser", "()V" ) ;
if (voidopenVariableBrowserID == NULL) {
std::cerr << "Could not access to the method " << "openVariableBrowser" << std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
}

                         curEnv->CallStaticVoidMethod(cls, voidopenVariableBrowserID );if (curEnv->ExceptionCheck()) {
curEnv->ExceptionDescribe() ;
}

}

void BrowseVar::openVariableBrowser (JavaVM * jvm_, char ** columnNames, int columnNamesSize){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID voidopenVariableBrowserjobjectArray_ID = curEnv->GetStaticMethodID(cls, "openVariableBrowser", "([Ljava/lang/String;)V" ) ;
if (voidopenVariableBrowserjobjectArray_ID == NULL) {
std::cerr << "Could not access to the method " << "openVariableBrowser" << std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
}
jclass stringArrayClass = curEnv->FindClass("java/lang/String");

// create java array of strings.
jobjectArray columnNames_ = curEnv->NewObjectArray( columnNamesSize, stringArrayClass, NULL);
if (columnNames_ == NULL)
{
std::cerr << "Could not allocate Java string array, memory full." << std::endl;
exit(EXIT_FAILURE);
}

// convert each char * to java strings and fill the java array.
for ( int i = 0; i < columnNamesSize; i++)
{
jstring TempString = curEnv->NewStringUTF( columnNames[i] );
if (TempString == NULL)
{
std::cerr << "Could not convert C string to Java UTF string, memory full." << std::endl;
exit(EXIT_FAILURE);
}

curEnv->SetObjectArrayElement( columnNames_, i, TempString);

// avoid keeping reference on to many strings
curEnv->DeleteLocalRef(TempString);
}
                         curEnv->CallStaticVoidMethod(cls, voidopenVariableBrowserjobjectArray_ID ,columnNames_);curEnv->DeleteLocalRef(stringArrayClass);
curEnv->DeleteLocalRef(columnNames_);
if (curEnv->ExceptionCheck()) {
curEnv->ExceptionDescribe() ;
}

}

void BrowseVar::openVariableBrowser (JavaVM * jvm_, char ** columnNames, int columnNamesSize, char ** variableNames, int variableNamesSize, int* variableBytes, int variableBytesSize, int* variableTypes, int variableTypesSize, char ** variableVisibility, int variableVisibilitySize){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID voidopenVariableBrowserjobjectArray_jobjectArray_jobjectArray_jobjectArray_jobjectArray_ID = curEnv->GetStaticMethodID(cls, "openVariableBrowser", "([Ljava/lang/String;[Ljava/lang/String;[I[I[Ljava/lang/String;)V" ) ;
if (voidopenVariableBrowserjobjectArray_jobjectArray_jobjectArray_jobjectArray_jobjectArray_ID == NULL) {
std::cerr << "Could not access to the method " << "openVariableBrowser" << std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
}
jclass stringArrayClass = curEnv->FindClass("java/lang/String");

// create java array of strings.
jobjectArray columnNames_ = curEnv->NewObjectArray( columnNamesSize, stringArrayClass, NULL);
if (columnNames_ == NULL)
{
std::cerr << "Could not allocate Java string array, memory full." << std::endl;
exit(EXIT_FAILURE);
}

// convert each char * to java strings and fill the java array.
for ( int i = 0; i < columnNamesSize; i++)
{
jstring TempString = curEnv->NewStringUTF( columnNames[i] );
if (TempString == NULL)
{
std::cerr << "Could not convert C string to Java UTF string, memory full." << std::endl;
exit(EXIT_FAILURE);
}

curEnv->SetObjectArrayElement( columnNames_, i, TempString);

// avoid keeping reference on to many strings
curEnv->DeleteLocalRef(TempString);
}

// create java array of strings.
jobjectArray variableNames_ = curEnv->NewObjectArray( variableNamesSize, stringArrayClass, NULL);
if (variableNames_ == NULL)
{
std::cerr << "Could not allocate Java string array, memory full." << std::endl;
exit(EXIT_FAILURE);
}

// convert each char * to java strings and fill the java array.
for ( int i = 0; i < variableNamesSize; i++)
{
jstring TempString = curEnv->NewStringUTF( variableNames[i] );
if (TempString == NULL)
{
std::cerr << "Could not convert C string to Java UTF string, memory full." << std::endl;
exit(EXIT_FAILURE);
}

curEnv->SetObjectArrayElement( variableNames_, i, TempString);

// avoid keeping reference on to many strings
curEnv->DeleteLocalRef(TempString);
}
jintArray variableBytes_ = curEnv->NewIntArray( variableBytesSize ) ;

curEnv->SetIntArrayRegion( variableBytes_, 0, variableBytesSize, (jint*)(variableBytes) ) ;


jintArray variableTypes_ = curEnv->NewIntArray( variableTypesSize ) ;

curEnv->SetIntArrayRegion( variableTypes_, 0, variableTypesSize, (jint*)(variableTypes) ) ;



// create java array of strings.
jobjectArray variableVisibility_ = curEnv->NewObjectArray( variableVisibilitySize, stringArrayClass, NULL);
if (variableVisibility_ == NULL)
{
std::cerr << "Could not allocate Java string array, memory full." << std::endl;
exit(EXIT_FAILURE);
}

// convert each char * to java strings and fill the java array.
for ( int i = 0; i < variableVisibilitySize; i++)
{
jstring TempString = curEnv->NewStringUTF( variableVisibility[i] );
if (TempString == NULL)
{
std::cerr << "Could not convert C string to Java UTF string, memory full." << std::endl;
exit(EXIT_FAILURE);
}

curEnv->SetObjectArrayElement( variableVisibility_, i, TempString);

// avoid keeping reference on to many strings
curEnv->DeleteLocalRef(TempString);
}
                         curEnv->CallStaticVoidMethod(cls, voidopenVariableBrowserjobjectArray_jobjectArray_jobjectArray_jobjectArray_jobjectArray_ID ,columnNames_, variableNames_, variableBytes_, variableTypes_, variableVisibility_);curEnv->DeleteLocalRef(stringArrayClass);
curEnv->DeleteLocalRef(columnNames_);
curEnv->DeleteLocalRef(variableNames_);
curEnv->DeleteLocalRef(variableBytes_);
curEnv->DeleteLocalRef(variableTypes_);
curEnv->DeleteLocalRef(variableVisibility_);
if (curEnv->ExceptionCheck()) {
curEnv->ExceptionDescribe() ;
}

}

void BrowseVar::closeVariableBrowser (JavaVM * jvm_){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID voidcloseVariableBrowserID = curEnv->GetStaticMethodID(cls, "closeVariableBrowser", "()V" ) ;
if (voidcloseVariableBrowserID == NULL) {
std::cerr << "Could not access to the method " << "closeVariableBrowser" << std::endl;
curEnv->ExceptionDescribe();
exit(EXIT_FAILURE);
}

                         curEnv->CallStaticVoidMethod(cls, voidcloseVariableBrowserID );if (curEnv->ExceptionCheck()) {
curEnv->ExceptionDescribe() ;
}

}

}