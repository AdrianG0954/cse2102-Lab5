package com.example.demo;

import java.util.UUID;
// import java.util.List;

public class Question {
    private UUID uuid;
    private String question;
    private boolean answer;

    public Question(UUID uuid, String question, boolean answer) {
        this.uuid = uuid;
        this.question = question;
        this.answer = answer;
    }

    public UUID getUuid() {
        return uuid;
    }

    public void setUuid(UUID uuid) {
        this.uuid = uuid;
    }

    public String getQuestion() {
        return question;
    }

    public void setQuestion(String question) {
        this.question = question;
    }

    public boolean getAnswer() {
        return answer;
    }

    public void setAnswer(boolean answer) {
        this.answer = answer;
    }
}