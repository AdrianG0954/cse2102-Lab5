package com.example.demo;

import org.junit.Test;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;

@WebMvcTest(quizController.class)
public class PasswordTest {
    @Test
    public void testValidPassword() {
        Password password = new Password("Dsjdks@1234", "user1", "user1@uconn.edu");
        assertTrue(password.isPasswordValid());
    }

    @Test
    public void testInvalidPassword() {
        Password password = new Password("notgood", "user1", "user1@uconn.edu");
        assertFalse(password.isPasswordValid());
    }

}