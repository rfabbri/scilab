#include "BrowseVar.hxx"
/* Generated by GIWS (version 2.0.1) with command:
giws --disable-return-size-array --output-dir D:\git\debug\similan\scilab\modules\ui_data\src\jni\ --throws-exception-on-error --description-file BrowseVar.giws.xml 
*/
/*

This is generated code.

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

                // Static declarations (if any)
                
// Returns the current env

JNIEnv * BrowseVar::getCurrentEnv() {
JNIEnv * curEnv = NULL;
jint res=this->jvm->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
if (res != JNI_OK) {
throw GiwsException::JniException(getCurrentEnv());
}
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
  throw GiwsException::JniClassNotFoundException(curEnv, this->className());
}

this->instanceClass = static_cast<jclass>(curEnv->NewGlobalRef(localClass));

/* localClass is not needed anymore */
curEnv->DeleteLocalRef(localClass);

if (this->instanceClass == NULL) {
throw GiwsException::JniObjectCreationException(curEnv, this->className());
}


constructObject = curEnv->GetMethodID( this->instanceClass, construct.c_str() , param.c_str() ) ;
if(constructObject == NULL){
throw GiwsException::JniObjectCreationException(curEnv, this->className());
}

localInstance = curEnv->NewObject( this->instanceClass, constructObject ) ;
if(localInstance == NULL){
throw GiwsException::JniObjectCreationException(curEnv, this->className());
}
 
this->instance = curEnv->NewGlobalRef(localInstance) ;
if(this->instance == NULL){
throw GiwsException::JniObjectCreationException(curEnv, this->className());
}
/* localInstance not needed anymore */
curEnv->DeleteLocalRef(localInstance);

                /* Methods ID set to NULL */
voidopenVariableBrowserID=NULL;
voidsetVariableBrowserDatajobjectArray_java_lang_Stringjava_lang_StringjintArray_intintjintArray_intintjintArray_intintjobjectArray_java_lang_Stringjava_lang_StringjobjectArray_java_lang_Stringjava_lang_StringjintArray_intintjintArray_intintjobjectArray_java_lang_Stringjava_lang_StringjbooleanArray_booleanbooleanID=NULL;
voidupdateVariableBrowserDataID=NULL;
jbooleanisVariableBrowserOpenedID=NULL;
voidcloseVariableBrowserID=NULL;


}

BrowseVar::BrowseVar(JavaVM * jvm_, jobject JObj) {
        jvm=jvm_;

        JNIEnv * curEnv = getCurrentEnv();

jclass localClass = curEnv->GetObjectClass(JObj);
        this->instanceClass = static_cast<jclass>(curEnv->NewGlobalRef(localClass));
        curEnv->DeleteLocalRef(localClass);

        if (this->instanceClass == NULL) {
throw GiwsException::JniObjectCreationException(curEnv, this->className());
        }

        this->instance = curEnv->NewGlobalRef(JObj) ;
        if(this->instance == NULL){
throw GiwsException::JniObjectCreationException(curEnv, this->className());
        }
        /* Methods ID set to NULL */
        voidopenVariableBrowserID=NULL;
voidsetVariableBrowserDatajobjectArray_java_lang_Stringjava_lang_StringjintArray_intintjintArray_intintjintArray_intintjobjectArray_java_lang_Stringjava_lang_StringjobjectArray_java_lang_Stringjava_lang_StringjintArray_intintjintArray_intintjobjectArray_java_lang_Stringjava_lang_StringjbooleanArray_booleanbooleanID=NULL;
voidupdateVariableBrowserDataID=NULL;
jbooleanisVariableBrowserOpenedID=NULL;
voidcloseVariableBrowserID=NULL;


}

// Generic methods

void BrowseVar::synchronize() {
if (getCurrentEnv()->MonitorEnter(instance) != JNI_OK) {
throw GiwsException::JniMonitorException(getCurrentEnv(), "BrowseVar");
}
}

void BrowseVar::endSynchronize() {
if ( getCurrentEnv()->MonitorExit(instance) != JNI_OK) {
throw GiwsException::JniMonitorException(getCurrentEnv(), "BrowseVar");
}
}
// Method(s)

void BrowseVar::openVariableBrowser (JavaVM * jvm_){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID voidopenVariableBrowserID = curEnv->GetStaticMethodID(cls, "openVariableBrowser", "()V" ) ;
if (voidopenVariableBrowserID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "openVariableBrowser");
}

                         curEnv->CallStaticVoidMethod(cls, voidopenVariableBrowserID );
                        curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

void BrowseVar::setVariableBrowserData (JavaVM * jvm_, char const* const* variableNames, int variableNamesSize, int const* variableBytes, int variableBytesSize, int const* variableTypes, int variableTypesSize, int const* variableIntegerTypes, int variableIntegerTypesSize, char const* const* variableListTypes, int variableListTypesSize, char const* const* variableSize, int variableSizeSize, int const* variableNbRows, int variableNbRowsSize, int const* variableNbCols, int variableNbColsSize, char const* const* variableVisibility, int variableVisibilitySize, bool const* variableFromUser, int variableFromUserSize){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID voidsetVariableBrowserDatajobjectArray_java_lang_Stringjava_lang_StringjintArray_intintjintArray_intintjintArray_intintjobjectArray_java_lang_Stringjava_lang_StringjobjectArray_java_lang_Stringjava_lang_StringjintArray_intintjintArray_intintjobjectArray_java_lang_Stringjava_lang_StringjbooleanArray_booleanbooleanID = curEnv->GetStaticMethodID(cls, "setVariableBrowserData", "([Ljava/lang/String;[I[I[I[Ljava/lang/String;[Ljava/lang/String;[I[I[Ljava/lang/String;[Z)V" ) ;
if (voidsetVariableBrowserDatajobjectArray_java_lang_Stringjava_lang_StringjintArray_intintjintArray_intintjintArray_intintjobjectArray_java_lang_Stringjava_lang_StringjobjectArray_java_lang_Stringjava_lang_StringjintArray_intintjintArray_intintjobjectArray_java_lang_Stringjava_lang_StringjbooleanArray_booleanbooleanID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "setVariableBrowserData");
}
jclass stringArrayClass = curEnv->FindClass("java/lang/String");

// create java array of strings.
jobjectArray variableNames_ = curEnv->NewObjectArray( variableNamesSize, stringArrayClass, NULL);
if (variableNames_ == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}

// convert each char * to java strings and fill the java array.
for ( int i = 0; i < variableNamesSize; i++)
{
jstring TempString = curEnv->NewStringUTF( variableNames[i] );
if (TempString == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}

curEnv->SetObjectArrayElement( variableNames_, i, TempString);

// avoid keeping reference on to many strings
curEnv->DeleteLocalRef(TempString);
}
jintArray variableBytes_ = curEnv->NewIntArray( variableBytesSize ) ;

if (variableBytes_ == NULL)
{
// check that allocation succeed
throw GiwsException::JniBadAllocException(curEnv);
}

curEnv->SetIntArrayRegion( variableBytes_, 0, variableBytesSize, (jint*)(variableBytes) ) ;


jintArray variableTypes_ = curEnv->NewIntArray( variableTypesSize ) ;

if (variableTypes_ == NULL)
{
// check that allocation succeed
throw GiwsException::JniBadAllocException(curEnv);
}

curEnv->SetIntArrayRegion( variableTypes_, 0, variableTypesSize, (jint*)(variableTypes) ) ;


jintArray variableIntegerTypes_ = curEnv->NewIntArray( variableIntegerTypesSize ) ;

if (variableIntegerTypes_ == NULL)
{
// check that allocation succeed
throw GiwsException::JniBadAllocException(curEnv);
}

curEnv->SetIntArrayRegion( variableIntegerTypes_, 0, variableIntegerTypesSize, (jint*)(variableIntegerTypes) ) ;



// create java array of strings.
jobjectArray variableListTypes_ = curEnv->NewObjectArray( variableListTypesSize, stringArrayClass, NULL);
if (variableListTypes_ == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}

// convert each char * to java strings and fill the java array.
for ( int i = 0; i < variableListTypesSize; i++)
{
jstring TempString = curEnv->NewStringUTF( variableListTypes[i] );
if (TempString == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}

curEnv->SetObjectArrayElement( variableListTypes_, i, TempString);

// avoid keeping reference on to many strings
curEnv->DeleteLocalRef(TempString);
}

// create java array of strings.
jobjectArray variableSize_ = curEnv->NewObjectArray( variableSizeSize, stringArrayClass, NULL);
if (variableSize_ == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}

// convert each char * to java strings and fill the java array.
for ( int i = 0; i < variableSizeSize; i++)
{
jstring TempString = curEnv->NewStringUTF( variableSize[i] );
if (TempString == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}

curEnv->SetObjectArrayElement( variableSize_, i, TempString);

// avoid keeping reference on to many strings
curEnv->DeleteLocalRef(TempString);
}
jintArray variableNbRows_ = curEnv->NewIntArray( variableNbRowsSize ) ;

if (variableNbRows_ == NULL)
{
// check that allocation succeed
throw GiwsException::JniBadAllocException(curEnv);
}

curEnv->SetIntArrayRegion( variableNbRows_, 0, variableNbRowsSize, (jint*)(variableNbRows) ) ;


jintArray variableNbCols_ = curEnv->NewIntArray( variableNbColsSize ) ;

if (variableNbCols_ == NULL)
{
// check that allocation succeed
throw GiwsException::JniBadAllocException(curEnv);
}

curEnv->SetIntArrayRegion( variableNbCols_, 0, variableNbColsSize, (jint*)(variableNbCols) ) ;



// create java array of strings.
jobjectArray variableVisibility_ = curEnv->NewObjectArray( variableVisibilitySize, stringArrayClass, NULL);
if (variableVisibility_ == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}

// convert each char * to java strings and fill the java array.
for ( int i = 0; i < variableVisibilitySize; i++)
{
jstring TempString = curEnv->NewStringUTF( variableVisibility[i] );
if (TempString == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}

curEnv->SetObjectArrayElement( variableVisibility_, i, TempString);

// avoid keeping reference on to many strings
curEnv->DeleteLocalRef(TempString);
}
jbooleanArray variableFromUser_ = curEnv->NewBooleanArray( variableFromUserSize ) ;
curEnv->SetBooleanArrayRegion( variableFromUser_, 0, variableFromUserSize, (jboolean*)variableFromUser ) ;

                         curEnv->CallStaticVoidMethod(cls, voidsetVariableBrowserDatajobjectArray_java_lang_Stringjava_lang_StringjintArray_intintjintArray_intintjintArray_intintjobjectArray_java_lang_Stringjava_lang_StringjobjectArray_java_lang_Stringjava_lang_StringjintArray_intintjintArray_intintjobjectArray_java_lang_Stringjava_lang_StringjbooleanArray_booleanbooleanID ,variableNames_, variableBytes_, variableTypes_, variableIntegerTypes_, variableListTypes_, variableSize_, variableNbRows_, variableNbCols_, variableVisibility_, variableFromUser_);
                        curEnv->DeleteLocalRef(stringArrayClass);
curEnv->DeleteLocalRef(variableNames_);
curEnv->DeleteLocalRef(variableBytes_);
curEnv->DeleteLocalRef(variableTypes_);
curEnv->DeleteLocalRef(variableIntegerTypes_);
curEnv->DeleteLocalRef(variableListTypes_);
curEnv->DeleteLocalRef(variableSize_);
curEnv->DeleteLocalRef(variableNbRows_);
curEnv->DeleteLocalRef(variableNbCols_);
curEnv->DeleteLocalRef(variableVisibility_);
curEnv->DeleteLocalRef(variableFromUser_);
curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

void BrowseVar::updateVariableBrowserData (JavaVM * jvm_){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID voidupdateVariableBrowserDataID = curEnv->GetStaticMethodID(cls, "updateVariableBrowserData", "()V" ) ;
if (voidupdateVariableBrowserDataID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "updateVariableBrowserData");
}

                         curEnv->CallStaticVoidMethod(cls, voidupdateVariableBrowserDataID );
                        curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

bool BrowseVar::isVariableBrowserOpened (JavaVM * jvm_){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID jbooleanisVariableBrowserOpenedID = curEnv->GetStaticMethodID(cls, "isVariableBrowserOpened", "()Z" ) ;
if (jbooleanisVariableBrowserOpenedID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "isVariableBrowserOpened");
}

                        jboolean res =  static_cast<jboolean>( curEnv->CallStaticBooleanMethod(cls, jbooleanisVariableBrowserOpenedID ));
                        curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
return (res == JNI_TRUE);

}

void BrowseVar::closeVariableBrowser (JavaVM * jvm_){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID voidcloseVariableBrowserID = curEnv->GetStaticMethodID(cls, "closeVariableBrowser", "()V" ) ;
if (voidcloseVariableBrowserID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "closeVariableBrowser");
}

                         curEnv->CallStaticVoidMethod(cls, voidcloseVariableBrowserID );
                        curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

}
