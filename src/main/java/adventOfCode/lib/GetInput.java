package adventOfCode.lib;

import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URI;
import java.net.URL;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;


public class GetInput {
    private static final String ENV_VAR_NAME = "AOC_SESSION_KEY";
    private static final String INPUT_BASE_URL = "https://adventofcode.com/%s/day/%s/input";
    private static final String INPUTS_DIR = "inputs/%s";
    private static final String USER_AGENT_STR = "github.com/NoSpawnn/advent-of-code";

    private static String getSessionKey() throws Exception {
        String sessionKey = System.getenv(ENV_VAR_NAME);

        if (sessionKey == null || sessionKey.isEmpty()) {
            throw new Exception("Session key environment variable is unset");
        }

        return sessionKey;
    }

    private static HttpURLConnection buildRequest(String year, String day) throws Exception {
        String reqUrlStr = String.format(INPUT_BASE_URL, year, day);
        URL url = URI.create(reqUrlStr).toURL();

        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("GET");
        connection.setRequestProperty("User-Agent", USER_AGENT_STR);
        connection.setRequestProperty("Cookie", "session=" + getSessionKey());

        return connection;
    }

    public static void download(String year, String day) throws Exception {
        Path dir = Path.of("", String.format(INPUTS_DIR, year)).toAbsolutePath();
        Files.createDirectories(dir);

        Path filePath = Path.of(dir.toString(), String.format("%s.txt", day));

        if (Files.exists(filePath)) {
            System.out.println("!! input file already exists !!");
            return;
        }

        HttpURLConnection connection = buildRequest(year, day.startsWith("0") ? day.substring(1) : day);
        int responseCode = connection.getResponseCode();

        if (responseCode == HttpURLConnection.HTTP_NOT_FOUND) {
            System.out.printf("DOWNLOAD ERROR %d - requested input does not exist (%s day %s)\n", responseCode, year, day);
            return;
        } else if (responseCode == HttpURLConnection.HTTP_BAD_REQUEST) {
            System.out.printf("DOWNLOAD ERROR %d - is your session key correct?\n", responseCode);
            return;
        } else if (responseCode != HttpURLConnection.HTTP_OK) {
            System.out.printf("DOWNLOAD ERROR %d - %s\n", responseCode, connection.getResponseMessage());
            return;
        }

        try (InputStream inputStream = connection.getInputStream()) {
            Files.copy(inputStream, filePath, StandardCopyOption.REPLACE_EXISTING);
        }

        System.out.printf("File downloaded: %s%n", filePath);
    }
}
