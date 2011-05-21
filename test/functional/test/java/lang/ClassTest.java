package test.java.lang;

import jvm.TestCase;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.util.Arrays;
import java.util.List;

public class ClassTest extends TestCase {
  public static void testGetAnnotation() {
    Tag tag = TaggedClass.class.getAnnotation(Tag.class);

    assertEquals(Byte.MAX_VALUE, tag.byteValue());
    assertEquals(Character.MAX_VALUE, tag.charValue());
    assertEquals(Short.MAX_VALUE, tag.shortValue());
    assertEquals(Integer.MAX_VALUE, tag.intValue());
    assertEquals(Long.MAX_VALUE, tag.longValue());
    assertEquals(Float.MAX_VALUE, tag.floatValue());
    assertEquals(Double.MAX_VALUE, tag.doubleValue());
    assertEquals("hello, world", tag.stringValue());
    assertEquals(Required.YES, tag.enumValue());
    assertEquals(Object.class, tag.classValue());
    assertNotNull(tag.annotationValue());

    assertArrayEquals(new byte[]     { Byte.MIN_VALUE,      Byte.MAX_VALUE      }, tag.byteArrayValue());
    assertArrayEquals(new char[]     { Character.MIN_VALUE, Character.MAX_VALUE }, tag.charArrayValue());
    assertArrayEquals(new short[]    { Short.MIN_VALUE,     Short.MAX_VALUE     }, tag.shortArrayValue());
    assertArrayEquals(new int[]      { Integer.MIN_VALUE,   Integer.MAX_VALUE   }, tag.intArrayValue());
    assertArrayEquals(new long[]     { Long.MIN_VALUE,      Long.MAX_VALUE      }, tag.longArrayValue());
    assertArrayEquals(new float[]    { Float.MIN_VALUE,     Float.MAX_VALUE     }, tag.floatArrayValue());
    assertArrayEquals(new double[]   { Double.MIN_VALUE,    Double.MAX_VALUE    }, tag.doubleArrayValue());
    assertArrayEquals(new String[]   { "hello, world",      "Hello, World!"     }, tag.stringArrayValue());
    assertArrayEquals(new Required[] { Required.YES,        Required.NO         }, tag.enumArrayValue());
    assertArrayEquals(new Class<?>[] { Integer.class,       Long.class          }, tag.classArrayValue());
    assertNotNull(tag.annotationArrayValue());
  }

  @Tag(
    byteValue        = Byte.MAX_VALUE,
    charValue        = Character.MAX_VALUE,
    shortValue       = Short.MAX_VALUE,
    intValue         = Integer.MAX_VALUE,
    longValue        = Long.MAX_VALUE,
    floatValue       = Float.MAX_VALUE,
    doubleValue      = Double.MAX_VALUE,
    stringValue      = "hello, world",
    enumValue        = Required.YES,
    classValue       = Object.class,
    annotationValue  = @Tag2,

    byteArrayValue   = { Byte.MIN_VALUE,      Byte.MAX_VALUE      },
    charArrayValue   = { Character.MIN_VALUE, Character.MAX_VALUE },
    shortArrayValue  = { Short.MIN_VALUE,     Short.MAX_VALUE     },
    intArrayValue    = { Integer.MIN_VALUE,   Integer.MAX_VALUE   },
    longArrayValue   = { Long.MIN_VALUE,      Long.MAX_VALUE      },
    floatArrayValue  = { Float.MIN_VALUE,     Float.MAX_VALUE     },
    doubleArrayValue = { Double.MIN_VALUE,    Double.MAX_VALUE    },
    stringArrayValue = { "hello, world",      "Hello, World!"     },
    enumArrayValue   = { Required.YES,        Required.NO         },
    classArrayValue  = { Integer.class,       Long.class          },
    annotationArrayValue = { @Tag2, @Tag2 }
  )
  public static class TaggedClass {
  }

  @Retention(RetentionPolicy.RUNTIME)
  public @interface Tag {
    byte       byteValue();
    char       charValue();
    short      shortValue();
    int        intValue();
    long       longValue();
    float      floatValue();
    double     doubleValue();
    String     stringValue();
    Required   enumValue();
    Class<?>   classValue();
    Tag2       annotationValue();

    byte[]     byteArrayValue();
    char[]     charArrayValue();
    short[]    shortArrayValue();
    int[]      intArrayValue();
    long[]     longArrayValue();
    float[]    floatArrayValue();
    double[]   doubleArrayValue();
    String[]   stringArrayValue();
    Required[] enumArrayValue();
    Class<?>[] classArrayValue();
    Tag2[]     annotationArrayValue();
  }

  public static enum Required { YES, NO }

  public @interface Tag2 { }

  public static void testGetClasses() {
     List<String> classNames = sort(map(Arrays.asList(Type.class.getClasses()), new Function<Class<?>, String>() {
     public String apply(Class<?> klass) {
       return klass.getName();
      }
    }));
    assertEquals(Arrays.asList("test.java.lang.ClassTest$Type$InnerInstance", "test.java.lang.ClassTest$Type$InnerStatic"), classNames);
  }

  public static void testGetDeclaredClasses() {
     List<String> classNames = sort(map(Arrays.asList(Type.class.getDeclaredClasses()), new Function<Class<?>, String>() {
     public String apply(Class<?> klass) {
       return klass.getName();
      }
    }));
    assertEquals(Arrays.asList("test.java.lang.ClassTest$Type$InnerInstance", "test.java.lang.ClassTest$Type$InnerInstancePrivate", "test.java.lang.ClassTest$Type$InnerStatic"), classNames);
  }

  public static class Type {
    public class InnerInstance { }
    public static class InnerStatic { }
    @SuppressWarnings("unused") private class InnerInstancePrivate { }
  }

  public static void testGetEnclosingClass() {
    assertNull(Object.class.getEnclosingClass());
    class LocalClass { }
    assertEquals(ClassTest.class, LocalClass.class.getEnclosingClass());
  }

  public static void testIsAnonymousClass() {
    assertFalse(int.class.isAnonymousClass());
    assertFalse(int[].class.isAnonymousClass());
    assertFalse(Object.class.isAnonymousClass());
    assertFalse(Object[].class.isAnonymousClass());
    assertTrue(new Object() { }.getClass().isAnonymousClass());
  }

  public static void testIsArray() {
    assertFalse(int.class.isArray());
    assertTrue(int[].class.isArray());
    assertFalse(Object.class.isArray());
    assertTrue(Object[].class.isArray());
    assertFalse(new Object() { }.getClass().isArray());
  }

  public static void testIsLocalClass() {
    assertFalse(int.class.isLocalClass());
    assertFalse(int[].class.isLocalClass());
    assertFalse(Object.class.isLocalClass());
    assertFalse(Object[].class.isLocalClass());
    assertFalse(new Object() { }.getClass().isLocalClass());
    class LocalClass { }
    assertTrue(LocalClass.class.isLocalClass());
  }

  public static void testIsMemberClass() {
    assertFalse(Object.class.isMemberClass());
    assertTrue(MemberClass.class.isMemberClass());
  }
  class MemberClass { }

  public static void testIsPrimitive() {
    assertTrue(int.class.isPrimitive());
    assertFalse(int[].class.isPrimitive());
    assertFalse(Object.class.isPrimitive());
    assertFalse(Object[].class.isPrimitive());
    assertFalse(new Object() { }.getClass().isPrimitive());
  }

  public static void main(String[] args) {
    testGetAnnotation();
    testGetClasses();
    testGetDeclaredClasses();
    testGetEnclosingClass();
    testIsAnonymousClass();
    testIsArray();
    testIsLocalClass();
    testIsMemberClass();
    testIsPrimitive();
  }
}
