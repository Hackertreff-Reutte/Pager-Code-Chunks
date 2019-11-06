import javax.sound.sampled.*;
import javax.swing.*;
import java.util.ArrayList;

public class AudioSignalGenerator {


    //Beware only tested on windows

    public static ArrayList<String> messageDataArray = new ArrayList<String>();

    public static byte amplitude = 30; // max 127?
    public static byte allowNegativeAmplitude = 1; // 1 or 0    1 = with negative Amplitude
    public static int speed = 512; //transmission speed


    private static SourceDataLine sdl;


    public static void setupAudio() throws LineUnavailableException {


        AudioFormat af = new AudioFormat((float) 44100, 8, 1, true, false);
        Mixer.Info[] infos = AudioSystem.getMixerInfo();
        Mixer.Info mixerinfo = null;

        ArrayList<String> soundoptions = new ArrayList<String>();

        for (Mixer.Info inf : infos) {
            if (inf.getDescription().equals("Direct Audio Device: DirectSound Playback")) {
                soundoptions.add(inf.getName());
            }
        }

        String input = (String) JOptionPane.showInputDialog(null, "Choose Sound Output",
                "Sound Card Chooser", JOptionPane.QUESTION_MESSAGE, null, // Use
                // default
                // icon
                soundoptions.toArray(), // Array of choices
                soundoptions.toArray()[0]); // Initial choice

        for (Mixer.Info inf : infos) {
            if (inf.getName().equals(input)) {
                mixerinfo = inf;
            }
        }

        sdl = AudioSystem.getSourceDataLine(af, mixerinfo);

        sdl.open();
        sdl.start();
    }

    public static void closeAudio() {
        sdl.drain();
        sdl.stop();
    }


    public static void sendAudio() {

        int interval = 0;
        byte[] buf = new byte[1];

        for (String message : messageDataArray) {
            for (int i = 0; i < message.length(); i++) {


                //  interval = ((int) ((i / ((double) 44100)) 0* speed)) % 2;
                interval = message.charAt(i) - 48;


                for (int x = 0; x < 44100 / speed; x++) {
                    int value = amplitude * (1 + (-(1 + allowNegativeAmplitude)) * interval);
                    // System.out.println(value);
                    buf[0] = (byte) value;
                    sdl.write(buf, 0, 1);
                }
            }
        }

    }


    public static void main(String[] args) {

        try{
            setupAudio();
        }catch (LineUnavailableException e){
            e.printStackTrace();
        }


        //Just to open the vox
        messageDataArray.add("1010100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

        //POCSAG data
        messageDataArray.add("1010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101001111100110100100001010011011000011110101000100111000001100101110111101010001001110000011001011101111010100010011100000110010111011110101000100111000001100101110000100001101111010001000110100010000011010000010101010011010100011111001101001000010101110110001111010101000100000100000011100001111010100010011100000110010111011110101000100111000001100101110111101010001001110000011001011100100101101001011010010100101111011111001101001000010100110110000111101010001001110000011001011101111010100010011100000110010111011110101000100111000001100101110111101010001001110000011001011100001000011011110100010001101000100000110100000101010100110101000111110011010010000101011101100011110101010001000001000000111000011110101000100111000001100101110111101010001001110000011001011101111010100010011100000110010111001001011010010110100101001011110111110011010010000101001101100001111010100010011100000110010111011110101000100111000001100101110111101010001001110000011001011101111010100010011100000110010111000010000110111101000100011010001000001101000001010101001101010001111100110100100001010111011000111101010100010000010000001110000111101010001001110000011001011101111010100010011100000110010111011110101000100111000001100101110010010110100101101001010010111101111100110100100001010011011000011110101000100111000001100101110111101010001001110000011001011101111010100010011100000110010111011110101000100111000001100101110000100001101111010001000110100010000011010000010101010011010100011111001101001000010101110110001111010101000100000100000011100001111010100010011100000110010111011110101000100111000001100101110111101010001001110000011001011100100101101001011010010100101111");
        //data used from https://habr.com/en/post/438906/

        sendAudio();

        closeAudio();

    }
}
