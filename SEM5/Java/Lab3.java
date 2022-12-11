public class Lab3 {
    public static void main(String[] args) {
        final String text = "Are you serious soome soooome? I don't even know what to say soooome some! Finally, some soooome good news.";
        final String[] sentences = text.replace(",","").split("(?<=[.!?])");

        String bigWord = "";
        final String startLetter = "s";
        final String endLetter = "e";

        for (String sentence : sentences) {
            String[] words = sentence.replaceAll("[^a-zA-Z ]","").split(" ");

            for (String word : words) {
                if (word.startsWith(startLetter)
                        && word.endsWith(endLetter)
                        && bigWord.length() < word.length()) {
                        bigWord = word;
                }
            }
        }
        String newText = text.replace(bigWord, "");
        System.out.println(newText);
    }
}
// C3 = 2 (String)
// C17 = 10 (З кожного речення заданого тексту видалити підрядок найбільшої довжини, що починається та закінчується заданими літерами.)