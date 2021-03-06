/*
 * Copyright (C) 2006  Pekka Enberg
 *
 * This file is released under the 2-clause BSD license. Please refer to the
 * file LICENSE for details.
 */
package jvm;

/**
 * @author Pekka Enberg
 */
public class LoadConstantsTest extends TestCase {
    public static void testAconstNull() {
        assertNull(aconst_null());
    }

    public static Object aconst_null() {
        return null;
    }

    public static void testIconst() {
        assertEquals(-1, iconst_m1());
        assertEquals( 0, iconst_0());
        assertEquals( 1, iconst_1());
        assertEquals( 2, iconst_2());
        assertEquals( 3, iconst_3());
        assertEquals( 4, iconst_4());
        assertEquals( 5, iconst_5());
    }

    public static int iconst_m1() {
        return -1;
    }

    public static int iconst_0() {
        return 0;
    }

    public static int iconst_1() {
        return 1;
    }

    public static int iconst_2() {
        return 2;
    }

    public static int iconst_3() {
        return 3;
    }

    public static int iconst_4() {
        return 4;
    }

    public static int iconst_5() {
        return 5;
    }

    public static void testLdcStringConstant() {
        assertEquals(4, "HELO".length());
    } 

    public static void main(String[] args) {
        testAconstNull();
        testIconst();
        testLdcStringConstant();
    }
}
