package app.view;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.DecimalFormat;

public class TestCPU {
    private JPanel testCPU;
    private JTextArea factorizareTextArea;
    private JTextArea factorialTextArea;
    private JTextArea fibonacciTextArea;
    private JTextArea digitsOfPITextArea;
    private JButton backButton;
    private JLabel ratingLabel;
    private JTextArea fastFourierTextArea;
    private JTextArea matrixMultiplicationTextArea;
    Double digitsOfPITime;
    Double fibonacciTime;
    Double factorialTime;
    Double factorizareTime;
    Double fastFourierTransformTime;
    Double matrixMultiplicationTime;
    Double overallRating;
    private static final double WEIGHT_DIGITS_OF_PI = 1.0;
    private static final double WEIGHT_FIBONACCI = 1.3;
    private static final double WEIGHT_FACTORIAL = 2.0;
    private static final double WEIGHT_FACTORIZARE = 1.8;
    private static final double WEIGHT_FAST_FOURIER = 2.0;
    private static final double WEIGHT_MATRIX_MULTIPLICATION = 1.7;
    private static final DecimalFormat df = new DecimalFormat("0.00");

    public TestCPU(JPanel panel) {

        FillTextArea(0);
        digitsOfPITextArea.append(digitsOfPITime.toString() + "s");
        FillTextArea(1);
        fibonacciTextArea.append(fibonacciTime.toString() + "s");
        FillTextArea(2);
        factorialTextArea.append(factorialTime.toString() + "s");
        FillTextArea(3);
        factorizareTextArea.append(factorizareTime.toString() + "s");
        FillTextArea(4);
        fastFourierTextArea.append(fastFourierTransformTime.toString() + "s");
        FillTextArea(5);
        matrixMultiplicationTextArea.append(matrixMultiplicationTime.toString() + "s");

        overallRating = calculateOverallRating();
        ratingLabel.setText("Rating: " + df.format(overallRating * 200));

        GUI.changePanel(testCPU, "CPU Test Page");

        backButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                GUI.changePanel(panel, "Description Page");
            }
        });
    }

    private float calculateRating(float time) {
        if (time == 0.0f) {
            return Float.POSITIVE_INFINITY;
        }

        return 1.0f / time * 10000;
    }

    public void FillTextArea(Integer testNr) {
        try {
            String exePath = new String();
            switch (testNr){
                case 0:
                    exePath = "..\\DigitsOfPi\\x64\\Debug\\DigitsOfPi.exe";
                    break;
                case 1:
                    exePath = "..\\Fibonacci\\x64\\Debug\\Fibonacci.exe";
                    break;
                case 2:
                    exePath = "..\\Factorial\\x64\\Debug\\Factorial.exe";
                    break;
                case 3:
                    exePath = "..\\Factorizare\\x64\\Debug\\Factorizare.exe";
                    break;
                case 4:
                    exePath = "..\\FastFourierTransform\\x64\\Debug\\FastFourierTransform.exe";
                    break;
                case 5:
                    exePath = "..\\MatrixMultiplication\\x64\\Debug\\MatrixMultiplication.exe";
                    break;
                default:
            }

            // Use ProcessBuilder to start the external program
            ProcessBuilder processBuilder = new ProcessBuilder(exePath);
            // Redirect the error stream to the standard output so you can read it
            processBuilder.redirectErrorStream(true);
            // Start the process
            Process process = processBuilder.start();
            // Read the output of the external program
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                switch (testNr){
                    case 0:
                        digitsOfPITime = Double.parseDouble(line);
                        break;
                    case 1:
                        fibonacciTime = Double.parseDouble(line);
                        break;
                    case 2:
                        factorialTime = Double.parseDouble(line);
                        break;
                    case 3:
                        factorizareTime = Double.parseDouble(line);
                        break;
                    case 4:
                        fastFourierTransformTime = Double.parseDouble(line);
                        break;
                    case 5:
                        matrixMultiplicationTime = Double.parseDouble(line);
                        break;
                    default:
                }
            }

            // Wait for the process to finish
            int exitCode = process.waitFor();
            System.out.println("Exit Code For Case " + testNr +": " + exitCode);

        } catch (IOException | InterruptedException exception) {
            exception.printStackTrace();
        }

    }

//    private double calculateOverallRating() {
//        return WEIGHT_DIGITS_OF_PI * digitsOfPITime +
//                WEIGHT_FIBONACCI * fibonacciTime +
//                WEIGHT_FACTORIAL * factorialTime +
//                WEIGHT_FACTORIZARE * factorizareTime +
//                WEIGHT_FAST_FOURIER * fastFourierTransformTime +
//                WEIGHT_MATRIX_MULTIPLICATION * matrixMultiplicationTime;
//    }

    private double calculateOverallRating() {
        return (WEIGHT_DIGITS_OF_PI / (digitsOfPITime + 1e-6)) +
                (WEIGHT_FIBONACCI / (fibonacciTime + 1e-6)) +
                (WEIGHT_FACTORIAL / (factorialTime + 1e-6)) +
                (WEIGHT_FACTORIZARE / (factorizareTime + 1e-6)) +
                (WEIGHT_FAST_FOURIER / (fastFourierTransformTime + 1e-6)) +
                (WEIGHT_MATRIX_MULTIPLICATION / (matrixMultiplicationTime + 1e-6));
    }

}
