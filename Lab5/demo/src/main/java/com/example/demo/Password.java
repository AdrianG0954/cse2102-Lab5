package com.example.demo;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Password {
    private String pwd;
    private String username;
    private String email;

    public Password(String pwd, String username, String email) {
        this.pwd = pwd;
        this.username = username;
        this.email = email;
    }

    public String getPwd() {
        return pwd;
    }

    public boolean isPasswordValid() {
        // Check if password has a minimum length of 8 characters.
        if (pwd.length() < 8) {
            return false;
        }

        // Check if password contains at least one uppercase letter, one lowercase letter, and one digit.
        Pattern pattern = Pattern.compile("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).+$");
        Matcher matcher = pattern.matcher(pwd);
        if (!matcher.matches()) {
            return false;
        }

        // Check for password entropy
        double entropy = pwd.length() * Math.log(94) / Math.log(2);
        if (entropy < 40) {
            return false;
        }

        // Check if password does not contain the user's name or email address.
        if (pwd.toLowerCase().contains(username.toLowerCase()) || pwd.toLowerCase().contains(email.toLowerCase())) {
            return false;
        }

        return true;
    }
}