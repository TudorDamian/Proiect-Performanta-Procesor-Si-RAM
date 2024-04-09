package app.view;

import javax.swing.*;

public class GUI {
    private static JFrame appFrame = initFrame();

    private static JFrame initFrame() {
        JFrame frame = new JFrame();
        frame.setSize(500, 600);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        return frame;
    }

    public static void changePanel(JPanel panel, String frameTitle) {
        appFrame.setContentPane(panel);
        appFrame.setTitle(frameTitle);
        appFrame.getContentPane().revalidate();
        appFrame.getContentPane().repaint();
    }

    public static void showDialogMessage(String message) {
        JOptionPane.showMessageDialog(appFrame, message);
    }

    public static void showDialogMessageError(String message) {
        JOptionPane.showMessageDialog(appFrame, message, "Error", JOptionPane.ERROR_MESSAGE);
    }
}
