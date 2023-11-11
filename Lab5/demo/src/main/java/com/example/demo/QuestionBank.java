package com.example.demo;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

public class QuestionBank {
    private List<Question> questions;

    public QuestionBank() {
        this.questions = new ArrayList<>();

        // Populate the question bank with sample questions.
        questions.add(new Question(UUID.randomUUID(), "Is your name Fling Fleep?", false));
        questions.add(new Question(UUID.randomUUID(), "Do you love burgers?", true));
        questions.add(new Question(UUID.randomUUID(), "Is Haris a plum?", true));
        questions.add(new Question(UUID.randomUUID(), "Does Jonathan stink?", true));
        questions.add(new Question(UUID.randomUUID(), "Is Jainil a stinky plum?", true));
        questions.add(new Question(UUID.randomUUID(), "Do you love Java?", true));
    }

    public List<Question> getQuestions() {
        return questions;
    }
}
