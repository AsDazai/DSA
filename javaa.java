import java.io.*;
import java.util.*;

public class ExternalSorting {
    public static void main(String[] args) throws IOException {
        // Input file containing unsorted data
        String inputFile = "input.txt";
        // Output file to store sorted data
        String outputFile = "output.txt";

        // Memory buffer size (number of records that can be sorted in memory)
        int bufferSize = 100; // Change this value as needed

        // Perform external sorting
        externalSort(inputFile, outputFile, bufferSize);
    }

    // External sorting function
    public static void externalSort(String inputFile, String outputFile, int bufferSize) throws IOException {
        // Open input and output streams
        BufferedReader reader = new BufferedReader(new FileReader(inputFile));
        BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile));

        // Read chunks of data into memory, sort them, and write them back to disk
        List<String> chunk = new ArrayList<>();
        String line;
        int chunkSize = 0;
        while ((line = reader.readLine()) != null) {
            chunk.add(line);
            chunkSize++;

            // If chunk size reaches the buffer size, sort and write the chunk to a temporary file
            if (chunkSize == bufferSize) {
                Collections.sort(chunk);
                for (String record : chunk) {
                    writer.write(record);
                    writer.newLine();
                }
                chunk.clear();
                chunkSize = 0;
            }
        }

        // Sort and write the remaining chunk to a temporary file
        if (!chunk.isEmpty()) {
            Collections.sort(chunk);
            for (String record : chunk) {
                writer.write(record);
                writer.newLine();
            }
        }

        // Close input and output streams
        reader.close();
        writer.close();

        // Merge sorted temporary files
        mergeSortedFiles(inputFile, outputFile);
    }

    // Merge sorted temporary files
    public static void mergeSortedFiles(String inputFile, String outputFile) throws IOException {
        // Open input streams for reading sorted chunks
        BufferedReader[] readers = {new BufferedReader(new FileReader(inputFile))};
        BufferedReader writer = new BufferedReader(new FileReader(outputFile));

        // Merge the sorted chunks using priority queue
        PriorityQueue<String> pq = new PriorityQueue<>();
        for (BufferedReader reader : readers) {
            String line = reader.readLine();
            if (line != null) {
                pq.add(line);
            }
        }

        // Write the sorted records to the output file
        BufferedWriter bw = new BufferedWriter(new FileWriter(outputFile));
        while (!pq.isEmpty()) {
            String minRecord = pq.poll();
            bw.write(minRecord);
            bw.newLine();

            // Read next record from the same input stream
            String nextRecord = readers[0].readLine();
            if (nextRecord != null) {
                pq.add(nextRecord);
            }
        }

        // Close input and output streams
        bw.close();
        for (BufferedReader reader : readers) {
            reader.close();
        }
    }
}
