package app.view;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MainPage {
    private JPanel mainPanel;
    private JTextArea textArea;
    private JButton testRAMButton;
    private JButton testCPUButton;
    private String exePath;
    private ProcessBuilder processBuilder;
    private Process process;
    private BufferedReader reader;
    private String line;
    private int exitCode;

    public MainPage() {
        GUI.changePanel(mainPanel, "Description Page");

        FillTextArea();

        testRAMButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new TestRAM(mainPanel);
            }
        });

        testCPUButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new TestCPU(mainPanel);
            }
        });
    }

    public void FillTextArea() {
        try {
            // Specify the path to your CPU_Spec.exe file
            exePath = "..\\CPU_Spec\\x64\\Debug\\CPU_Spec.exe";
            // Use ProcessBuilder to start the external program
            processBuilder = new ProcessBuilder(exePath);
            // Redirect the error stream to the standard output so you can read it
            processBuilder.redirectErrorStream(true);
            // Start the process
            process = processBuilder.start();
            // Read the output of the external program
            reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            textArea.append("----------CPU----------" + "\n\n");
            while ((line = reader.readLine()) != null) {
                textArea.append(line + '\n');
            }
            // Wait for the process to finish
            exitCode = process.waitFor();
            System.out.println("Exit Code For CPU_Spec: " + exitCode);

            // Specify the path to your Cache_Spec.exe file
            exePath = "..\\Cache_Spec\\x64\\Debug\\Cache_Spec.exe";
            // Use ProcessBuilder to start the external program
            processBuilder = new ProcessBuilder(exePath);
            // Redirect the error stream to the standard output so you can read it
            processBuilder.redirectErrorStream(true);
            // Start the process
            process = processBuilder.start();
            // Read the output of the external program
            reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            textArea.append("----------Cache Memory----------" + "\n\n");
            while ((line = reader.readLine()) != null) {
                textArea.append(line + '\n');
            }
            // Wait for the process to finish
            exitCode = process.waitFor();
            System.out.println("Exit CodeFor Cache_Spec: " + exitCode);

            // Specify the path to your RAM_Spec.exe file
            exePath = "..\\RAM_Spec\\x64\\Debug\\RAM_Spec.exe";
            // Use ProcessBuilder to start the external program
            processBuilder = new ProcessBuilder(exePath);
            // Redirect the error stream to the standard output so you can read it
            processBuilder.redirectErrorStream(true);
            // Start the process
            process = processBuilder.start();
            // Read the output of the external program
            reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            textArea.append("----------RAM----------" + "\n\n");
            while ((line = reader.readLine()) != null) {
                textArea.append(line + '\n');
            }
            // Wait for the process to finish
            exitCode = process.waitFor();
            System.out.println("Exit Code For RAM_Spec: " + exitCode);
        } catch (IOException | InterruptedException exception) {
            exception.printStackTrace();
        }
    }
}