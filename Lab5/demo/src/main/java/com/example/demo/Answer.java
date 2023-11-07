package com.example.demo;

public class Answer {
    private String option;
    private String answer;

    public Answer(String option, String answer) {
        this.option = option;
        this.answer = answer;
    }

    public String getAnswer() {
        return answer;
    }

    public void setAnswer(String answer) {
        this.answer = answer;
    }

    public String getOption() {
        return option;
    }

    public void setOption(String option) {
        this.option = option;
    }
}
