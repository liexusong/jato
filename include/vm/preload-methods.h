PRELOAD_METHOD(vm_java_lang_Boolean, "<init>", "(Z)V", vm_java_lang_Boolean_init)
PRELOAD_METHOD(vm_java_lang_Boolean, "booleanValue", "()Z", vm_java_lang_Boolean_booleanValue)
PRELOAD_METHOD(vm_java_lang_Boolean, "valueOf", "(Z)Ljava/lang/Boolean;", vm_java_lang_Boolean_valueOf)
PRELOAD_METHOD(vm_java_lang_Byte, "<init>", "(B)V", vm_java_lang_Byte_init)
PRELOAD_METHOD(vm_java_lang_Byte, "valueOf", "(B)Ljava/lang/Byte;", vm_java_lang_Byte_valueOf)
PRELOAD_METHOD(vm_java_lang_Character, "<init>", "(C)V", vm_java_lang_Character_init)
PRELOAD_METHOD(vm_java_lang_Character, "charValue", "()C", vm_java_lang_Character_charValue)
PRELOAD_METHOD(vm_java_lang_Character, "valueOf", "(C)Ljava/lang/Character;", vm_java_lang_Character_valueOf)
PRELOAD_METHOD(vm_java_lang_Class, "<init>", "(Ljava/lang/Object;Ljava/security/ProtectionDomain;)V", vm_java_lang_Class_init)
PRELOAD_METHOD(vm_java_lang_ClassLoader, "getSystemClassLoader", "()Ljava/lang/ClassLoader;", vm_java_lang_ClassLoader_getSystemClassLoader)
PRELOAD_METHOD(vm_java_lang_ClassLoader, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;", vm_java_lang_ClassLoader_loadClass)
PRELOAD_METHOD(vm_java_lang_Double, "<init>", "(D)V", vm_java_lang_Double_init)
PRELOAD_METHOD(vm_java_lang_Double, "valueOf", "(D)Ljava/lang/Double;", vm_java_lang_Double_valueOf)
PRELOAD_METHOD(vm_java_lang_Enum, "valueOf", "(Ljava/lang/Class;Ljava/lang/String;)Ljava/lang/Enum;", vm_java_lang_Enum_valueOf)
PRELOAD_METHOD(vm_java_lang_Float, "<init>", "(F)V", vm_java_lang_Float_init)
PRELOAD_METHOD(vm_java_lang_Float, "valueOf", "(F)Ljava/lang/Float;", vm_java_lang_Float_valueOf)
PRELOAD_METHOD(vm_java_lang_InheritableThreadLocal, "newChildThread", "(Ljava/lang/Thread;)V", vm_java_lang_InheritableThreadLocal_newChildThread)
PRELOAD_METHOD(vm_java_lang_Integer, "<init>", "(I)V", vm_java_lang_Integer_init)
PRELOAD_METHOD(vm_java_lang_Integer, "valueOf", "(I)Ljava/lang/Integer;", vm_java_lang_Integer_valueOf)
PRELOAD_METHOD(vm_java_lang_Long, "<init>", "(J)V", vm_java_lang_Long_init)
PRELOAD_METHOD(vm_java_lang_Long, "valueOf", "(J)Ljava/lang/Long;", vm_java_lang_Long_valueOf)
PRELOAD_METHOD(vm_java_lang_Number, "doubleValue", "()D", vm_java_lang_Number_doubleValue)
PRELOAD_METHOD(vm_java_lang_Number, "floatValue", "()F", vm_java_lang_Number_floatValue)
PRELOAD_METHOD(vm_java_lang_Number, "intValue", "()I", vm_java_lang_Number_intValue)
PRELOAD_METHOD(vm_java_lang_Number, "longValue", "()J", vm_java_lang_Number_longValue)
PRELOAD_METHOD(vm_java_lang_Short, "<init>", "(S)V", vm_java_lang_Short_init)
PRELOAD_METHOD(vm_java_lang_Short, "valueOf", "(S)Ljava/lang/Short;", vm_java_lang_Short_valueOf)
PRELOAD_METHOD(vm_java_lang_StackTraceElement, "<init>", "(Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;Z)V", vm_java_lang_StackTraceElement_init)
PRELOAD_METHOD(vm_java_lang_String, "length", "()I", vm_java_lang_String_length)
PRELOAD_METHOD(vm_java_lang_System, "exit", "(I)V", vm_java_lang_System_exit)
PRELOAD_METHOD(vm_java_lang_Thread, "<init>", "(Ljava/lang/VMThread;Ljava/lang/String;IZ)V", vm_java_lang_Thread_init)
PRELOAD_METHOD(vm_java_lang_Thread, "getName", "()Ljava/lang/String;", vm_java_lang_Thread_getName)
PRELOAD_METHOD(vm_java_lang_Thread, "isDaemon", "()Z", vm_java_lang_Thread_isDaemon)
PRELOAD_METHOD(vm_java_lang_ThreadGroup, "<init>", "()V", vm_java_lang_ThreadGroup_init)
PRELOAD_METHOD(vm_java_lang_ThreadGroup, "addThread", "(Ljava/lang/Thread;)V", vm_java_lang_ThreadGroup_addThread)
PRELOAD_METHOD(vm_java_lang_Throwable, "getCause", "()Ljava/lang/Throwable;", vm_java_lang_Throwable_getCause)
PRELOAD_METHOD(vm_java_lang_Throwable, "getStackTrace", "()[Ljava/lang/StackTraceElement;", vm_java_lang_Throwable_getStackTrace)
PRELOAD_METHOD(vm_java_lang_Throwable, "initCause", "(Ljava/lang/Throwable;)Ljava/lang/Throwable;", vm_java_lang_Throwable_initCause)
PRELOAD_METHOD(vm_java_lang_Throwable, "setStackTrace", "([Ljava/lang/StackTraceElement;)V", vm_java_lang_Throwable_setStackTrace)
PRELOAD_METHOD(vm_java_lang_Throwable, "stackTraceString", "()Ljava/lang/String;", vm_java_lang_Throwable_stackTraceString)
PRELOAD_METHOD(vm_java_lang_VMString, "intern", "(Ljava/lang/String;)Ljava/lang/String;", vm_java_lang_VMString_intern)
PRELOAD_METHOD(vm_java_lang_VMThread, "<init>", "(Ljava/lang/Thread;)V", vm_java_lang_VMThread_init)
PRELOAD_METHOD(vm_java_lang_VMThread, "run", "()V", vm_java_lang_VMThread_run)
PRELOAD_METHOD(vm_java_lang_ref_Reference, "clear", "()V", vm_java_lang_ref_Reference_clear)
PRELOAD_METHOD(vm_java_lang_ref_Reference, "enqueue", "()Z", vm_java_lang_ref_Reference_enqueue)
PRELOAD_METHOD(vm_java_nio_DirectByteBufferImpl_ReadWrite, "<init>", "(Ljava/lang/Object;Lgnu/classpath/Pointer;III)V", vm_java_nio_DirectByteBufferImpl_ReadWrite_init)
PRELOAD_METHOD(vm_java_util_HashMap, "<init>", "()V", vm_java_util_HashMap_init)
PRELOAD_METHOD(vm_java_util_HashMap, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;", vm_java_util_HashMap_put)
PRELOAD_METHOD(vm_java_util_Properties, "setProperty", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;", vm_java_util_Properties_setProperty)
PRELOAD_METHOD(vm_sun_reflect_annotation_AnnotationInvocationHandler, "create", "(Ljava/lang/Class;Ljava/util/Map;)Ljava/lang/annotation/Annotation;", vm_sun_reflect_annotation_AnnotationInvocationHandler_create)
