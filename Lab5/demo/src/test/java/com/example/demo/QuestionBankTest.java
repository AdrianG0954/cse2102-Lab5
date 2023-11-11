package com.example.demo;

import org.junit.jupiter.api.Test;
import static org.junit.Assert.assertEquals;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import java.util.List;

@WebMvcTest(quizController.class)
public class QuestionBankTest {

    @Test
    public void testGetQuestions() {
        QuestionBank questionBank = new QuestionBank();
        List<Question> questions = questionBank.getQuestions();
        // checks if the question bank has 6 questions
        assertEquals(6, questions.size());
    }
}
