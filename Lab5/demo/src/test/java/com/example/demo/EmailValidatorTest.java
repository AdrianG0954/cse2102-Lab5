package com.example.demo;
import org.junit.jupiter.api.Test;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;

@WebMvcTest(quizController.class)
public class EmailValidatorTest {

    @Test
    public void testValidEmail() {
        assertTrue(EmailValidator.isEmailValid("adrian.garcia@uconn.edu"));
    }
    @Test
    public void testValidEmail2() {
        assertTrue(EmailValidator.isEmailValid("adrian123@gmail.com"));
    }
    @Test
    public void testInvalidEmail() {
        assertFalse(EmailValidator.isEmailValid("i am not a valid email"));
    }

    @Test
    public void testInvalidEmail2() {
        assertFalse(EmailValidator.isEmailValid("helloEveryone"));
    }
}
