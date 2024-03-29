#include "SciNotes.hxx"
/* Generated by GIWS (version 2.0.1) with command:
giws --disable-return-size-array --output-dir D:\git\debug\similan\scilab\modules\scinotes\src\jni\ --throws-exception-on-error --description-file SciNotes.giws.xml 
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

namespace org_scilab_modules_scinotes {

                // Static declarations (if any)
                
// Returns the current env

JNIEnv * SciNotes::getCurrentEnv() {
JNIEnv * curEnv = NULL;
jint res=this->jvm->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
if (res != JNI_OK) {
throw GiwsException::JniException(getCurrentEnv());
}
return curEnv;
}
// Destructor

SciNotes::~SciNotes() {
JNIEnv * curEnv = NULL;
this->jvm->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);

curEnv->DeleteGlobalRef(this->instance);
curEnv->DeleteGlobalRef(this->instanceClass);
curEnv->DeleteGlobalRef(this->stringArrayClass);}
// Constructors
SciNotes::SciNotes(JavaVM * jvm_) {
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
voidscinotesID=NULL;
voidscinotesjstringjava_lang_StringID=NULL;
voidscinotesjstringjava_lang_Stringjintintjstringjava_lang_StringID=NULL;
voidscinotesjstringjava_lang_StringjobjectArray_java_lang_Stringjava_lang_StringID=NULL;
voidcloseSciNotesFromScilabID=NULL;


}

SciNotes::SciNotes(JavaVM * jvm_, jobject JObj) {
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
        voidscinotesID=NULL;
voidscinotesjstringjava_lang_StringID=NULL;
voidscinotesjstringjava_lang_Stringjintintjstringjava_lang_StringID=NULL;
voidscinotesjstringjava_lang_StringjobjectArray_java_lang_Stringjava_lang_StringID=NULL;
voidcloseSciNotesFromScilabID=NULL;


}

// Generic methods

void SciNotes::synchronize() {
if (getCurrentEnv()->MonitorEnter(instance) != JNI_OK) {
throw GiwsException::JniMonitorException(getCurrentEnv(), "SciNotes");
}
}

void SciNotes::endSynchronize() {
if ( getCurrentEnv()->MonitorExit(instance) != JNI_OK) {
throw GiwsException::JniMonitorException(getCurrentEnv(), "SciNotes");
}
}
// Method(s)

void SciNotes::scinotes (JavaVM * jvm_){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID voidscinotesID = curEnv->GetStaticMethodID(cls, "scinotes", "()V" ) ;
if (voidscinotesID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "scinotes");
}

                         curEnv->CallStaticVoidMethod(cls, voidscinotesID );
                        curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

void SciNotes::scinotes (JavaVM * jvm_, char const* fileName){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID voidscinotesjstringjava_lang_StringID = curEnv->GetStaticMethodID(cls, "scinotes", "(Ljava/lang/String;)V" ) ;
if (voidscinotesjstringjava_lang_StringID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "scinotes");
}

jstring fileName_ = curEnv->NewStringUTF( fileName );
if (fileName != NULL && fileName_ == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}


                         curEnv->CallStaticVoidMethod(cls, voidscinotesjstringjava_lang_StringID ,fileName_);
                        curEnv->DeleteLocalRef(fileName_);
curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

void SciNotes::scinotes (JavaVM * jvm_, char const* fileName, int lineNumber, char const* functionName){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID voidscinotesjstringjava_lang_Stringjintintjstringjava_lang_StringID = curEnv->GetStaticMethodID(cls, "scinotes", "(Ljava/lang/String;ILjava/lang/String;)V" ) ;
if (voidscinotesjstringjava_lang_Stringjintintjstringjava_lang_StringID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "scinotes");
}

jstring fileName_ = curEnv->NewStringUTF( fileName );
if (fileName != NULL && fileName_ == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}


jstring functionName_ = curEnv->NewStringUTF( functionName );
if (functionName != NULL && functionName_ == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}


                         curEnv->CallStaticVoidMethod(cls, voidscinotesjstringjava_lang_Stringjintintjstringjava_lang_StringID ,fileName_, lineNumber, functionName_);
                        curEnv->DeleteLocalRef(fileName_);
curEnv->DeleteLocalRef(functionName_);
curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

void SciNotes::scinotes (JavaVM * jvm_, char const* fileName, char const* const* option, int optionSize){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID voidscinotesjstringjava_lang_StringjobjectArray_java_lang_Stringjava_lang_StringID = curEnv->GetStaticMethodID(cls, "scinotes", "(Ljava/lang/String;[Ljava/lang/String;)V" ) ;
if (voidscinotesjstringjava_lang_StringjobjectArray_java_lang_Stringjava_lang_StringID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "scinotes");
}

jstring fileName_ = curEnv->NewStringUTF( fileName );
if (fileName != NULL && fileName_ == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}

jclass stringArrayClass = curEnv->FindClass("java/lang/String");

// create java array of strings.
jobjectArray option_ = curEnv->NewObjectArray( optionSize, stringArrayClass, NULL);
if (option_ == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}

// convert each char * to java strings and fill the java array.
for ( int i = 0; i < optionSize; i++)
{
jstring TempString = curEnv->NewStringUTF( option[i] );
if (TempString == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}

curEnv->SetObjectArrayElement( option_, i, TempString);

// avoid keeping reference on to many strings
curEnv->DeleteLocalRef(TempString);
}
                         curEnv->CallStaticVoidMethod(cls, voidscinotesjstringjava_lang_StringjobjectArray_java_lang_Stringjava_lang_StringID ,fileName_, option_);
                        curEnv->DeleteLocalRef(stringArrayClass);
curEnv->DeleteLocalRef(fileName_);
curEnv->DeleteLocalRef(option_);
curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

void SciNotes::closeSciNotesFromScilab (JavaVM * jvm_){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID voidcloseSciNotesFromScilabID = curEnv->GetStaticMethodID(cls, "closeSciNotesFromScilab", "()V" ) ;
if (voidcloseSciNotesFromScilabID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "closeSciNotesFromScilab");
}

                         curEnv->CallStaticVoidMethod(cls, voidcloseSciNotesFromScilabID );
                        curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

}
