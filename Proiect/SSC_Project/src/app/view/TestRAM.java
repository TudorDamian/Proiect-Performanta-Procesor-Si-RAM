package app.view;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.DecimalFormat;

public class TestRAM {
    private JPanel testRAM;
    private JButton backButton;
    private JLabel ratingLabel;
    private Float testRAMTime;
    private static final DecimalFormat df = new DecimalFormat("0.00");

    public TestRAM(JPanel panel) {

        TestRAMTime();

        // Calculate the rating as the reciprocal of the time
        float rating = calculateRating(testRAMTime);

        ratingLabel.setText("Rating: " + df.format(rating));
        GUI.changePanel(testRAM, "RAM Test Page");

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

    public void TestRAMTime() {
        try {
            // Specify the path to your TestRAM.exe file
            String exePath = "..\\TestRAM\\x64\\Debug\\TestRAM.exe";
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
                testRAMTime = Float.parseFloat(line);
            }

            // Wait for the process to finish
            int exitCode = process.waitFor();
            System.out.println("Exit Code: " + exitCode);

        } catch (IOException | InterruptedException exception) {
            exception.printStackTrace();
        }
    }
}
