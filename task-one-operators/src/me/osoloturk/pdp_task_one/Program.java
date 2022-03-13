package me.osoloturk.pdp_task_one;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;
import java.util.stream.Collectors;

import static me.osoloturk.pdp_task_one.Constants.OPERATORS;


public class Program {

    public static void main(String[] args) {
        List<String> parameters = new ArrayList<>(Arrays.asList(args));
        parameters.add("Deneme.java");
        parameters.add("Deneme2.java");
        parameters.add("--debug");
        if (parameters.size() < 1) {
            System.out.println("You must have to define target files in parameters\n" +
                    "Example: java -jar app.jar targetfile.java targetfile2.java\n" +
                    "Not: You can use --debug or --expanded-debug parameter");
            return;
        }
        if (parameters.stream().anyMatch(s -> s.equalsIgnoreCase("--debug"))) {
            DEBUG_MODE = Program.DEBUG_MODE.ENABLED;
            parameters = parameters.stream()
                    .filter(s -> !s.equalsIgnoreCase("--debug"))
                    .collect(Collectors.toList());
        }
        if (parameters.stream().anyMatch(s -> s.equalsIgnoreCase("--expanded-debug"))) {
            DEBUG_MODE = Program.DEBUG_MODE.EXPANDED;
            parameters = parameters.stream()
                    .filter(s -> !s.equalsIgnoreCase("--expanded-debug"))
                    .collect(Collectors.toList());
        }
        start_analysis(parameters);
    }

    private static void start_analysis(List<String> files) {
        if (DEBUG_MODE != Program.DEBUG_MODE.CLOSE) {
            System.out.print("Requested Files:");
            System.out.println(files);
        }
        for (final String fileName : files) {
            File targetFile = new File(fileName);
            if (!targetFile.exists()) {
                System.out.println("File: " + fileName + "\n" +
                        "\tResult: Error\n" +
                        "\tCause: File not exist!");
                return;
            }
            Scanner scanner = null;
            try {
                scanner = new Scanner(targetFile);
            } catch (FileNotFoundException e) {
                System.out.println("File: " + fileName + "\n" +
                        "\tResult: Error\n" +
                        "\tCause: File not exist!");
                return;
            }
            ClassReader reader = new ClassReader();
            boolean in_comment = false;
            int in_block = 0;
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                line = preprocess(line);
                LinkedList<String> operatorQueue = new LinkedList<>();
                /*
                    Ignore for multiple line comments
                */
                if (line.startsWith("/*")) {
                    in_comment = true;
                }
                if (line.endsWith("*/")) {
                    in_comment = false;
                    continue;
                }
                if (in_comment) continue;

                /*
                    Ignore for the outscope blocks
                 */

                if (line.endsWith("{") && line.contains(")")) {
                    in_block++;
                }
                if (line.endsWith("}")) {
                    in_block--;
                }
                if (in_block <= 0) continue;
                while (true) {
                    String finalLine = line;
                    Optional<String> operator = OPERATORS.stream()
                            .filter(value -> finalLine.contains(value))
                            .findFirst();
                    if (operator.isPresent()) {
                        if (DEBUG_MODE != Program.DEBUG_MODE.CLOSE) {
                            System.out.println("Operator Founded:\n" +
                                    "\tLine:" + line + "\n" +
                                    "\tOperator: " + operator.get() + "\n" +
                                    "\tOperator Group: " + reader.getCategories(operator.get()));
                        }
                        int previouslyCount = line.length();
                        line = line.replace(operator.get(), "");
                        int diff = previouslyCount - line.length();
                        for (int i = 0; i < diff; i += operator.get().length())
                            reader.addDetection(operator.get());
                    } else {
                        if (DEBUG_MODE == Program.DEBUG_MODE.EXPANDED) {
                            System.out.println("Empty line for the operators:\n" +
                                    "\tLine:" + line);
                        }
                        break;
                    }
                }
            }
            System.out.println("File: " + fileName + "\n" +
                    "Result: Success\n" +
                    "Response:");
            int totalCounter = 0;
            System.out.println("Operator Bilgisi:");
            for (final OperatorGroup group : reader.getGroups()) {
                System.out.println("\t" + group.toString());
                totalCounter += group.getCount();
            }
            System.out.println("Operand Bilgisi:\n" +
                    "\tToplam Operand Sayisi: " + totalCounter);
            scanner.close();
        }
    }

    private static String preprocess(String line) {
        /*
            Clean for comment lines
            Source: https://stackoverflow.com/questions/36468305/java-regex-for-deleting-all-comments-programmatically
         */

        line = line.replaceAll("/\\*[^*]*(?:\\*(?!/)[^*]*)*\\*/|//.*", "");

        /*
            Clean strings
         */
        line = line.replaceAll("(\"[\\p{L}\\p{N}\\p{P}]+\")", "");
        line = line.replaceAll("(\'[\\p{L}\\p{N}\\p{P}]+\')", "");

        line = line.trim();
        return line;
    }

    public enum DEBUG_MODE {
        CLOSE, ENABLED, EXPANDED;
    }

    public static DEBUG_MODE DEBUG_MODE = Program.DEBUG_MODE.CLOSE;


}
