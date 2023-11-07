package com.example.demo;

import java.util.UUID;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import java.util.List;

@RestController
public class quizController {

    private QuestionBank questionBank = new QuestionBank();

    @GetMapping("/uuid")
    public MyUuid getUuid() {
        UUID uuid = UUID.randomUUID();
        return new MyUuid(uuid);
    }

    @PostMapping("/validatePass")
    @ResponseStatus(HttpStatus.OK)
    public ResponseEntity<Password> validatePassword(@RequestParam(value = "pwd") String pwd, @RequestParam(value = "username") String username, @RequestParam(value = "email") String email) {
        Password password = new Password(pwd, username, email);
        return new ResponseEntity<>(password, HttpStatus.OK);
    }
    
    @PostMapping("/emailCheck")
    @ResponseStatus(HttpStatus.OK)
    public ResponseEntity<String> checkEmail(@RequestParam(value = "email") String email) {
        return new ResponseEntity<>("Email is valid.", HttpStatus.OK);
    }

    @GetMapping("/questionBank")
    public ResponseEntity<List<Question> > getQuizQuestions() {
        List<Question> questions = questionBank.getQuestions();
        return new ResponseEntity<>(questions, HttpStatus.OK);
    }
}