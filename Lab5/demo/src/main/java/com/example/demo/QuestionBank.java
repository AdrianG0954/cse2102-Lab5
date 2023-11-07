package com.example.demo;

import java.util.UUID;
import java.util.ArrayList;
import java.util.List;

public class QuestionBank {
    private List<Question> questions;

    public QuestionBank() {
        this.questions = new ArrayList<>();
        // Populate the question bank with sample questions.
        Question question1 = new Question(UUID.randomUUID(), "Is your name Fling Fleep?", false);
        Question question2 = new Question(UUID.randomUUID(), "Do you love burgers?", true);
        Question question3 = new Question(UUID.randomUUID(), "is haris a plum?", true);
        Question question4 = new Question(UUID.randomUUID(), "Does jonathan stink?", true);
        Question question5 = new Question(UUID.randomUUID(), "is jainil a stinky plum?", true);
        Question question6 = new Question(UUID.randomUUID(), "Do you love Java?", true);
        
        questions.add(question1);
        questions.add(question2);
        questions.add(question3);
        questions.add(question4);
        questions.add(question5);
        questions.add(question6);
    }

    public List<Question> getQuestions() {
        return questions;
    }
}