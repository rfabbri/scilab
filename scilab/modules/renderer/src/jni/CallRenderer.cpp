#include "CallRenderer.hxx"
/* Generated by GIWS (version 2.0.1) with command:
giws --disable-return-size-array --output-dir D:\git\debug\similan\scilab\modules\renderer\src\jni\ --throws-exception-on-error --description-file renderer.giws.xml 
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

namespace org_scilab_modules_renderer {

                // Static declarations (if any)
                
// Returns the current env

JNIEnv * CallRenderer::getCurrentEnv() {
JNIEnv * curEnv = NULL;
jint res=this->jvm->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
if (res != JNI_OK) {
throw GiwsException::JniException(getCurrentEnv());
}
return curEnv;
}
// Destructor

CallRenderer::~CallRenderer() {
JNIEnv * curEnv = NULL;
this->jvm->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);

curEnv->DeleteGlobalRef(this->instance);
curEnv->DeleteGlobalRef(this->instanceClass);
}
// Constructors
CallRenderer::CallRenderer(JavaVM * jvm_) {
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
voidstartInteractiveZoomjstringjava_lang_StringID=NULL;
jdoubleArray_clickRubberBoxjstringjava_lang_StringjdoubleArray_doubledoubleID=NULL;
jdoubleArray_dragRubberBoxjstringjava_lang_StringID=NULL;
voidupdateTextBoundsjstringjava_lang_StringID=NULL;
voidupdateSubwinScalejstringjava_lang_StringID=NULL;
jdoubleArray_get2dViewCoordinatesjstringjava_lang_StringjdoubleArray_doubledoubleID=NULL;
jdoubleArray_getPixelFrom2dViewCoordinatesjstringjava_lang_StringjdoubleArray_doubledoubleID=NULL;
jdoubleArray_get2dViewFromPixelCoordinatesjstringjava_lang_StringjdoubleArray_doubledoubleID=NULL;
jdoubleArray_getViewingAreajstringjava_lang_StringID=NULL;


}

CallRenderer::CallRenderer(JavaVM * jvm_, jobject JObj) {
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
        voidstartInteractiveZoomjstringjava_lang_StringID=NULL;
jdoubleArray_clickRubberBoxjstringjava_lang_StringjdoubleArray_doubledoubleID=NULL;
jdoubleArray_dragRubberBoxjstringjava_lang_StringID=NULL;
voidupdateTextBoundsjstringjava_lang_StringID=NULL;
voidupdateSubwinScalejstringjava_lang_StringID=NULL;
jdoubleArray_get2dViewCoordinatesjstringjava_lang_StringjdoubleArray_doubledoubleID=NULL;
jdoubleArray_getPixelFrom2dViewCoordinatesjstringjava_lang_StringjdoubleArray_doubledoubleID=NULL;
jdoubleArray_get2dViewFromPixelCoordinatesjstringjava_lang_StringjdoubleArray_doubledoubleID=NULL;
jdoubleArray_getViewingAreajstringjava_lang_StringID=NULL;


}

// Generic methods

void CallRenderer::synchronize() {
if (getCurrentEnv()->MonitorEnter(instance) != JNI_OK) {
throw GiwsException::JniMonitorException(getCurrentEnv(), "CallRenderer");
}
}

void CallRenderer::endSynchronize() {
if ( getCurrentEnv()->MonitorExit(instance) != JNI_OK) {
throw GiwsException::JniMonitorException(getCurrentEnv(), "CallRenderer");
}
}
// Method(s)

void CallRenderer::startInteractiveZoom (JavaVM * jvm_, char const* id){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID voidstartInteractiveZoomjstringjava_lang_StringID = curEnv->GetStaticMethodID(cls, "startInteractiveZoom", "(Ljava/lang/String;)V" ) ;
if (voidstartInteractiveZoomjstringjava_lang_StringID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "startInteractiveZoom");
}

jstring id_ = curEnv->NewStringUTF( id );
if (id != NULL && id_ == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}


                         curEnv->CallStaticVoidMethod(cls, voidstartInteractiveZoomjstringjava_lang_StringID ,id_);
                        curEnv->DeleteLocalRef(id_);
curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

double* CallRenderer::clickRubberBox (JavaVM * jvm_, char const* id, double const* startRectangle, int startRectangleSize){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID jdoubleArray_clickRubberBoxjstringjava_lang_StringjdoubleArray_doubledoubleID = curEnv->GetStaticMethodID(cls, "clickRubberBox", "(Ljava/lang/String;[D)[D" ) ;
if (jdoubleArray_clickRubberBoxjstringjava_lang_StringjdoubleArray_doubledoubleID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "clickRubberBox");
}

jstring id_ = curEnv->NewStringUTF( id );
if (id != NULL && id_ == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}


jdoubleArray startRectangle_ = curEnv->NewDoubleArray( startRectangleSize ) ;

if (startRectangle_ == NULL)
{
// check that allocation succeed
throw GiwsException::JniBadAllocException(curEnv);
}

curEnv->SetDoubleArrayRegion( startRectangle_, 0, startRectangleSize, (jdouble*)(startRectangle) ) ;


                        jdoubleArray res =  static_cast<jdoubleArray>( curEnv->CallStaticObjectMethod(cls, jdoubleArray_clickRubberBoxjstringjava_lang_StringjdoubleArray_doubledoubleID ,id_, startRectangle_));
                        if (res == NULL) { return NULL; }
                        if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}int lenRow;
 lenRow = curEnv->GetArrayLength(res);
jboolean isCopy = JNI_FALSE;

/* GetPrimitiveArrayCritical is faster than getXXXArrayElements */
jdouble *resultsArray = static_cast<jdouble *>(curEnv->GetPrimitiveArrayCritical(res, &isCopy));
double* myArray= new double[ lenRow];

for (jsize i = 0; i <  lenRow; i++){
myArray[i]=resultsArray[i];
}
curEnv->ReleasePrimitiveArrayCritical(res, resultsArray, JNI_ABORT);

                        curEnv->DeleteLocalRef(res);
curEnv->DeleteLocalRef(id_);
curEnv->DeleteLocalRef(startRectangle_);
curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
delete[] myArray;
                                throw GiwsException::JniCallMethodException(curEnv);
}
return myArray;

}

double* CallRenderer::dragRubberBox (JavaVM * jvm_, char const* id){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID jdoubleArray_dragRubberBoxjstringjava_lang_StringID = curEnv->GetStaticMethodID(cls, "dragRubberBox", "(Ljava/lang/String;)[D" ) ;
if (jdoubleArray_dragRubberBoxjstringjava_lang_StringID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "dragRubberBox");
}

jstring id_ = curEnv->NewStringUTF( id );
if (id != NULL && id_ == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}


                        jdoubleArray res =  static_cast<jdoubleArray>( curEnv->CallStaticObjectMethod(cls, jdoubleArray_dragRubberBoxjstringjava_lang_StringID ,id_));
                        if (res == NULL) { return NULL; }
                        if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}int lenRow;
 lenRow = curEnv->GetArrayLength(res);
jboolean isCopy = JNI_FALSE;

/* GetPrimitiveArrayCritical is faster than getXXXArrayElements */
jdouble *resultsArray = static_cast<jdouble *>(curEnv->GetPrimitiveArrayCritical(res, &isCopy));
double* myArray= new double[ lenRow];

for (jsize i = 0; i <  lenRow; i++){
myArray[i]=resultsArray[i];
}
curEnv->ReleasePrimitiveArrayCritical(res, resultsArray, JNI_ABORT);

                        curEnv->DeleteLocalRef(res);
curEnv->DeleteLocalRef(id_);
curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
delete[] myArray;
                                throw GiwsException::JniCallMethodException(curEnv);
}
return myArray;

}

void CallRenderer::updateTextBounds (JavaVM * jvm_, char const* id){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID voidupdateTextBoundsjstringjava_lang_StringID = curEnv->GetStaticMethodID(cls, "updateTextBounds", "(Ljava/lang/String;)V" ) ;
if (voidupdateTextBoundsjstringjava_lang_StringID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "updateTextBounds");
}

jstring id_ = curEnv->NewStringUTF( id );
if (id != NULL && id_ == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}


                         curEnv->CallStaticVoidMethod(cls, voidupdateTextBoundsjstringjava_lang_StringID ,id_);
                        curEnv->DeleteLocalRef(id_);
curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

void CallRenderer::updateSubwinScale (JavaVM * jvm_, char const* id){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID voidupdateSubwinScalejstringjava_lang_StringID = curEnv->GetStaticMethodID(cls, "updateSubwinScale", "(Ljava/lang/String;)V" ) ;
if (voidupdateSubwinScalejstringjava_lang_StringID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "updateSubwinScale");
}

jstring id_ = curEnv->NewStringUTF( id );
if (id != NULL && id_ == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}


                         curEnv->CallStaticVoidMethod(cls, voidupdateSubwinScalejstringjava_lang_StringID ,id_);
                        curEnv->DeleteLocalRef(id_);
curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}
}

double* CallRenderer::get2dViewCoordinates (JavaVM * jvm_, char const* id, double const* coords, int coordsSize){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID jdoubleArray_get2dViewCoordinatesjstringjava_lang_StringjdoubleArray_doubledoubleID = curEnv->GetStaticMethodID(cls, "get2dViewCoordinates", "(Ljava/lang/String;[D)[D" ) ;
if (jdoubleArray_get2dViewCoordinatesjstringjava_lang_StringjdoubleArray_doubledoubleID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "get2dViewCoordinates");
}

jstring id_ = curEnv->NewStringUTF( id );
if (id != NULL && id_ == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}


jdoubleArray coords_ = curEnv->NewDoubleArray( coordsSize ) ;

if (coords_ == NULL)
{
// check that allocation succeed
throw GiwsException::JniBadAllocException(curEnv);
}

curEnv->SetDoubleArrayRegion( coords_, 0, coordsSize, (jdouble*)(coords) ) ;


                        jdoubleArray res =  static_cast<jdoubleArray>( curEnv->CallStaticObjectMethod(cls, jdoubleArray_get2dViewCoordinatesjstringjava_lang_StringjdoubleArray_doubledoubleID ,id_, coords_));
                        if (res == NULL) { return NULL; }
                        if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}int lenRow;
 lenRow = curEnv->GetArrayLength(res);
jboolean isCopy = JNI_FALSE;

/* GetPrimitiveArrayCritical is faster than getXXXArrayElements */
jdouble *resultsArray = static_cast<jdouble *>(curEnv->GetPrimitiveArrayCritical(res, &isCopy));
double* myArray= new double[ lenRow];

for (jsize i = 0; i <  lenRow; i++){
myArray[i]=resultsArray[i];
}
curEnv->ReleasePrimitiveArrayCritical(res, resultsArray, JNI_ABORT);

                        curEnv->DeleteLocalRef(res);
curEnv->DeleteLocalRef(id_);
curEnv->DeleteLocalRef(coords_);
curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
delete[] myArray;
                                throw GiwsException::JniCallMethodException(curEnv);
}
return myArray;

}

double* CallRenderer::getPixelFrom2dViewCoordinates (JavaVM * jvm_, char const* id, double const* coords, int coordsSize){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID jdoubleArray_getPixelFrom2dViewCoordinatesjstringjava_lang_StringjdoubleArray_doubledoubleID = curEnv->GetStaticMethodID(cls, "getPixelFrom2dViewCoordinates", "(Ljava/lang/String;[D)[D" ) ;
if (jdoubleArray_getPixelFrom2dViewCoordinatesjstringjava_lang_StringjdoubleArray_doubledoubleID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "getPixelFrom2dViewCoordinates");
}

jstring id_ = curEnv->NewStringUTF( id );
if (id != NULL && id_ == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}


jdoubleArray coords_ = curEnv->NewDoubleArray( coordsSize ) ;

if (coords_ == NULL)
{
// check that allocation succeed
throw GiwsException::JniBadAllocException(curEnv);
}

curEnv->SetDoubleArrayRegion( coords_, 0, coordsSize, (jdouble*)(coords) ) ;


                        jdoubleArray res =  static_cast<jdoubleArray>( curEnv->CallStaticObjectMethod(cls, jdoubleArray_getPixelFrom2dViewCoordinatesjstringjava_lang_StringjdoubleArray_doubledoubleID ,id_, coords_));
                        if (res == NULL) { return NULL; }
                        if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}int lenRow;
 lenRow = curEnv->GetArrayLength(res);
jboolean isCopy = JNI_FALSE;

/* GetPrimitiveArrayCritical is faster than getXXXArrayElements */
jdouble *resultsArray = static_cast<jdouble *>(curEnv->GetPrimitiveArrayCritical(res, &isCopy));
double* myArray= new double[ lenRow];

for (jsize i = 0; i <  lenRow; i++){
myArray[i]=resultsArray[i];
}
curEnv->ReleasePrimitiveArrayCritical(res, resultsArray, JNI_ABORT);

                        curEnv->DeleteLocalRef(res);
curEnv->DeleteLocalRef(id_);
curEnv->DeleteLocalRef(coords_);
curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
delete[] myArray;
                                throw GiwsException::JniCallMethodException(curEnv);
}
return myArray;

}

double* CallRenderer::get2dViewFromPixelCoordinates (JavaVM * jvm_, char const* id, double const* coords, int coordsSize){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID jdoubleArray_get2dViewFromPixelCoordinatesjstringjava_lang_StringjdoubleArray_doubledoubleID = curEnv->GetStaticMethodID(cls, "get2dViewFromPixelCoordinates", "(Ljava/lang/String;[D)[D" ) ;
if (jdoubleArray_get2dViewFromPixelCoordinatesjstringjava_lang_StringjdoubleArray_doubledoubleID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "get2dViewFromPixelCoordinates");
}

jstring id_ = curEnv->NewStringUTF( id );
if (id != NULL && id_ == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}


jdoubleArray coords_ = curEnv->NewDoubleArray( coordsSize ) ;

if (coords_ == NULL)
{
// check that allocation succeed
throw GiwsException::JniBadAllocException(curEnv);
}

curEnv->SetDoubleArrayRegion( coords_, 0, coordsSize, (jdouble*)(coords) ) ;


                        jdoubleArray res =  static_cast<jdoubleArray>( curEnv->CallStaticObjectMethod(cls, jdoubleArray_get2dViewFromPixelCoordinatesjstringjava_lang_StringjdoubleArray_doubledoubleID ,id_, coords_));
                        if (res == NULL) { return NULL; }
                        if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}int lenRow;
 lenRow = curEnv->GetArrayLength(res);
jboolean isCopy = JNI_FALSE;

/* GetPrimitiveArrayCritical is faster than getXXXArrayElements */
jdouble *resultsArray = static_cast<jdouble *>(curEnv->GetPrimitiveArrayCritical(res, &isCopy));
double* myArray= new double[ lenRow];

for (jsize i = 0; i <  lenRow; i++){
myArray[i]=resultsArray[i];
}
curEnv->ReleasePrimitiveArrayCritical(res, resultsArray, JNI_ABORT);

                        curEnv->DeleteLocalRef(res);
curEnv->DeleteLocalRef(id_);
curEnv->DeleteLocalRef(coords_);
curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
delete[] myArray;
                                throw GiwsException::JniCallMethodException(curEnv);
}
return myArray;

}

double* CallRenderer::getViewingArea (JavaVM * jvm_, char const* id){

JNIEnv * curEnv = NULL;
jvm_->AttachCurrentThread(reinterpret_cast<void **>(&curEnv), NULL);
jclass cls = curEnv->FindClass( className().c_str() );

jmethodID jdoubleArray_getViewingAreajstringjava_lang_StringID = curEnv->GetStaticMethodID(cls, "getViewingArea", "(Ljava/lang/String;)[D" ) ;
if (jdoubleArray_getViewingAreajstringjava_lang_StringID == NULL) {
throw GiwsException::JniMethodNotFoundException(curEnv, "getViewingArea");
}

jstring id_ = curEnv->NewStringUTF( id );
if (id != NULL && id_ == NULL)
{
throw GiwsException::JniBadAllocException(curEnv);
}


                        jdoubleArray res =  static_cast<jdoubleArray>( curEnv->CallStaticObjectMethod(cls, jdoubleArray_getViewingAreajstringjava_lang_StringID ,id_));
                        if (res == NULL) { return NULL; }
                        if (curEnv->ExceptionCheck()) {
throw GiwsException::JniCallMethodException(curEnv);
}int lenRow;
 lenRow = curEnv->GetArrayLength(res);
jboolean isCopy = JNI_FALSE;

/* GetPrimitiveArrayCritical is faster than getXXXArrayElements */
jdouble *resultsArray = static_cast<jdouble *>(curEnv->GetPrimitiveArrayCritical(res, &isCopy));
double* myArray= new double[ lenRow];

for (jsize i = 0; i <  lenRow; i++){
myArray[i]=resultsArray[i];
}
curEnv->ReleasePrimitiveArrayCritical(res, resultsArray, JNI_ABORT);

                        curEnv->DeleteLocalRef(res);
curEnv->DeleteLocalRef(id_);
curEnv->DeleteLocalRef(cls);
if (curEnv->ExceptionCheck()) {
delete[] myArray;
                                throw GiwsException::JniCallMethodException(curEnv);
}
return myArray;

}

}
