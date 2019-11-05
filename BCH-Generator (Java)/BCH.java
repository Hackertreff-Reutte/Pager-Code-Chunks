public class BCH {


    public static boolean debug = false;


    public static long calculatePolynomialRemainder(long ShiftedData, int fullLength, long generator, int generatorLength){

        long remainder = 0;

        for(int i = fullLength; i > 0; i--){

            //append the remainder with the next bit of data from data
            remainder = (remainder << 1)^((ShiftedData >> (i-1))&1);

            if(debug) {
                System.out.println("Remainder: " + Long.toBinaryString(remainder));
            }
            //checks if the bit of the remainder that has the same location as the MSB of the generator is 1 (bit)
            if((remainder >> (generatorLength - 1)&1) == 1){
                remainder = remainder^generator;
                if(debug) {
                    System.out.println("XOR");
                }
            }

        }

        if(debug) {
            System.out.println("End Remainder: " + Long.toBinaryString(remainder) + "\n");
        }
        return remainder;
    }

    public static long generateBCH(long data, int dataLength, long generator, int generatorLength, int fullLength){

        //append data with 0 generator length
        long ShiftedData = data << (fullLength - dataLength); //BCH length (generator - 1)

        System.out.println("\nGenerating BCH Code: \n");

        System.out.println("BCH(" + fullLength + "," + dataLength + ")\n");

        long remainder = calculatePolynomialRemainder(ShiftedData, fullLength, generator, generatorLength);
        System.out.println("BCH Remainder: " + Long.toBinaryString(remainder));
        long newBCH = ShiftedData^remainder;
        System.out.println("\nNew BCH: " + Long.toBinaryString(newBCH) + "\n");

        return newBCH;
    }

    public static boolean checkBCH(long fullCode, int codeLength, long generator, int generatorLength){

        System.out.println("Checking BCH Code ....\n");

        long remainder = calculatePolynomialRemainder(fullCode, codeLength, generator, generatorLength);
        System.out.println("BCH Remainder: " + Long.toBinaryString(remainder));
        return remainder == 0;
    }

    public static void main(String[] args) {

        //String s_data = "100000110100000101010";

        //generator bit needs to start with 1 !!!! otherwise it makes no sense
        //String s_generator = "11101101001";


        //INFO BCH(code length, data length)

        String s_data = "011110101000100111000";
        String s_generator = "11101101001";
        int bchCodeLength = 10;  //number of bch bits in the code (code length - data length)

        int dataLength = s_data.length();
        int generatorLength = s_generator.length();
        int fullLength = dataLength + bchCodeLength;



        long generator = Long.parseLong(s_generator, 2);
        long data = Long.parseLong(s_data, 2);

        long newBCH = generateBCH(data, dataLength, generator, generatorLength, fullLength);

        System.out.println("\n\n---------------------------------------------------------------------------------\n\n");

        System.out.println("Checking generated String");
        boolean result = checkBCH(newBCH, 31, generator, generatorLength);

        System.out.println("\nThe code has no errors: " + result);

        System.out.println("\n\n---------------------------------------------------------------------------------\n\n");

        //-----------other BCH Code ----------------------------

        System.out.println("Checking other Code");


        String s_otherCode = "0111101010001001110001100110101";
        long otherCode = Long.parseLong(s_otherCode,2);

        int otherCodeLength = s_otherCode.length();


        result = checkBCH(otherCode, otherCodeLength, generator, generatorLength);

        System.out.println("\nThe code has no errors: " + result);
    }
}
